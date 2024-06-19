#pragma once

#include "state/state.h"
#include "idl/message/message.pb.h"
#include <map>
#include <memory>

// 该类用于存储、修改某个连接的状态，提供相关接口
class CacheState
{
public:

    /// @brief CmdHandler需要用这个对象，ConnectionState也需要用到这个对象，但是conn_to_state_table_应当
    /// 全局保持唯一的一份，那干脆写成单例模式吧
    /// @return 
    static CacheState& Get();

    /// @brief 在state server服务器启动时调用，用来恢复分布式存储到redis中的connid、定时器等数据
    void Init();

    /// @brief 为某个连接客户端创建并管理连接状态对象
    /// @param connid 
    /// @param conn_state 
    void StoreConnIDState(uint64_t connid, std::shared_ptr<ConnectionState> conn_state);
    void DeleteConnIDState(uint64_t connid);
    std::shared_ptr<ConnectionState> GetConnIDState(uint64_t connid);


    /// @brief 将用户的did和conn_id拼接在一起存储进redis中
    /// @param did 
    /// @param conn_id 
    /// @return 
    std::string LoginSlotMarshal(uint64_t did, uint64_t connid);
    /// @brief 将redis中读取的conn_id信息解码，该信息是did和conn_id拼接而成的，把它俩分开
    /// @param login_slot 
    /// @return 第一个是did，第二个是conn_id
    std::pair<uint64_t, uint64_t> LoginSlotUnmarshal(const std::string& login_slot);
    /// @brief 根据connid获取对应存储的set集合名称，或者叫登录槽
    /// @param connid 
    /// @return 
    std::string GetLoginSlotKey(uint64_t connid);


    /// @brief 登录时需要调用该接口，该接口负责存储信息到redis的槽中，添加路由记录，创建ConnectionState并存储
    /// @param did 
    /// @param connid 
    void ConnLogin(uint64_t did, uint64_t connid);
    /// @brief state server重启时，读取并解析完存储在redis中的connid信息后，调用此方法恢复
    /// ConnectionState对象和里面的定时器
    /// @param did 
    /// @param connid 
    void ConnReload(uint64_t did, uint64_t connid);
    /// @brief 登出时的修改状态对象的操作，会去redis中删除connid等信息
    /// @param connid 
    /// @return 返回did，因为如果是重连场景，需要拿到did后重新调用ConnLogin
    uint64_t ConnLogOut(uint64_t connid);
    /// @brief 用户断线重连时调用该接口，该接口会修改用户状态，去redis中删掉老的connid信息，注册新的connid信息等操作
    /// 但这种做法并没有复用什么老连接的状态，那断线重连的意义是什么呢？
    /// @param old_connid 
    /// @param new_connid 
    /// @return 成功返回true，失败返回false
    bool ReConnection(uint64_t old_connid, uint64_t new_connid);


    /// @brief 重置心跳定时器接口
    /// @param connid 
    void ResetConnTimer(uint64_t connid);

    /// @brief 创建ConnectionState对象，仅用于state server重启时从redis恢复connid时使用，
    /// 如果后续没有其他地方使用的话，就放到私有属性中
    /// @param did 
    /// @param connid 
    /// @return 
    std::shared_ptr<ConnectionState> NewConnState(uint64_t did, uint64_t connid);

    /// @brief 使用lua脚本实现在redis中比较并自增max_client_id
    /// @param connid 
    /// @param old_max_clientid 
    /// @return 
    bool CompareAndIncrClientID(uint64_t connid, uint64_t old_max_clientid);

    /// @brief 将push_msg挂载到redis飞行队列中，启动重发定时器
    /// @param connid 
    /// @param push_msg 未序列化的push_msg对象
    /// @param push_msg_str 这是push_msg序列化后的字符串，最后会直接挂到redis飞行队列中，其实也可以将push_msg反序列化后
    /// 再挂到飞行队列中，但多一次反序列化步骤感觉性能开销还是比较大的
    /// @return 
    bool AppendLastMsg(uint64_t connid, message::PushMsg& push_msg, std::string& push_msg_str);

    /// @brief 去redis中读取飞行队列中的最后的消息，别忘了redis中存储了三个东西MaxClientIDKey、LoginSlotSetKey、LastMsgKey。
    /// 通过LastMsgKey去redis查询，就能去读取最后的消息，当然消息可能超时或者压根就没有导致读不到
    /// @param connid 
    /// @return 返回最新的消息的指针，如果指针为空，那么说明没有飞行消息，如果不为空，就说明确实有最新消息没推送
    std::unique_ptr<message::PushMsg> GetLastMsg(uint64_t connid);
    /// @brief 收到用户传来的确认消息时，根据确认消息信息来删除redis飞行队列中的消息，删除重传定时器
    /// @param connid 
    /// @param sessionid 
    /// @param msgid 
    void AckLastMsg(uint64_t connid, uint64_t sessionid, uint64_t msgid);

    // 计算conn_id对应的set名称中的插槽值
    uint64_t GetConnStateSlot(uint64_t connid);

private:
    CacheState() = default;
    CacheState(const CacheState&) = delete;
    CacheState& operator= (const CacheState&) = delete;

    // 这个表需要锁吗？是否存在线程安全问题
    std::map<uint64_t, std::shared_ptr<ConnectionState>> conn_to_state_table_;
};
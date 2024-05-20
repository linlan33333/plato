#pragma once

#include <semaphore.h>
#include <zookeeper/zookeeper.h>
#include <string>
#include <functional>

class ZkClient;
struct Context
{
    struct String_vector* s_v_ptr = nullptr;

    ZkClient* zk_cli_ptr = nullptr;
};

// 封装的zk客户端
class ZkClient
{
public:
    ZkClient();
    ~ZkClient();

    // zkclient启动连接zkserver
    void Start();
    // 再zkserver上根据指定的path创建znode节点
    /**
     * path表示znode节点路径，data表示节点的值
     * datalen表示节点的值的长度，state表示这是一个临时性节点还是永久性节点（0为永久性节点）
    */
    void Create(const char* path, const char* data, int datalen, int state = 0);
    // 根据参数指定的znode节点路径，或者znode节点的值
    std::string GetData(const char* path);

    /// @brief 获取目录下的所有孩子节点信息
    /// @param path 
    /// @param children 传入一个String_vector类型变量的地址，方便把结果放到里面
    /// @return 获取成功返回true，失败返回false
    bool GetChildren(const char* path, String_vector* children);

    /// @brief 设置某个路径下的子节点新增时的回调函数
    /// @param func 
    void SetChildNodeNumAddCallback(std::function<void(zhandle_t*, const char*, const char*)> func);
    /// @brief 设置某个路径下的子节点删除时的回调函数
    /// @param func 
    void SetChildNodeNumDelCallback(std::function<void(zhandle_t*, const char*)> func);

    /// @brief 该函数用于检查某个节点路径下的子节点是否发生数量变化，比如新增、删除子节点，然后执行
    void check_and_trigger(zhandle_t *zh, struct String_vector *previous, struct String_vector *current);

private:  
    // zk的客户端句柄，通过句柄才能操作zkserver
    zhandle_t* m_zhandle;

    /// @brief 全局监控器函数中的上下文信息对象
    Context* watcher_ctx_;

    /// @brief 某个节点的子节点数量增加时的回调函数，会传入该节点的数据
    std::function<void(zhandle_t*, const char*, const char*)> child_node_num_add_callback_;
    /// @brief 某个节点的子节点数量减少时的回调函数，会传入该节点的数据
    std::function<void(zhandle_t*, const char*)> child_node_num_del_callback_;
};
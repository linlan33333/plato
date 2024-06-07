#include "cmdhandler.h"
#include "state/timer.h"
#include "cache.h"
#include "rpc/client/gatewaycaller.h"
#include "idl/message/message.pb.h"
#include <spdlog/spdlog.h>

CmdHandler &CmdHandler::Get()
{
    static CmdHandler handler;
    return handler;
}

MsgHandler CmdHandler::GetHandler(message::CmdType type)
{
    auto msg_handler_pair = msg_handler_map_.find(type);
    if (msg_handler_pair != msg_handler_map_.end()) 
    {
        return msg_handler_pair->second;
    }

    // 返回个空的临时对象
    return MsgHandler ();
}

void CmdHandler::MsgCmdHandler(CmdContext& cmd_ctx)
{
    message::MsgCmd msg_cmd;
    if (!msg_cmd.ParseFromString(cmd_ctx.Payload))
    {
        spdlog::warn("CmdHandler.cc::MsgCmdHandler: Parse message from string failed!");
        return;
    }

    message::CmdType type = msg_cmd.type();
    // 调用相应的handler函数处理
    GetHandler(type)(cmd_ctx, msg_cmd);
}

CmdHandler::CmdHandler()
{
    msg_handler_map_.insert({message::CmdType::Login, std::bind(&CmdHandler::LoginMsgHandler, this, std::placeholders::_1, std::placeholders::_2)});
    msg_handler_map_.insert({message::CmdType::Heartbeat, std::bind(&CmdHandler::HeartBeatMsgHandler, this, std::placeholders::_1, std::placeholders::_2)});
    msg_handler_map_.insert({message::CmdType::ReConn, std::bind(&CmdHandler::ReConnMsgHandler, this, std::placeholders::_1, std::placeholders::_2)});
    msg_handler_map_.insert({message::CmdType::UP, std::bind(&CmdHandler::UpMsgHandler, this, std::placeholders::_1, std::placeholders::_2)});
    msg_handler_map_.insert({message::CmdType::ACK, std::bind(&CmdHandler::AckMsgHandler, this, std::placeholders::_1, std::placeholders::_2)});
}

void CmdHandler::LoginMsgHandler(CmdContext& ctx, message::MsgCmd& cmd)
{
    message::LoginMsg login_msg;
    std::string msg_str = cmd.payload();
    if (!login_msg.ParseFromString(msg_str))
    {
        spdlog::warn("CmdHandler.cc::LoginMsgHandler: Parse from string error!");
        return;
    }

    // 这里处理业务逻辑，将消息发给业务层进行下一步
    // 。。。。。。
    std::cout << "恭喜你登录成功" << std::endl;

    // 存储该用户的连接状态
    std::shared_ptr<ConnectionState> conn_state(std::make_shared<ConnectionState>(ctx.ConnID, login_msg.head().deviceid()));
    CacheState::Get().StoreConnIDState(ctx.ConnID, conn_state);
    
    // 设置心跳定时器，期间没有心跳消息则登出
    uint32_t timer_id = Timer::Get().RunAfter(3 * 1000, std::bind(&CacheState::ConnLogOut, &(CacheState::Get()), ctx.ConnID));
    conn_state->SetHeartTimerId(timer_id);

    // 回复客户端登录成功
    SendAckMsg(message::Login, ctx.ConnID, 0, 0, "login ok");
}

void CmdHandler::HeartBeatMsgHandler(CmdContext& ctx, message::MsgCmd& cmd)
{
    message::HeartbeatMsg msg;
    std::string msg_str = cmd.payload();
    if (!msg.ParseFromString(msg_str))
    {
        spdlog::warn("CmdHandler.cc::HeartBeatMsgHandler: Parse from string error!");
        return;
    }

    // 重置心跳定时器
    std::shared_ptr<ConnectionState> conn_state = CacheState::Get().GetConnIDState(ctx.ConnID);
    if (conn_state != nullptr) 
    {
        conn_state->ResetHeartBeatTimer();
    }

    // TODO 为减少通信量，可以暂时不回复心跳的ack
}

void CmdHandler::ReConnMsgHandler(CmdContext &ctx, message::MsgCmd &cmd)
{
    message::ReConnMsg msg;
    std::string msg_str = cmd.payload();
    if (!msg.ParseFromString(msg_str))
    {
        spdlog::warn("CmdHandler.cc::ReConnMsgHandler: Parse from string error!");
        return;
    }

    // 重连消息头中的connID才是上一次断开连接的connID
    uint64_t last_connid = msg.head().connid();
    // 找到原来的ConnectionState
    std::shared_ptr<ConnectionState> conn_state = CacheState::Get().GetConnIDState(last_connid);
    if (conn_state != nullptr) 
    {
        // 先停止重连定时器，都已经触发重连定时器了，说明心跳定时器早执行完了
        // 那心跳定时器咋不设置呢？因为客户端会发送心跳消息，当收到心跳消息时自动重置心跳定时器
        // 那如果客户端发送重连信令后又断开连接了呢？这个情况下该怎么办？
        // 所以个人认为这里就得重新设置一下心跳计时器，客户端不发心跳就清理资源
        conn_state->DeleteReConnTimer();
        conn_state->ResetHeartBeatTimer();
        // 得给conn_state更换connid了
        CacheState::Get().DeleteConnIDState(last_connid);
        CacheState::Get().StoreConnIDState(ctx.ConnID, conn_state);

        SendAckMsg(message::ReConn, ctx.ConnID, 0, 0, "reconn ok");
        return;
    }

    // 没找到这个状态，那就说明已经被清理了，重连失败，让客户端重新登录吧
    SendAckMsg(message::ReConn, ctx.ConnID, 0, 1, "reconn failed");
}

void CmdHandler::UpMsgHandler(CmdContext &ctx, message::MsgCmd &cmd)
{
    message::UPMsg up_msg;
    std::string msg_str = cmd.payload();
    if (!up_msg.ParseFromString(msg_str))
    {
        spdlog::warn("CmdHandler.cc::UpMsgHandler: Parse from string error!");
        return;
    }

    // 先拿到ConnectionState对象
    std::shared_ptr<ConnectionState> conn_state = CacheState::Get().GetConnIDState(ctx.ConnID);
    if (conn_state != nullptr)
    {
        // 接收到的消息是连贯的，交付业务服务器去做进一步处理
        if (conn_state->CheckUPMsg(up_msg.head().clientid()))
        {
            // 调用下游业务层rpc，只有当rpc回复成功后才能更新max_clientID
			// 这里先假设成功
            // 。。。。。。
            conn_state->AddMaxClientId();

            std::cout << "收到的消息是：" << up_msg.upmsgbody() << std::endl;
            // 客户端发上行消息过来我就回上行消息过去，要是CmdType设为ACK客户端就分不清这是哪个信令的ACK了
            SendAckMsg(message::CmdType::UP, ctx.ConnID, up_msg.head().clientid(), 0, "recieve msg ok");

            ///////////////////////////// 以下是模拟给用户推送消息，让用户回复ack，来测试下行消息处理器好不好使
            message::PushMsg push_msg;
            push_msg.set_msgid(10086);
            push_msg.set_sessionid(10086);
            push_msg.set_content(up_msg.upmsgbody());
            std::string push_msg_str;
            if (!push_msg.SerializeToString(&push_msg_str))
            {
                spdlog::warn("CmdHandler.cc::UpMsgHandler: PushMsg serialize to string error!");
                return;
            }

            // 让消息id自增
            conn_state->AddMsgId();
            
            // 和之前说的一样，只保留最新推送给客户端的消息定时器，老的推送消息的定时器都取消
            conn_state->DeleteMsgTimer();
            // 创建新的消息的定时器，无限重传
            // 该方法内部会将消息先推送给客户端，所以不需要调用SendMsg了，直接调用它即可
            RePush(ctx.ConnID, push_msg_str);
        }
        // 接收的消息不连贯怎么办，这里先按下不表
        else 
        {
            spdlog::info("CmdHandler.cc::UpMsgHandler: The received message is not coherent");
        }
    }
    else
    {
        spdlog::warn("CmdHandler.cc::UpMsgHandler: Can\'t find ConnectionState object!");
    }
}

void CmdHandler::AckMsgHandler(CmdContext &ctx, message::MsgCmd &cmd)
{
    message::ACKMsg ack_msg;
    std::string msg_str = cmd.payload();
    if (!ack_msg.ParseFromString(msg_str))
    {
        spdlog::warn("CmdHandler.cc::AckMsgHandler: Parse from string error!");
        return;
    }

    std::shared_ptr<ConnectionState> conn_state = CacheState::Get().GetConnIDState(ctx.ConnID);
    if (conn_state != nullptr) 
    {
        // 客户端回复了ACK，就取消掉该消息的定时器，这里只做测试用，逻辑简化一下
        // 注意客户端是可以合并确认的，只需要发送最后一次服务器推送的消息的ACK即可，这样服务器就知道客户端
        // 收到的消息到哪一条了
        conn_state->DeleteMsgTimer();
    }
    else 
    {
        spdlog::warn("CmdHandler.cc::AckMsgHandler: Can\'t find ConnectionState object!");
    }
}

void CmdHandler::SendAckMsg(message::CmdType cmd_type, uint64_t connid, uint64_t clientid, uint32_t code, std::string msg)
{
    message::ACKMsg ack_msg;
    ack_msg.set_code(code);
    ack_msg.set_msg(msg);
    ack_msg.set_connid(connid);
    ack_msg.set_type(message::ACK);
    ack_msg.set_clientid(clientid);

    std::string download;
    if (!ack_msg.SerializeToString(&download))
    {
        spdlog::warn("CmdHandler.cc::SendAckMsg: Serialize to ACKMsg error!");
        return;
    }

    SendMsg(connid, message::ACK, download);
}

// 发送msg，消息必须打包成MsgCmd再发送，接收也是MsgCmd，发送也是MsgCmd才行
void CmdHandler::SendMsg(uint64_t connid, message::CmdType cmd_type, std::string &download)
{
    message::MsgCmd msg_cmd;
    msg_cmd.set_type(cmd_type);
    msg_cmd.set_payload(download);

    std::string data;
    if (!msg_cmd.SerializeToString(&data))
    {
        spdlog::warn("CmdHandler.cc::SendMsg: Serialize to MsgCmd error!");
        return;
    }

    GatewayCaller::Get().Push(connid, data);
}

// 这里需要完成发送消息和重设定时器两个步骤，然后递归地设置定时器任务为该函数，做到无限重发的效果
void CmdHandler::RePush(uint64_t connid, std::string &msg_data)
{
    SendMsg(connid, message::CmdType::Push, msg_data);

    // 每次自己重新去查找有无该连接对象，防止该连接对象都没了还重发个啥
    std::shared_ptr<ConnectionState> conn_state = CacheState::Get().GetConnIDState(connid);
    if (conn_state != nullptr)
    {
        // 这里不需要判断该定时器对应的消息是不是最新的，因为不是最新的话UpMsgHandler函数里面就已经取消掉该定时器了
        // 所以只要是消息重发的定时器那一定是最新的消息
        uint32_t msg_timer_id = Timer::Get().RunAfter(100, std::bind(&CmdHandler::RePush, &(CmdHandler::Get()), connid, msg_data));
        conn_state->SetMsgTimerId(msg_timer_id);
    }
    else
    {
        spdlog::warn("CmdHandler.cc::RePush: Repush message failed! Can\'t find connection state object!");
    }
}

#include "domain/message/writer/rpc/service/impl.h"
#include "common/grpc/domain/code.h"
#include "flowcontroller.h"
#include <spdlog/spdlog.h>

grpc::Status MessageWriterRpcServiceImpl::PushMessage(grpc::ServerContext *context, const ::MessageDomain::PushMessageRequest *request, ::MessageDomain::PushMessageResponse *response)
{
    // 解析请求体的数据
    uint64_t session_id = request->sessionid();
    message::SessionType type = request->type();

    // 调用请求messageID的接口
    uint64_t message_id = 0;

    message::MessageDTO message = request->message();
    message.set_messageid(message_id);

    // MessageDTO装填上messageID后就可以进行下一步处理了
    std::string message_str;
    if (!message.SerializeToString(&message_str))
    {
        spdlog::error("MessageWriterRpcServiceImpl.cc::PushMessage: Serialize MessageDTO error! Message will lost!");

        response->set_code(Domain::Code::UPLOADMESSAGEERROR);
        response->set_msg("Serialize message to MessageDTO error! Message will lost!");
        return grpc::Status::OK;
    }

    // TODO: 存储层存储消息，理论上要按照消息的因果一致和最终一致性存到不同类型的数据库中
    // 但目前只实现因果一致性的聊天APP，所以这里不做区分了，直接往数据库里存
    // 。。。。。。。。。。。。。

    // 消息推送，由于消息已经存储到数据库中，可以确保数据不丢失了，那么异步推送消息即可，不需要等待消息推送成功再返回
    // 对于超大群聊，走流控组件，即临时保存住该超大群聊的消息一段时间，根据数据量判断是否需要做协议升降级
    if (type == message::SessionType::SUPER) 
    {
        FlowController::Get().AddMessageAndCheckFlow(session_id, message_id, message_str);
    }

    // TODO: 对于普通消息，直接让MessageSender推送消息即可
    message::MsgCmd msg_cmd;
    msg_cmd.set_type(message::CmdType::Push);
    msg_cmd.set_payload(message_str);
    // 调用MessageSender发送消息
    // 。。。。。。。。。。

    response->set_code(Domain::Code::SUCCESS);
    return grpc::Status::OK;
}
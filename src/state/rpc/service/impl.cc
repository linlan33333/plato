#include "state/rpc/service/impl.h"
#include "state/workpool.h"
#include "rpc/client/gatewaycaller.h"
#include "grpc/state/state.pb.h"
#include "cmdhandler.h"
#include "grpc/state/cmdcontext.h"
#include <spdlog/spdlog.h>

grpc::Status StateServerRpcServiceImpl::CancelConn(grpc::ServerContext* context, const StateRequest* request, StateResponse *response)
{
    // 可能涉及到业务服务器等多个服务器的处理逻辑，暂时搁置，学完了再做

    // 返回RPC响应，只需设置好值就行，会自动帮我们将response发回去
    response->set_code(0);
    response->set_msg("success");

    return grpc::Status::OK;
}

grpc::Status StateServerRpcServiceImpl::SendMsg(grpc::ServerContext* context, const StateRequest* request, StateResponse *response)
{
    CmdContext ctx;
    ctx.Cmd = CMD::SendMsgCmd;
    ctx.ConnID = request->connid();
    ctx.Endpoint = request->endpoint();
    ctx.Payload = request->data();

    // 这里处理网关发来的信令，把信令直接丢给CmdHandler形成一个任务，把这个任务扔给线程池异步去做
    WorkPool::Get().Push(std::bind(&CmdHandler::MsgCmdHandler, &(CmdHandler::Get()), ctx));

    // 返回RPC响应，只需设置好值就行，会自动帮我们将response发回去
    response->set_code(0);
    response->set_msg("success");

    return grpc::Status::OK;
}


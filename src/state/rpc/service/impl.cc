#include "state/rpc/service/impl.h"
#include "state/workpool.h"
#include "rpc/client/gatewaycaller.h"
#include "grpc/state/state.pb.h"
#include "cmdhandler.h"
#include "grpc/state/cmdcontext.h"
#include <spdlog/spdlog.h>
#include "impl.h"

grpc::Status StateServerRpcServiceImpl::CancelConn(grpc::ServerContext* context, const StateRequest* request, StateResponse *response)
{
    // 打印日志
    spdlog::info("RPC server: Cancel connection! endpoint: {1}, connid: {2}, data: {3}", request->endpoint(), request->connid(), request->data());

    // 去redis中删除掉该用户的登录信息
    CacheState::Get().ConnLogOut(request->connid());

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


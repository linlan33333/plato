#include "state/rpc/service/impl.h"
#include "rpc/client/gatewaycaller.h"
#include "state/workpool.h"

void StateServerRpcServiceImpl::CancelConn(StateRequest *request, StateResponse *response, srpc::RPCContext *ctx)
{
    // 可能涉及到业务服务器等多个服务器的处理逻辑，暂时搁置，学完了再做

    // 返回RPC响应，只需设置好值就行，会自动帮我们将response发回去
    response->set_code(0);
    response->set_msg("success");
}

void StateServerRpcServiceImpl::SendMsg(StateRequest *request, StateResponse *response, srpc::RPCContext *ctx)
{
    
    std::string endpoint = request->endpoint();
    unsigned long long connid = request->connid();
    std::string data = request->data();

    // 这里先测试echo效果，即网关发送给我什么消息，我就回复给网关什么消息
    // 这里应当调用rpc客户端的接口发送回消息，把这个任务扔给线程池异步去做
    WorkPool::Get().Push(std::bind(&GatewayCaller::Push, GatewayCaller::Get(), connid, data));

    // 返回RPC响应，只需设置好值就行，会自动帮我们将response发回去
    response->set_code(0);
    response->set_msg("success");
}
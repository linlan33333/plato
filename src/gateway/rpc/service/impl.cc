#include "rpc/service/impl.h"
#include "gateway/workpool.h"

GatewayRpcServiceImpl::GatewayRpcServiceImpl(NetService *net_service)
    : net_service_(net_service)
{
}

void GatewayRpcServiceImpl::DelConn(GatewayRequest *request, GatewayResponse *response, srpc::RPCContext *ctx)
{
    // 给线程池放入cmd信令，后续逻辑交给线程池处理

    // 返回RPC响应，只需设置好值就行，会自动帮我们将response发回去
    response->set_code(0);
    response->set_msg("success");
}

void GatewayRpcServiceImpl::Push(GatewayRequest *request, GatewayResponse *response, srpc::RPCContext *ctx)
{
    // echo回声测试，这里会获取到gateway发送给state server的数据
    // 把它打印出来
    unsigned long long connid = request->connid();
    std::string data = request->data();

    std::cout << "接收到state server发过来的消息: " << data << std::endl;

    // 把数据发回给客户端，同样使用线程池去异步执行任务
    WorkPool::Get().Push([connid, data, this] () {
        muduo::net::TcpConnectionPtr* conn = net_service_->GetConnById(connid);
        conn->send(data);
    });


    // 返回RPC响应，只需设置好值就行，会自动帮我们将response发回去
    response->set_code(0);
    response->set_msg("success");
}

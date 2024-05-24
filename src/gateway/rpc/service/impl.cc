#include "rpc/service/impl.h"
#include "gateway/workpool.h"
#include <spdlog/spdlog.h>

GatewayRpcServiceImpl::GatewayRpcServiceImpl(NetService* net_service)
    : net_service_(net_service)
{

}

grpc::Status GatewayRpcServiceImpl::DelConn(grpc::ServerContext* context, const GatewayRequest* request, GatewayResponse *response)
{
    // 给线程池放入cmd信令，后续逻辑交给线程池处理

    // 返回RPC响应，只需设置好值就行，会自动帮我们将response发回去
    response->set_code(0);
    response->set_msg("success");

    return grpc::Status::OK;
}

grpc::Status GatewayRpcServiceImpl::Push(grpc::ServerContext* context, const GatewayRequest* request, GatewayResponse *response)
{
    // echo回声测试，这里会获取到gateway发送给state server的数据
    // 把它打印出来
    unsigned long long connid = request->connid();
    std::string data = request->data();

    // 把数据发回给客户端，同样使用线程池去异步执行任务
    WorkPool::Get().Push([connid, data, this] () {
        muduo::net::TcpConnection* conn = net_service_->GetConnById(connid);
        if (conn == nullptr) 
        {
            return;
        }
        if (conn->disconnected()) 
        {
            spdlog::warn("gateway/impl.cc:33: The target TcpConnection has disconnected!");
            return;
        }

        conn->send(data);
    });

    // 返回RPC响应，只需设置好值就行，会自动帮我们将response发回去
    response->set_code(0);
    response->set_msg("success");

    return grpc::Status::OK;
}
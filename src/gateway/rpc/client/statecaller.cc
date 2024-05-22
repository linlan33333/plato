#include "rpc/client/statecaller.h"
#include "config/state.h"
#include <spdlog/spdlog.h>

static WFFacilities::WaitGroup wait_group(1);

void sig_handler(int signo)
{
	wait_group.done();
}

StateCaller::StateCaller()
    : client_(StateServerConfig::Get().GetIp().c_str(), StateServerConfig::Get().GetPort())
{    
}

void StateCaller::cancelconn_done(StateResponse *response, srpc::RPCContext *context)
{
    // 这个逻辑暂时还没学，先不管
    // 是不是去mainLoop中删掉该连接的有关信息？

}

void StateCaller::sendmsg_done(StateResponse *response, srpc::RPCContext *context)
{
    std::cout << response->msg() << std::endl;
}

StateCaller &StateCaller::Get()
{
    static StateCaller caller;
    return caller;
}

void StateCaller::CancelConn(std::string endpoint, unsigned long long connid, std::string data)
{
    StateRequest cancelconn_req;
    cancelconn_req.set_endpoint(endpoint);
    cancelconn_req.set_connid(connid);
    cancelconn_req.set_data(data);
    
    client_.CancelConn(&cancelconn_req, std::bind(&StateCaller::cancelconn_done, this, std::placeholders::_1, std::placeholders::_2));

    wait_group.wait();
	google::protobuf::ShutdownProtobufLibrary();
}

void StateCaller::SendMsg(std::string endpoint, unsigned long long connid, std::string data)
{
    StateRequest push_req;
    push_req.set_endpoint(endpoint);
    push_req.set_connid(connid);
    push_req.set_data(data);

    std::cout << "已发送消息：" << data << std::endl;

    client_.SendMsg(&push_req, std::bind(&StateCaller::sendmsg_done, this, std::placeholders::_1, std::placeholders::_2));

    wait_group.wait();
	google::protobuf::ShutdownProtobufLibrary();
}

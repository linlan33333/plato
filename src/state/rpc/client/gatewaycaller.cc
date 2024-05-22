#include "rpc/client/gatewaycaller.h"
#include "config/gateway.h"

static WFFacilities::WaitGroup wait_group(1);

void sig_handler(int signo)
{
	wait_group.done();
}

GatewayCaller &GatewayCaller::Get()
{
    static GatewayCaller caller;
    return caller;
}

GatewayCaller::GatewayCaller()
    : client_(GatewayConfig::Get().GetIp().c_str(), GatewayConfig::Get().GetPortForRPCService())
{
}

void GatewayCaller::DelConn(unsigned long long connid, std::string data)
{
    GatewayRequest delconn_req;
    delconn_req.set_connid(connid);
    delconn_req.set_data(data);

    client_.DelConn(&delconn_req, std::bind(&GatewayCaller::delconn_done, this, std::placeholders::_1, std::placeholders::_2));

    wait_group.wait();
	google::protobuf::ShutdownProtobufLibrary();
}

void GatewayCaller::Push(unsigned long long connid, std::string data)
{
    GatewayRequest push_req;
    push_req.set_connid(connid);
    push_req.set_data(data);

    std::cout << "state server已回拨消息: " << data << std::endl;

    client_.Push(&push_req, std::bind(&GatewayCaller::push_done, this, std::placeholders::_1, std::placeholders::_2));

    wait_group.wait();
	google::protobuf::ShutdownProtobufLibrary();
}

void GatewayCaller::delconn_done(GatewayResponse *response, srpc::RPCContext *context)
{
    // 这个逻辑暂时没学，先搁置
    // 需要去修改本服务器的该用户的状态，再通知业务服务器去下线之类的
}

void GatewayCaller::push_done(GatewayResponse *response, srpc::RPCContext *context)
{
    std::cout << response->msg() << std::endl;
}

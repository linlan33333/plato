#include "srpc/gateway/gateway.srpc.h"
#include "workflow/WFFacilities.h"

using namespace srpc;

static WFFacilities::WaitGroup wait_group(1);

void sig_handler(int signo)
{
	wait_group.done();
}

class GatewayServiceImpl : public Gateway::Service
{
public:

	void DelConn(GatewayRequest *request, GatewayResponse *response, srpc::RPCContext *ctx) override
	{
		// TODO: fill server logic here
	}

	void Push(GatewayRequest *request, GatewayResponse *response, srpc::RPCContext *ctx) override
	{
		// TODO: fill server logic here
	}
};

int main()
{
	GOOGLE_PROTOBUF_VERIFY_VERSION;
	unsigned short port = 1412;
	SRPCServer server;

	GatewayServiceImpl gateway_impl;
	server.add_service(&gateway_impl);

	server.start(port);
	wait_group.wait();
	server.stop();
	google::protobuf::ShutdownProtobufLibrary();
	return 0;
}

#include "srpc/gateway/gateway.srpc.h"
#include "workflow/WFFacilities.h"

using namespace srpc;

static WFFacilities::WaitGroup wait_group(1);

void sig_handler(int signo)
{
	wait_group.done();
}

// 调用远程rpc请求的接口
static void delconn_done(GatewayResponse *response, srpc::RPCContext *context)
{
}

static void push_done(GatewayResponse *response, srpc::RPCContext *context)
{
}

int main()
{
	GOOGLE_PROTOBUF_VERIFY_VERSION;
	const char *ip = "127.0.0.1";
	unsigned short port = 1412;

	Gateway::SRPCClient client(ip, port);

	// example for RPC method call
	GatewayRequest delconn_req;
	//delconn_req.set_message("Hello, srpc!");
	client.DelConn(&delconn_req, delconn_done);

	wait_group.wait();
	google::protobuf::ShutdownProtobufLibrary();
	return 0;
}

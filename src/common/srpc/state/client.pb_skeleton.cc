#include "state.srpc.h"
#include "workflow/WFFacilities.h"

using namespace srpc;

static WFFacilities::WaitGroup wait_group(1);

void sig_handler(int signo)
{
	wait_group.done();
}

static void cancelconn_done(StateResponse *response, srpc::RPCContext *context)
{
}

static void sendmsg_done(StateResponse *response, srpc::RPCContext *context)
{
}

int main()
{
	GOOGLE_PROTOBUF_VERIFY_VERSION;
	const char *ip = "127.0.0.1";
	unsigned short port = 1412;

	State::SRPCClient client(ip, port);

	// example for RPC method call
	StateRequest cancelconn_req;
	//cancelconn_req.set_message("Hello, srpc!");
	client.CancelConn(&cancelconn_req, cancelconn_done);

	wait_group.wait();
	google::protobuf::ShutdownProtobufLibrary();
	return 0;
}

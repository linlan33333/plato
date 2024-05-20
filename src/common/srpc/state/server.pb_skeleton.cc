#include "state.srpc.h"
#include "workflow/WFFacilities.h"

using namespace srpc;

static WFFacilities::WaitGroup wait_group(1);

void sig_handler(int signo)
{
	wait_group.done();
}

class StateServiceImpl : public State::Service
{
public:

	void CancelConn(StateRequest *request, StateResponse *response, srpc::RPCContext *ctx) override
	{
		// TODO: fill server logic here
	}

	void SendMsg(StateRequest *request, StateResponse *response, srpc::RPCContext *ctx) override
	{
		// TODO: fill server logic here
	}
};

int main()
{
	GOOGLE_PROTOBUF_VERIFY_VERSION;
	unsigned short port = 1412;
	SRPCServer server;

	StateServiceImpl state_impl;
	server.add_service(&state_impl);

	server.start(port);
	wait_group.wait();
	server.stop();
	google::protobuf::ShutdownProtobufLibrary();
	return 0;
}

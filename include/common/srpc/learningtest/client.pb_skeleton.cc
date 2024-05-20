#include "signup.srpc.h"
#include "workflow/WFFacilities.h"

using namespace srpc;

static WFFacilities::WaitGroup wait_group(1);

void sig_handler(int signo)
{
	wait_group.done();
}

// 收到RPC调用结果后的回调函数
// context可以和workflow的series对接，也可以获取一些连接信息等
static void signup_done(RespSignup *response, srpc::RPCContext *context)
{
	// 查看结果，这里的response已经反序列化好了
	std::cout << "response: " << response->code() << "  " << response->message() << std::endl;
}

int main()
{
	GOOGLE_PROTOBUF_VERIFY_VERSION;
	// 目标服务器的ip和端口号
	const char *ip = "127.0.0.1";
	unsigned short port = 1412;

	// 这就是stub代理类，帮我们发起rpc请求
	UserService::SRPCClient client(ip, port);

	// example for RPC method call
	// 准备rpc的传入参数
	ReqSignup signup_req;
	// 设置调用rpc方法需要传入的参数
	signup_req.set_username("hahaha");
	signup_req.set_password("123456");

	client.Signup(&signup_req, signup_done);

	wait_group.wait();
	google::protobuf::ShutdownProtobufLibrary();
	return 0;
}

#include "signup.srpc.h"
#include "workflow/WFFacilities.h"

using namespace srpc;

static WFFacilities::WaitGroup wait_group(1);

void sig_handler(int signo)
{
	wait_group.done();
}

class UserServiceServiceImpl : public UserService::Service
{
public:

	// ctx是和workflow对接的
	void Signup(ReqSignup *request, RespSignup *response, srpc::RPCContext *ctx) override
	{
		// TODO: fill server logic here
		std::string user_name = request->username();
		std::string password = request->password();

		std::cout << "username: " << user_name << std::endl;
		std::cout << "password: " << password << std::endl; 

		response->set_code(200);
		response->set_message("好了你已经注册成功了");

		// 通过ctx找到rpcTask所在的序列，当rpcTask所在的序列执行结束后，再回复响应给客户端
		// auto XXXTask = WFTaskFactory::create_mysql_task();		// 假设这里是一个mysql查询任务，得查询到这个人之后才能返回响应
		// 等待这个任务执行结束后再返回结果，因为workflow执行任务是异步的，你提交任务它会立马返回表示提交成功，然后它把任务放到消息队列
		// 里面去慢慢执行，所以这里得等到该任务完成才能返回响应  得看看workflow教程了
		// ctx->get_series()->push_back(XXXTask);
	}
};

int main()
{
	GOOGLE_PROTOBUF_VERIFY_VERSION;
	unsigned short port = 1412;
	SRPCServer server;

	// 注册一个服务
	UserServiceServiceImpl userservice_impl;
	server.add_service(&userservice_impl);

	server.start(port);
	wait_group.wait();
	server.stop();
	google::protobuf::ShutdownProtobufLibrary();
	return 0;
}

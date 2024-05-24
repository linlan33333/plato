#include "gateway/rpc/service/service.h"
#include "config/gateway.h"
#include "netservice.h"
#include <unistd.h>
#include <thread>

void SRPCServerStart(GatewayRpcService* rpc_server)
{
    rpc_server->Start();
}

int main(int argc, char* argv[])
{
    // 加载配置文件读取配置
    if (argc < 2) {
        std::cout << "please enter -i XXX.yaml" << std::endl;
        exit(EXIT_FAILURE);
    }

    // 判断参数合不合规
    int c = 0;
    std::string config_file;    // 存放配置文件的文件名
    while ((c = getopt(argc, argv, "i:")) != -1) {
        switch (c)
        {
        case 'i': {
            config_file = optarg;
            break;
        }
            
        case '?': {     // 当输入的参数中没有这个指令比如-a，-x之类的，就会走这个分支
            std::cout << "invalid args! " << std::endl;
            exit(EXIT_FAILURE);
        }
            
        case ':': {
            std::cout << "need <configfile>! please enter -i XXX.yaml" << std::endl;
            exit(EXIT_FAILURE);
        }
        
        default:
            break;
        }
    }

    // 初始化全局配置
    Conf::Init(config_file);

    muduo::net::EventLoop loop;
    muduo::net::InetAddress addr(GatewayConfig::Get().GetIp(), GatewayConfig::Get().GetPortForNetService());
    NetService net_server(&loop, addr);

    GatewayRpcService rpc_server(&net_server);

    // 先用一个线程运行起来srpc服务器，不然会阻塞主线程导致muduo网络库启动不了
    std::thread run_rpc_server(SRPCServerStart, &rpc_server);

    net_server.Start();
    loop.loop();

    return 0;
}
#include <muduo/net/http/HttpServer.h>
#include <muduo/net/http/HttpRequest.h>
#include <muduo/net/http/HttpResponse.h>
#include <muduo/net/EventLoop.h>
#include "config/conf.h"
#include "config/ipconfig.h"
#include "domain/dispatcher.h"
#include "source/source.h"

#include <iostream>
#include <string>

void onRequest(const muduo::net::HttpRequest& req, muduo::net::HttpResponse* resp)
{
    if (req.path() == "/ip/list")
    {
        resp->setStatusCode(muduo::net::HttpResponse::k200Ok);
        resp->setStatusMessage("OK");
        resp->setContentType("text/html");
        resp->addHeader("Server", "Muduo");
        std::string now = muduo::Timestamp::now().toFormattedString();
        resp->setBody("<html><head><title>This is title</title></head>"
            "<body><h1>Hello</h1>Now is " + now +
            "</body></html>");
    }
    else 
    {
        resp->setStatusCode(muduo::net::HttpResponse::k404NotFound);
        resp->setStatusMessage("Not Found");
        resp->setCloseConnection(true);
    }
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

    Conf::Init(config_file);

    std::cout << IpConfConfig::Get().GetServicePathForIPConf() << std::endl;

    // 这里得先初始化排序大池子
    Dispatcher* dispatcher = new Dispatcher();
    // 再启动服务注册中心客户端
    Source source(dispatcher);
    source.Init();

    muduo::net::EventLoop loop;
    // 注册定时任务，也就是每秒拉取注册中心的最新数据
    // ......

    // 启动HTTP服务器
    muduo::net::HttpServer server(&loop, muduo::net::InetAddress(6789), "dummy");
    server.setHttpCallback(onRequest);
    server.setThreadNum(1);
    server.start();
    loop.loop();
}
#include "state/rpc/service/service.h"
#include "config/conf.h"
#include <unistd.h>

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

    StateRpcService service;
    service.Start();

    return 0;
}
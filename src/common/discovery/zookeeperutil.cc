#include "discovery/zookeeperutil.h"
#include "config/discovery.h"
#include <spdlog/spdlog.h>
#include <semaphore.h>
#include <sstream>
#include <iostream>

#define ZNODE_PATH "/plato/ip_dispatcher"

// 全局的watcher观察期，用于在watcher回调线程中执行，当zkserver给zkclient发送通知时调用
void global_watcher(zhandle_t* zh, int type, int state, const char* path, void* watcherCtx) {
    if (type == ZOO_SESSION_EVENT) {    // 回调的消息类型是与会话相关的消息类型
        if (state == ZOO_CONNECTED_STATE) {    // zkclient和zkserver连接成功
            sem_t* sem = (sem_t*)zoo_get_context(zh);
            sem_post(sem);  // 信号量加一，让主线程继续往下走
        }
    }

    // 回调的消息类型是某个节点的子节点发生变化的消息类型
    if (type == ZOO_CHILD_EVENT && strcmp(path, ZNODE_PATH) == 0) {
        Context* ctx = static_cast<Context*>(watcherCtx);
        // 存储变化之前的子节点列表
        struct String_vector *previous_children = ctx->s_v_ptr;
        // 存储变化后的子节点列表
        struct String_vector current_children;

        // 获取当前子节点列表，并重新设置watcher
        if (ZOK == zoo_wget_children(zh, ZNODE_PATH, global_watcher, ctx, &current_children)) {
            ZkClient* zkcli_ptr = ctx->zk_cli_ptr;
            std::cout << "子节点发生变化" << std::endl;
            // 这行代码出错了，后面再看
            zkcli_ptr->check_and_trigger(zh, previous_children, &current_children);

            // 清理旧列表并更新为最新的子节点列表
            deallocate_String_vector(ctx->s_v_ptr);
            *ctx->s_v_ptr = current_children;
        }
    } 
}   

ZkClient::ZkClient()
    : m_zhandle(nullptr)
{
    watcher_ctx_ = new Context();
    watcher_ctx_->s_v_ptr = new struct String_vector();
    watcher_ctx_->zk_cli_ptr = this;
}

ZkClient::~ZkClient()
{
    if (m_zhandle != nullptr) {
        // 把句柄关闭掉，释放资源
        zookeeper_close(m_zhandle);
    }

    if (watcher_ctx_ != nullptr) {
        delete watcher_ctx_->s_v_ptr;
        delete watcher_ctx_;
    }
}

// 创建zk客户端，从而方便与zk服务器联系
void ZkClient::Start()
{
    // 读取zookeeper配置
    std::string connstr = DiscoveryConfig::Get().GetIpPortForDiscovery();    // 这个格式是zk规定好的，遵守就行

    /**
     * zookeeper_init需要传入的前三个参数，分别是IP地址端口号，监听器触发时的回调函数，会话超时时间，也就是心跳检测超时时间，超过该时间没消息就认为节点挂了
     * 后三个参数不用管，就这么传就行。
     * 
     * zookeeper_mt：多线程版本，这里使用的是该版本
     * 该版本的API客户端程序提供了三个线程：
     * API调用线程：也就是调用zookeeper_init函数的线程
     * 网络I/O线程：专门连接zk服务器的线程，底层使用poll，连接成功后发送心跳消息也是由该线程去做
     * watcher回调线程：当zk服务器响应时，该线程会专门调用global_watcher回调函数
     * 这一句话就干了三件事：1、创建句柄，初始化一些数据  2、发送网络数据给zk服务器  3、创建watcher线程等待zk服务器回信
    */
    m_zhandle = zookeeper_init(connstr.c_str(), global_watcher, 30000, nullptr, watcher_ctx_, 0);

    if (m_zhandle == nullptr) {
        spdlog::error("zookeeper_init error!");
        exit(EXIT_FAILURE);
    }

    sem_t sem;
    sem_init(&sem, 0, 0);
    // 给m_zhandle添加上下文，可以理解为给m_zhandle添加一些额外的信息
    // 由于API调用线程和watcher回调线程之间需要线程同步，等watcher回调线程收到响应后,
    // API调用线程才能接着往下走执行业务函数，所以这里得用信号量同步一下
    zoo_set_context(m_zhandle, &sem);

    sem_wait(&sem);

    // 先获取一下目标路径下的节点有哪些,顺便重新注册一下监听器回调函数
    zoo_wget_children(m_zhandle, ZNODE_PATH, global_watcher, watcher_ctx_, watcher_ctx_->s_v_ptr);
    std::cout << "zookeeper_init success!" << std::endl;
}

// 创建znode节点
void ZkClient::Create(const char *path, const char *data, int datalen, int state)
{
    char path_buffer[128];
    int bufferlen = sizeof(path_buffer);
    int flag;
    // 先判断path表示的znode节点是否存在，如果存在，就不再重复创建了
    flag = zoo_exists(m_zhandle, path, 0, nullptr);
    if (flag == ZNONODE) {      // 如果结点不存在
        // 创建指定path的znode节点
        flag = zoo_create(m_zhandle, path, data, datalen,
            &ZOO_OPEN_ACL_UNSAFE, state, path_buffer, bufferlen);
        if (flag == ZOK) {
            spdlog::info("znode create success... path: {}", path);
        }
        else {
            spdlog::error("flag: {0}; znode create error... path: {1}", flag, path);
            exit(EXIT_FAILURE);
        }
    }
}

// 根据指定的path，获取znode节点的值
std::string ZkClient::GetData(const char *path)
{
    char buffer[64];    // 节点的值存放在这里
    int bufferlen = sizeof(buffer);
    // 同步的方式获取值，获取不到就会一直阻塞
    int flag = zoo_get(m_zhandle, path, 0, buffer, &bufferlen, nullptr);
    if (flag != ZOK) {
        spdlog::error("get znode path error... path: {}", path);
        return "";
    }
    else {
        return buffer;
    }
}

bool ZkClient::GetChildren(const char *path, String_vector *children)
{
    // 调用 ZooKeeper 客户端库接口获取子节点列表
    int flag = zoo_get_children(m_zhandle, path, 0, children);
    
    if (flag != ZOK) {
        // 获取子节点列表失败，返回 false
        spdlog::error("get znode children info error... path: {}", path);
        return false;
    }
    
    // 获取子节点列表成功，返回 true
    return true;
}

void ZkClient::SetChildNodeNumAddCallback(std::function<void(zhandle_t *, const char *, const char *)> func)
{
    child_node_num_add_callback_ = func;
}

void ZkClient::SetChildNodeNumDelCallback(std::function<void(zhandle_t *, const char *)> func)
{
    child_node_num_del_callback_ = func;
}

void ZkClient::check_and_trigger(zhandle_t *zh, String_vector *previous, String_vector *current)
{
    int found;
    for (int i = 0; i < current->count; i++) {
        found = 0;
        for (int j = 0; j < previous->count; j++) {
            if (strcmp(current->data[i], previous->data[j]) == 0) {
                found = 1;
                break;
            }
        }
        if (!found) {
            spdlog::info("Node added: {}", current->data[i]);
            // 组装新增的节点的完整路径
            std::stringstream ss;
            ss << ZNODE_PATH << current->data[i];
            // 装着网关节点的数据
            char node_data[1024];
            int buffer_len = sizeof(node_data);
            if (ZOK == zoo_get(zh, ss.str().c_str(), 0, node_data, &buffer_len, nullptr))
            {
                // 把网关节点的数据传给该回调函数
                child_node_num_add_callback_(zh, current->data[i], node_data);
            }
        }
    }

    for (int j = 0; j < previous->count; j++) {
        found = 0;
        for (int i = 0; i < current->count; i++) {
            if (strcmp(previous->data[j], current->data[i]) == 0) {
                found = 1;
                break;
            }
        }
        if (!found) {
            spdlog::info("Node deleted: {}", previous->data[j]);
            child_node_num_del_callback_(zh, previous->data[j]);
        }
    }
}

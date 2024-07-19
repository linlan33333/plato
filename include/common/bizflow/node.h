#pragma once

#include "bizflow/meta.h"
#include "bizflow/graph.h"
#include <string>
#include <vector>
#include <memory>
#include <functional>
#include <map>
#include <any>

// 出现类之间的循环引用的情况时需要前置申明
class Graph;

// 该类是每个Rpc服务请求节点的实例，需要提前定义好节点的运行逻辑并传入
class Node
{
public:
    Node(std::string node_name);
    Node(std::string node_name, std::shared_ptr<Graph>& graph);

    void SetNodeName(std::string& name);
    std::string& GetNodeName();

    void SetGraph(std::shared_ptr<Graph> graph);
    std::shared_ptr<Graph> GetGraph();

    /// @brief 放入该节点的依赖节点名称，定义依赖关系时请调用该函数
    /// @param name 
    void PushDeps(std::string& name);
    /// @brief 获取该节点的前置节点列表
    /// @return 
    std::vector<std::string>& GetDeps();

    void SetMeta(std::shared_ptr<Meta> meta);
    std::shared_ptr<Meta>& GetMeta();

    void SetServiceFunc(std::function<void()> func);

    /// @brief 运行该节点的接口，需要用户在传入的业务逻辑函数中完成三件事
    /// 1、根据依赖关系自行通过Graph指针拿到输入的CallbackCtx对象
    /// 2、运行中如果有错误，请将错误信息包装成Error对象传给自己的Item对象
    /// 3、运行后完成后请将结果CallbackCtx对象传给自己的Item对象
    void Run();

private:
    std::string node_name_;

    /// @brief 存放该节点的前置节点的名称，为什么是名称？因为Graph操作的是Item，想找到某个Node对应的Item，通过名称的方式最简单，因为Node和Item同样的名字
    std::vector<std::string> deps_;

    /// @brief 该Node节点的Meta对象，其中包含节点运行的控制信息等
    std::shared_ptr<Meta> meta_;

    /// @brief 该节点的业务逻辑函数，输入输出都是CallbackCtx子类对象的指针，需要你在传入函数对象时加工处理
    std::function<void()> service_func_;

    /// @brief 由于同一个Flow对象会创建多个相同的Graph，但每个Graph对象的运行进度不同，因此每个Graph中的Node节点就需要持有自己的Graph对象的指针
    /// 从而能够通过自己的Graph对象拿到前置节点的数据与运行情况等
    /// 使用弱智能指针是为了避免循环引用问题，因为Graph持有Item的强指针，Item持有Node的强指针，如果Node再持有Graph的强指针就没法析构了，而且Graph的生命周期长于Node
    std::weak_ptr<Graph> graph_;
};


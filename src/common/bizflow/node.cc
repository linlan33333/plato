#include "bizflow/node.h"

Node::Node(std::string name)
    : node_name_(name)
{
}


Node::Node(std::string name, std::shared_ptr<Graph>& graph)
    : node_name_(name)
    , graph_(graph)
{
}

void Node::SetNodeName(std::string &name)
{
    node_name_ = name;
}

std::string& Node::GetNodeName()
{
    return node_name_;
}

void Node::SetGraph(std::shared_ptr<Graph> graph)
{
    graph_ = graph;
}

std::shared_ptr<Graph> Node::GetGraph()
{
    std::shared_ptr<Graph> graph = graph_.lock();

    return graph;
}

void Node::PushDeps(std::string &name)
{
    deps_.emplace_back(name);
}

std::vector<std::string>& Node::GetDeps()
{
    return deps_;
}

void Node::SetMeta(std::shared_ptr<Meta> meta)
{
    meta_ = meta;
}

std::shared_ptr<Meta>& Node::GetMeta()
{
    return meta_;
}

void Node::SetServiceFunc(std::function<void()> func)
{
    service_func_ = func;
}

void Node::Run()
{
    service_func_();
}

#include "bizflow/graph.h"
#include "bizflow/engine.h"
#include "bizflow/workpool.h"
#include <spdlog/spdlog.h>
#include "graph.h"

Graph& Graph::AddNode(std::shared_ptr<Node> node)
{
    std::shared_ptr<Item> item(std::make_shared<Item>(node));
    std::string node_name = node->GetNodeName();
    // 将item添加到graph对象中
    item_map_.emplace(node_name, item);

    // 得到该Node节点的入度节点
    std::vector<std::string> deps = node->GetDeps();
    // 如果入度为0，说明该节点是输入节点或者其他非连通节点
    if (deps.size() == 0) 
    {
        // 输入节点没有被初始化过，那么它就是输入节点
        if (first_node_name_.size() == 0) 
        {
            // 注册输入节点
            first_node_name_ = node_name;
        }
        // 否则该节点视为某个非连通节点，图有问题不能构建
        // 添加日志信息，日志功能暂时没做，先打印
        spdlog::error("Graph.cc::AddNode: There cannot be any independent stages except for the first node. Node\'s name is {}", node_name);
        exit(-1);
    }

    // 最后调用该函数添加的节点作为输出节点，因此一直更新最后的节点是谁即可
    last_node_name_ = node_name;
    
    // 从Meta对象中得到该节点的控制信息，这里只有重试次数，以后如果有更多的控制信息可以填写在这里
    item->SetRetryNum(node->GetMeta()->GetRetryNum());

    for (auto& depend_node_name : deps)
    {   
        // 如果该节点的前置节点是自己的话，那肯定不允许，直接退出
        if (depend_node_name == node_name)
        {
            spdlog::error("Graph.cc::AddNode: The node has a dependency on itself. Node\'s name is {}", node_name);
            exit(-1);
        }

        std::shared_ptr<Item> depend_item = GetItem(depend_node_name);
        if (depend_item != nullptr)
        {
            // 把当前节点设置为该前置节点的后继，方便后续运行整个DAG
            depend_item->PushNextItem(item);
        }
        else 
        {
            spdlog::error("The dependent {} is not initialized. There is a cyclic dependency:[{} <- {}] \
                Please ensure that the order of adding nodes during buildgraph follows the precedence order.", depend_node_name, node_name, depend_node_name);
            exit(-1);
        }
    }

    // 设置该Node节点的图对象为自己
    node->SetGraph(std::make_shared<Graph> (this));

    return *this;
}

std::shared_ptr<Item> Graph::GetItem(std::string &node_name)
{
    auto item_pair = item_map_.find(node_name);
    if (item_pair != item_map_.end())
    {
        return item_pair->second;
    }

    return std::shared_ptr<Item>();
}

std::shared_ptr<Item> Graph::GetFinishedItem(std::string &node_name)
{
    std::shared_ptr<Item> item = GetItem(node_name);
    if (item != nullptr)
    {
        bizflow::EventType event = item->GetEvent();
        // 通过item代理的信息检查该节点是不是执行完得到结果了，没有就报错panic掉
        // 这么做的原因很简单：比如转账的RPC请求节点执行前需要先调用查询余额的RPC请求节点数据，获取查询余额后才能执行转账操作
		// 要是转账RPC节点Node去查询余额的RPC请求节点Node中拿余额数据，但查询余额的RPC请求节点没有得到数据结果，那么继续执行下去必出问题
        if (event == bizflow::EventType::ExecOK)
        {
            return item;
        }
        else 
        {
            spdlog::error("The node you obtained has not been completed yet. Node\'s name is {}", node_name);
            exit(-1);
        }
    }

    spdlog::warn("Graph.cc::GetFinishedItem: Can\'t find target item : {}", node_name);
    return std::shared_ptr<Item>();
}

void Graph::SetInput(std::shared_ptr<CallbackCtx> input)
{
    input_ = input;
}

// std::shared_ptr<CallbackCtx> &Graph::GetInput()
// {
//     return input_;
// }

// std::shared_ptr<CallbackCtx> Graph::GetOutput()
// {
//     std::shared_ptr<Item> item = GetFinishedItem(last_node_name_);
//     if (item != nullptr) 
//     {
//         return item->GetOutput();
//     }

//     return std::shared_ptr<CallbackCtx>();
// }

std::shared_ptr<Error>& Graph::GetError()
{
    return error_;
}

void Graph::ExecNext(std::shared_ptr<Item> &item)
{
    for (auto& next_item : item->GetNextItems())
    {
        // 该后继节点的入度减一
        next_item->DecrDepsNum();

        // 如果该节点的入度为0，说明所有前置节点运行完成，可以运行该节点
        if (next_item->CheckDepsNumNonPositive())
        {
            BizFlowWorkPool::Get().Push(std::bind(&Item::Run, next_item));
        }
    }
}

bool Graph::Run()
{
    // 由于有并行运行Flow个数的限制，先让信号量-1
    Engine::Get().DecrFlowParallelNum();

    // 检查输入节点有没有初始化，如果输入节点都没有那肯定是不行的
    if (first_node_name_.size() == 0)
    {
        spdlog::error("Graph.cc::Run: Graph has not been created");
        return false;
    }

    // 检查有没有设置输入参数
    if (input_ == nullptr)
    {
        spdlog::error("Graph.cc::Run: Graph has not set input arguments");
        return false;
    }

    std::shared_ptr<Item> begin_item = GetItem(first_node_name_);

    // 交给线程池运行输入节点
    BizFlowWorkPool::Get().Push(std::bind(&Item::Run, begin_item));
    
    while (true)
    {
        std::string node_name;
        // 阻塞式等待，拿到完成的节点的名字
        channel_.pop(node_name);

        // 获取该节点
        std::shared_ptr<Item> item = GetItem(node_name);

        // 看看该节点运行有没有出错
        switch (item->GetEvent())
        {
        case bizflow::EventType::ExecOK :
        {
            // 如果该节点是最后一个运行的节点，说明整个图运行结束，退出函数
            if (node_name == last_node_name_)
            {
                return true;
            }

            // 不是就运行后继节点
            ExecNext(item);
            break;
        }
        case bizflow::EventType::RetryableError :
        {
            if (!item->CheckRetryNumNonPositive())
            {
                // 这里其实不需要考虑线程安全问题，节点运行完才会走到这里，此时不会有其他线程运行该节点
                item->DecrRetryNum();
                // 重置错误信息，可能下次就运行成功了
                item->GetError()->Reset();
                BizFlowWorkPool::Get().Push(std::bind(&Item::Run, item));
                // 重试就回去继续等待下一个节点运行完
                continue;
            }
            else 
            {
                // 打印错误信息，以后可以改造成分布式链路跟踪的信息
                spdlog::error("Graph.cc::Run: The node {} retry attempts have been exhausted!", node_name);

                // 设置一下发生了什么错误
                error_ = item->GetError();
                // 其他路径上的节点会运行完，但是没有机会运行后继节点，因为不会有执行ExecNext函数的机会 
                return false;
            }
            break;
        }
        case  bizflow::EventType::NonRetryable :
        {
            spdlog::error("Graph.cc::Run: The node {} has happend unretryable error", node_name);

            // 设置一下发生了什么错误
            error_ = item->GetError();   
            // 其他路径上的节点会运行完，但是没有机会运行后继节点，因为不会有执行ExecNext函数的机会 
            return false;
        }
        case bizflow::EventType::AbortErr :
        {
            // 停止其他所有路径上正在运行的节点，不管有没有出结果
            stop_ = true;
            spdlog::error("Graph.cc::Run: The node {} has happend abort error", node_name);
            return false;
        }
        default:
            break;
        }
    }

    // 该Flow运行完成，让控制Flow并行运行数量的信号量+1
    Engine::Get().IncrFlowParallelNum();

    return true;
}   

void Graph::Work(std::shared_ptr<Item> &item)
{
    // 先检查一下有没有发生DAG中某个节点执行出错了，那就需要通知其他所有路径上的节点都停下来不要再执行下去了
    // 因此这里做一步检查是否需要停止继续执行
    if (stop_.load() == true)
    {
        return;
    }

    // 运行该节点
    item->Run();

    std::shared_ptr<Error> error = item->GetError();
    // Node节点运行完都没有设置Error对象，因此没有出错
    if (error == nullptr)
    {
        item->SetEvent(bizflow::EventType::ExecOK);
        return;
    }

    // 拿到该节点的Meta对象
    std::shared_ptr<Meta> meta = item->GetNode()->GetMeta();

    // 如果该错误类型是可重试类型，那么就设置item中的执行信息为发生可重试错误
    if (meta->GetErrorType(*error) == bizflow::ErrorType::RetryErr)
    {
        item->SetEvent(bizflow::EventType::RetryableError);
        return;
    }

    if (meta->GetErrorType(*error) == bizflow::ErrorType::NonRetryErr)
    {
        item->SetEvent(bizflow::EventType::NonRetryable);
        return;
    }

    if (meta->GetErrorType(*error) == bizflow::ErrorType::AbortErr)
    {
        item->SetEvent(bizflow::EventType::AbortErr);
        return;
    }

    // 再检查一次是不是要求停止所有节点运行
    if (stop_.load() == true)
    {
        // 该节点运行完成，将该节点的name放入消费队列中
        channel_.push(item->GetNode()->GetNodeName());  
    }
}

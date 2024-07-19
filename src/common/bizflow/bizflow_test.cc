#include "common/bizflow/engine.h"
#include "common/bizflow/node.h"
#include "bizflow/flow.h"
#include <spdlog/spdlog.h>
#include <iostream>
#include <memory>

// 先定义一些运行过程中会出现的错误
enum class ErrorType
{
    LOGINERROR,     // 模拟登录错误
    GETMESSAGEERROR,    // 获取消息错误
};

// 先创建节点以及输入输出数据对象，节点A的输入类，也是整个图的输入类
struct InputA : public CallbackCtx
{
    // 可以提前定义好字段赋好值，也可以只定义字段，到必要的时候赋值
    std::string nameA = "this is  node A input!";
};

struct OutputA : public CallbackCtx
{
    std::string new_nameA;
};

// B节点的输出类，也是整个图的输出类
struct OutputB : public CallbackCtx
{
    std::string new_nameB;
};

// 继承Flow对象编写构图逻辑
class TestFlow : public Flow
{
public:
    TestFlow(std::string flow_name)
    { 
        name_ = flow_name;
        // 添加自己到Engine中
        // 如果想通过Engine对象直接复用拿到该图对象，那么记得将该对象添加到Engine中存储
        Engine::Get().AddFlow(shared_from_this());
    }

    std::shared_ptr<Graph> BuildGraph() 
    {
        // 创建图对象
        std::shared_ptr<Graph> graph(std::make_shared<Graph> ());
        // // 设置图的输入参数对象
        // std::shared_ptr<CallbackCtx> inputA(std::make_shared<InputA>()); 
        // // 只有起始节点才需要设置输入数据，这个不舍
        // graph->SetInput(inputA);

        // 设置Node的四个属性：获取输入，传入控制对象Meta，传入业务逻辑，添加到图中
        std::shared_ptr<Node> nodeA(std::make_shared<Node> ("nodeA", graph));
        // 设置控制对象Meta
        std::shared_ptr<Meta> metaA(std::make_shared<Meta>());
        Error login_err("login error!", (int)ErrorType::LOGINERROR);
        // 设置该错误类型为可重试错误
        metaA->AddRetryError(login_err);
        nodeA->SetMeta(metaA);

        // 设置业务函数，写法相当丑陋，需要传入Node节点指针本身
        auto nodeA_func = [] (std::shared_ptr<Node> nodeA) {
            // 这是起始Node节点，输入参数从Graph对象中拿
            std::shared_ptr<Graph> graph = nodeA->GetGraph();
            std::shared_ptr<InputA> input;
            if (graph != nullptr)
            {
                // 传入具体的输入类型
                input = graph->GetInput<InputA>();
            }

            std::shared_ptr<Item> item = graph->GetItem(nodeA->GetNodeName());
            // 假设登录失败，就把错误记录下来 
            // item->SetError(std::make_shared<Error>("login error!", (int)ErrorType::LOGINERROR));
            // return;

            // 调用某个业务函数，在这里调用，传入input中列出的参数即可
            std::cout << input->nameA << std::endl;

            // 运行完设置一下输出数据到输出类中，然后传给Item对象
            std::shared_ptr<OutputA> output(std::make_shared<OutputA>());
            output->new_nameA = "node A result";
            // shared_ptr类型的子类指针转化为父类指针可以直接转换
            item->SetOutput(output);
        };

        nodeA->SetServiceFunc(std::bind(nodeA_func, nodeA));

        // 创建NodeB对象
        std::shared_ptr<Node> nodeB(std::make_shared<Node> ("nodeB", graph));
        // 设置控制对象Meta
        std::shared_ptr<Meta> metaB(std::make_shared<Meta>());
        Error get_message_err("get user unread message list error!", (int)ErrorType::GETMESSAGEERROR);
        // 设置该错误类型为可重试错误
        metaB->AddRetryError(get_message_err);
        nodeB->SetMeta(metaB);

        auto nodeB_func = [] (std::shared_ptr<Node> nodeB) {
            // 这是起始Node节点，输入参数从Graph对象中拿
            std::shared_ptr<Graph> graph = nodeB->GetGraph();
            // 调用GetFinishedItem获取前置节点的指针，如果前置节点没有运行完，会返回空指针
            std::shared_ptr<Item> itemA = graph->GetFinishedItem(nodeB->GetNodeName());
            if (itemA == nullptr) 
            {
                // 打印日志之类的
                spdlog::error("can\'t get node A result");
                return;
            }
            // 拿到前置节点的输出
            std::shared_ptr<OutputA> output_A = itemA->GetOutput<OutputA>();

            // 调用业务函数之类的
            std::cout << "A节点的输出数据: " + output_A->new_nameA << std::endl;
            std::shared_ptr<OutputB> output_B(std::make_shared<OutputB>());
            output_B->new_nameB = output_A->new_nameA + " node B result";

            // 设置输出结果
            std::shared_ptr<Item> itemB = graph->GetFinishedItem(nodeB->GetNodeName()); 
            itemB->SetOutput(output_B);
        };

        nodeB->SetServiceFunc(std::bind(nodeA_func, nodeB));

        // 链式调用一直添加即可
        graph->AddNode(nodeA).AddNode(nodeB);

        return graph;
    }
};

int main()
{
    std::shared_ptr<TestFlow> test_flow(std::make_shared<TestFlow>("TestFlow"));
    // 后续使用就可以直接从Engine中获取flow
    
    std::shared_ptr<Graph> graph = test_flow->BuildGraph();

    // 设置输入
    std::shared_ptr<InputA> input(std::make_shared<InputA>());
    graph->SetInput(input);

    // 运行
    graph->Run();

    // 获取输出
    std::shared_ptr<OutputB> output = graph->GetOutput<OutputB>();

    // 查看值
    std::cout << output->new_nameB << std::endl;

    return 0;
}
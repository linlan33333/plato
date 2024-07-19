#pragma once

#include "bizflow/item.h"
#include "bizflow/callbackctx.h"
#include <string>
#include <vector>
#include <unordered_map>
#include <tbb/concurrent_queue.h>

/// @brief Graph类可以有多个相同结构的Graph并发运行互不干扰，因此Graph每次要使用时都需要重新构建一个
class Graph
{
public:
    /// @brief 添加Node节点，该Node节点会被包装成Item存放进来，你可以链式调用放入Node节点
    /// @param node 
    Graph& AddNode(std::shared_ptr<Node> node);

    /// @brief 根据名称查找Node节点的代理对象Item
    /// @return 有返回该对象的指针，没有则返回空指针
    std::shared_ptr<Item> GetItem(std::string& node_name);

    /// @brief 获取Node节点的代理对象Item，在获取之前会判断该Item是否已经运行完成，只有运行完成才会返回其数据，否则返回空指针
    /// @param node_name 
    /// @return 
    std::shared_ptr<Item> GetFinishedItem(std::string& node_name);

    /// @brief 设置输入数据，你需要自定义一个继承自CallbackCtx的子类（最好是struct），然后放入输入参数
    void SetInput(std::shared_ptr<CallbackCtx> input);
    template<typename InputType>
    std::shared_ptr<InputType> GetInput() 
    {
        std::shared_ptr<InputType> input = std::dynamic_pointer_cast<InputType>(input_);
        if (input != nullptr) 
        {
            return input;
        }

        return std::shared_ptr<InputType>();
    }

    /// @brief 获取输出结果，注意请不要将Run函数和本函数放到两个线程中执行，因为如果整个DAG还没有运行出来结果，这个函数并不会自动阻塞
    /// @return 如果没有输出结果或者执行过程中出错，那么返回空指针
    template<typename OutputType>
    std::shared_ptr<OutputType> GetOutput()
    {
        std::shared_ptr<Item> item = GetFinishedItem(last_node_name_);
        if (item != nullptr) 
        {
            return item->GetOutput<OutputType>();
        }

        return std::shared_ptr<OutputType>();
    }

    /// @brief 如果图运行失败，可以调用该函数获取失败信息
    /// @return 
    std::shared_ptr<Error>& GetError();

    /// @brief 执行该节点的后继节点，在执行前会判断该后继节点的入度是否为0，如果为0才会执行
    /// @param node_name 
    void ExecNext(std::shared_ptr<Item>& item);

    /// @brief 运行整个DAG图，运行后请调用GetOutput拿到输出结果
    /// @return 运行成功返回true，失败则返回false
    bool Run();

private:
    void Work(std::shared_ptr<Item>& item);

    std::unordered_map<std::string, std::shared_ptr<Item>> item_map_;

    /// @brief 输入节点的名称，以它找到输入节点的Item
    std::string first_node_name_;
    /// @brief 输出节点的名称，以它找到输出节点的Item
    std::string last_node_name_;

    /// @brief 整张图的输入对象
    std::shared_ptr<CallbackCtx> input_;

    /// @brief 图运行失败时的失败信息
    std::shared_ptr<Error> error_;

    /// @brief 控制图中所有节点是否立即停止运行
    inline static std::atomic_bool stop_ = false;

    /// @brief 如何得知哪个节点已经运行完成，从而调用它的后继节点让它们运行？这里使用生产者消费者队列
    /// 如果某个节点运行完成了，那么该节点将自己的name放到队列里，Graph对象得知有数据后会调用后继节点
    tbb::concurrent_bounded_queue<std::string> channel_;
};


#pragma once

#include "bizflow/node.h"
#include "bizflow/callbackctx.h"
#include <shared_mutex>
#include <atomic>

namespace bizflow
{
    enum class EventType
    {
        ExecOK,             // 执行成功
        RetryableError,     // 发生可重试错误
        NonRetryable,       // 发生不可重试错误
        AbortErr            // 发生终止进程错误
    };
}

/// @brief 该类存储Graph对象运行过程中对应节点的运行状态，Graph通过该类运行Node节点，同时记录该Node节点的运行状态信息
/// 这些运行状态信息是动态变化的，所以要单独抽离出来形成一个类，而Node类存储的是这个节点运行时不变的属性，从而起到复用的效果
/// 后续看看可不可以添加一些分布式链路跟踪指标进去
class Item
{
public:
    Item() = default;
    Item(std::shared_ptr<Node> node);

    void SetNode(std::shared_ptr<Node> node);
    std::shared_ptr<Node>& GetNode();

    /// @brief 设置节点发生的事件
    /// @param event 
    void SetEvent(bizflow::EventType event);
    bizflow::EventType GetEvent();

    void PushNextItem(std::shared_ptr<Item>& next_item);
    std::vector<std::shared_ptr<Item>>& GetNextItems();

    /// @brief 增加未执行的前置依赖数
    void IncrDepsNum();
    void DecrDepsNum();
    /// @brief 判断剩余未运行的前置依赖节点数是否为0
    /// @return 
    bool CheckDepsNumNonPositive();

    /// @brief 设置节点输出结果，是由Node节点运行完拿到自己的Item然后设置进来的
    /// @param output 
    void SetOutput(std::shared_ptr<CallbackCtx> output);
    /// @brief 获取该节点的数据结果
    template<typename OutputType>
    std::shared_ptr<OutputType>& GetOutput()
    {
        std::shared_ptr<OutputType> output = std::dynamic_pointer_cast<OutputType>(output_);
        if (output != nullptr) 
        {
            return output_;
        }

        return std::shared_ptr<OutputType>();
    }

    /// @brief 设置错误信息，是由Node节点运行完拿到自己的Item然后设置进来的
    /// @param error 
    void SetError(std::shared_ptr<Error> error);
    /// @brief 得到错误信息
    /// @return 
    std::shared_ptr<Error>& GetError();

    void SetRetryNum(int retry_num);
    void DecrRetryNum();
    bool CheckRetryNumNonPositive();

    /// @brief 该Item运行，其实就是调用Node的Run方法让Node运行
    void Run();

private:
    /// @brief 管理具体的Node对象，使用shared_ptr，从而复用该Node对象
    std::shared_ptr<Node> node_;

    /// @brief 存储错误信息
    std::shared_ptr<Error> error_;

    /// @brief 该Node节点的所有后继节点
    std::vector<std::shared_ptr<Item>> next_Items_;

    /// @brief 该节点当前未运行完的前置节点数
    /// 这里会不会出现线程安全问题：某一个节点C有两个前驱节点A和B并行执行，结果前驱节点A刚把C入度减一，没进入判断
    /// 此时时间片切换到前驱节点B执行C的入度减一，然后时间片切换回节点A，节点A检查发现可以执行节点C，之后前驱节点B检查也发现可以执行C
    /// 就导致C被执行了两次
    std::atomic_int deps_num_;

    /// @brief Node节点的执行信息
    bizflow::EventType event_type_;

    /// @brief 该节点的输出
    std::shared_ptr<CallbackCtx> output_;

    /// @brief 该节点剩余可重试次数
    std::atomic_int retry_num_;
};
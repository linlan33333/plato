#include "bizflow/item.h"

Item::Item(std::shared_ptr<Node> node)
    : node_(node)
    , deps_num_(0)
{
    // 初始化重试次数
    retry_num_ = node_->GetMeta()->GetRetryNum();
}

void Item::SetNode(std::shared_ptr<Node> node)
{
    node_ = node;
    // 初始化重试次数
    retry_num_ = node_->GetMeta()->GetRetryNum();
}

std::shared_ptr<Node>& Item::GetNode()
{
    return node_;
}

void Item::SetEvent(bizflow::EventType event)
{
    event_type_ = event;
}

bizflow::EventType Item::GetEvent()
{
    return event_type_;
}

void Item::PushNextItem(std::shared_ptr<Item>& next_item)
{
    next_Items_.push_back(next_item);
}

std::vector<std::shared_ptr<Item>>& Item::GetNextItems()
{
    return next_Items_;
}

void Item::IncrDepsNum()
{
    deps_num_.fetch_add(1);
}

void Item::DecrDepsNum()
{
    deps_num_.fetch_sub(1);
}

bool Item::CheckDepsNumNonPositive()
{
    return deps_num_.load() <= 0;
}

void Item::SetOutput(std::shared_ptr<CallbackCtx> output)
{
    output_ = output;
}

// std::shared_ptr<CallbackCtx>& Item::GetOutput()
// {
//     return output_;
// }

void Item::SetError(std::shared_ptr<Error> error)
{
    error_ = error;
}

std::shared_ptr<Error>& Item::GetError()
{
    return error_;
}

void Item::SetRetryNum(int retry_num)
{
    retry_num_.store(retry_num);
}

void Item::DecrRetryNum()
{
    retry_num_.fetch_sub(1);
}

bool Item::CheckRetryNumNonPositive()
{
    return retry_num_.load() <= 0;
}

void Item::Run()
{
    // Node会在自己的业务函数对象中定义好自己需要哪些前置Item的output，或者Graph对象的input作为输入从而运行
    // 因此不用担心Node节点怎么获取输入数据的事情。同理Node运行完会将输出结果赋值到Item对象中
    node_->Run();
}

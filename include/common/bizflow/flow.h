#pragma once

#include "bizflow/graph.h"
#include <string>

/// @brief 如果需要定义某个Flow，请继承该类并重写BuildGraph函数以及Register函数
class Flow : public std::enable_shared_from_this<Flow>
{
public:
    Flow() = default;
    /// @brief 请重写该函数，在其中定义好Node节点的运行逻辑，Node节点的输入输出，Graph的构成
    /// @return 返回创建好的Graph对象的指针
    virtual std::shared_ptr<Graph> BuildGraph() = 0;

    virtual void SetName(std::string& name) { name_ = name; }
    virtual std::string& GetName() { return name_; }

    virtual ~Flow() = default;

protected:
    std::string name_;

private:
    Flow(const Flow&) = delete;
    Flow& operator= (const Flow&) = delete;
};
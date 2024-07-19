#pragma once

#include "conf.h"

class BizFlowConfig
{
public:
    static BizFlowConfig& Get();

    /// @brief 获取配置文件中bizflow的线程池中线程数，由于bizflow运行的节点都是IO密集型任务
    /// 所以这个数量超物理线程数太多问题也不大
    /// @return 
    int GetWorkSize();

    /// @brief 获取配置文件中的最大允许并行运行的flow数量
    /// @return 
    int GetFlowParallelNUm();

private:
    BizFlowConfig() = default;
    BizFlowConfig(const BizFlowConfig&) = delete;
    BizFlowConfig& operator= (const BizFlowConfig&) = delete;
};
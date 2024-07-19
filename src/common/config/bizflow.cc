#include "config/bizflow.h"

BizFlowConfig &BizFlowConfig::Get()
{
    static BizFlowConfig config;
    return config;
}

int BizFlowConfig::GetWorkSize()
{
    return Conf::GetConf()["bizflow"]["worksize"].as<uint32_t>();
}

int BizFlowConfig::GetFlowParallelNUm()
{
    return Conf::GetConf()["bizflow"]["flow_parallel_num"].as<uint32_t>();
}

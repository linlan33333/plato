#include "domain/endpoint.h"
#include <spdlog/spdlog.h>

Endpoint::Endpoint(std::string ip, std::string port)
    : ip_(ip)
    , port_(port)
    , active_score_(0)
    , static_score_(0)
    , stat_window_(std::make_unique<Window> ())
{
}

std::string Endpoint::GetKey()
{
    return ip_ + ":" + port_;
}

double Endpoint::GetActiveScore()
{
    if (active_score_ == 0) 
    {
        spdlog::warn("The active score of endpoint {} is 0", GetKey());
    }
    return active_score_;
}

double Endpoint::GetStaticScore()
{
    if (static_score_ == 0) 
    {
        spdlog::warn("The static score of endpoint {} is 0", GetKey());
    }
    return static_score_;
}

void Endpoint::UpdateStat(State &s)
{
    stat_window_->AppendStat(s);
    // 更新完stat别忘了更新当前窗口的得分
    CalculateScore();
}

void Endpoint::CalculateScore()
{
    active_score_ = stat_window_->GetActiveScore();
    static_score_ = stat_window_->GetStaticScore();
}

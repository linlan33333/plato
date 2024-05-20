#pragma once

#include "domain/window.h"
#include <string>
#include <memory>

class Endpoint
{
public:
    Endpoint(std::string ip, std::string port);

    /// @brief 有时需要查看该endpoint的IP地址等信息，这里以“ip:port”的字符串形式返回结果
    /// @return 
    std::string GetKey();

    double GetActiveScore();
    double GetStaticScore();

    void UpdateStat(State& s);

    void CalculateScore();

private:
    std::string ip_;

    std::string port_;

    double active_score_;

    double static_score_;

    std::unique_ptr<Window> stat_window_;
};
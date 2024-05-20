#pragma once
#include <string>

enum class EventType
{
    ADDNODE,
    DELNODE
};

// 
class Event
{
public:

    Event() = default;
    Event(EventType type, const std::string& ip, const std::string& port, double conn_num = 0, double msg_bytes = 0);

    void SetType(EventType type);
    EventType GetType();

    void SetIp(const std::string& ip);
    std::string GetIp();

    void SetPort(const std::string& port);
    std::string GetPort();

    void SetConnectionNum(double conn_num);
    double GetConnectionNum();

    void SetMessageBytes(double msg_bytes);
    double GetMessageBytes();

    /// @brief 以ip:port的字符串形式返回，如果想设计一个容器装载Event对象，那么key可以用ip:port表示
    /// @return 
    std::string GetKey();

private:
    EventType type_;

    std::string ip_;

    std::string port_;
    
    double connection_num_;

    double message_bytes_;
};
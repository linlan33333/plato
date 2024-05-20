#include "source/event.h"

Event::Event(EventType type, const std::string &ip, const std::string &port, double conn_num, double msg_bytes)
    : type_(type)
    , ip_(ip)
    , port_(port)
    , connection_num_(conn_num)
    , message_bytes_(msg_bytes)
{
}

void Event::SetType(EventType type)
{
    type_ = type;
}

EventType Event::GetType()
{
    return type_;
}

void Event::SetIp(const std::string &ip)
{
    ip_ = ip;
}

std::string Event::GetIp()
{
    return ip_;
}

void Event::SetPort(const std::string &port)
{
    port_ = port;
}

std::string Event::GetPort()
{
    return port_;
}

void Event::SetConnectionNum(double conn_num)
{
    connection_num_ = conn_num;
}

double Event::GetConnectionNum()
{
    return connection_num_;
}

void Event::SetMessageBytes(double msg_bytes)
{
    message_bytes_ = msg_bytes;
}

double Event::GetMessageBytes()
{
    return message_bytes_;
}

std::string Event::GetKey()
{
    return ip_ + ":" + port_;
}

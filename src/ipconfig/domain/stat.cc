#include "domain/stat.h"

State::State(double connect_num, double message_bytes)
    : connect_num_(connect_num)
    , message_bytes_(message_bytes)
{

}
void State::SetConnectNum(double connect_num)
{
    connect_num_ = connect_num;
}

double State::GetConnectNum()
{
    return connect_num_;
}

void State::SetMessagetBytes(double message_bytes)
{
    message_bytes_ = message_bytes;
}

double State::GetMessagetBytes()
{
    return message_bytes_;
}

double State::CalculateActiveScore()
{
    return GetGB();
}

double State::CalculateStaticScore()
{
    return connect_num_;
}

void State::Avg(double num)
{
    connect_num_ /= num;
    message_bytes_ /= num;
}

void State::Add(State &s)
{
    connect_num_ += s.connect_num_;
    message_bytes_ += s.message_bytes_;
}

State &State::operator+=(State &s)
{
    connect_num_ += s.connect_num_;
    message_bytes_ += s.message_bytes_;
    return *this;
}

State &State::operator+(State &s)
{
    connect_num_ += s.connect_num_;
    message_bytes_ += s.message_bytes_;
    return *this;
}

void State::Sub(State &s)
{
    connect_num_ -= s.connect_num_;
    message_bytes_ -= s.message_bytes_;
}

State &State::operator-=(State &s)
{
    connect_num_ -= s.connect_num_;
    message_bytes_ -= s.message_bytes_;
    return *this;
}

State &State::operator-(State &s)
{
    connect_num_ -= s.connect_num_;
    message_bytes_ -= s.message_bytes_;
    return *this;
}

double State::GetGB()
{
    return message_bytes_ /= 1073741824.0;
}

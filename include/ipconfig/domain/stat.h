#pragma once

class State
{
public:
    State() = default;
    State(double connect_num, double message_bytes);

    void SetConnectNum(double connect_num);
    double GetConnectNum();

    void SetMessagetBytes(double message_bytes);
    double GetMessagetBytes();

    /// @brief 计算动态分
    /// @return 
    double CalculateActiveScore();

    /// @brief 计算静态分
    /// @return 
    double CalculateStaticScore();

    /// @brief 为了开闭原则以后添加新的指标时求窗口window的所有Stat对象的均值时不需要修改window的逻辑，
    ///         这里提供好求均值的接口，只需要window对象将所有Stat对象相加，然后调用Avg函数即可得到
    ///         求完均值处理后的Stat对象
    /// @param num 
    void Avg(double num);

    void Add(State& s);
    State& operator+= (State& s);
    State& operator+ (State& s);

    void Sub(State& s);
    State& operator-= (State& s);
    State& operator- (State& s);

    // 把收发消息的总字节数换算成多少GB
    double GetGB();

private:
    // 对于gateway网关机来说，存在不同时期加入进来的物理机，所以机器的配置是不同的，使用负载来衡量会导致偏差。
    // 为更好的应对动态的机器配置变化，我们统计其剩余资源值，来衡量一个机器其是否更适合增加其负载。
    // 这里的数值代表的是，此endpoint对应的机器其，自身剩余的资源指标。
    // 业务上，im gateway 总体持有的长连接数量 的剩余值
    double connect_num_ = 0;

    // 业务上，im gateway 每秒收发消息的总字节数 的剩余值
    double message_bytes_ = 0;
};
#pragma once

#include <muduo/net/Buffer.h>
#include <string>

class Read
{
public:
    static Read& Get();

    /// @brief 针对网关的protobuf序列化后的数据，按照约定好的格式读取消息头、消息体
    /// @param buffer 
    std::string ReadData(muduo::net::Buffer* buffer);

private:
    /// @brief 读取固定长度数据，由于这个固定长度到底是多少不好说，单独抽出来形成一个函数
    /// @param buffer 
    /// @param datalen 
    /// @return 
    std::string ReadFixedData(muduo::net::Buffer* buffer, int datalen);
};
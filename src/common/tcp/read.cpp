#include "tcp/read.h"
#include <spdlog/spdlog.h>
#include <iostream>

Read &Read::Get()
{
    static Read read;
    return read;
}
std::string Read::ReadData(muduo::net::Buffer *buffer)
{
    // 判断数据长度是否超过四字节，如果小于则连固定消息头都读不出来，那还读个屁数据
    while (buffer->readableBytes() < 4) {
        spdlog::info("Readable data length less than 4 bytes, can\'t parse fixed header!");
    }

    // 先取四字节固定消息头数据，解析固定消息头
    std::string fixed_header = buffer->retrieveAsString(4);
    uint32_t len;
    fixed_header.copy((char*)&len, 4, 0);
    std::string data = ReadFixedData(buffer, len);

    return data;
}

std::string Read::ReadFixedData(muduo::net::Buffer *buffer, int datalen)
{
    // 解决TCP拆包问题，如果数据长度小于datalen就循环阻塞，虽然会损耗一些性能，但是问题不大
    while (buffer->readableBytes() < datalen) {
        spdlog::info("Readable data length less than {} bytes, can\'t parse data!", datalen);
    }
    return buffer->retrieveAsString(datalen);
}
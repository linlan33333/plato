#pragma once

#include <string>
#include <chrono>

// 命名空间就设置为文件夹名称吧
namespace cache
{
    // 某个连接的最大消息id，和该连接存储在同一个Redis cluster slot中，后一个占位符是connid，来标识
    // 这是哪一个connid对应的最大消息id
    const std::string MaxClientIDKey = "max_client_id_{%d}_%llu";

    // 某个连接connid对应的最后的消息，会被业务服务器存储在redis中（直接存PushMsg的序列化数据），如果该消息没有超时，
    // 那么state server重启时去读取最后的消息，如果有的话，就拿到消息去恢复定时器，因此怎么去redis
    // 中去取该连接对应的消息，就拿这个key去取，前一个占位符是connid算出来的插槽key，后一个占位符是
    // connid，这样就唯一标识了该消息是属于哪个连接的
    const std::string LastMsgKey = "last_msg_{%d}_%llu";

    // 登录的槽，对应一个set集合
    const std::string LoginSlotSetKey = "login_slot_set_{%d}";

    // 定义时间常量，redis中一些key的过期时间都设为一周，这么写是因为redis-plus-plus中的接口设置超时时间是std::chrono::seconds类型
    const std::chrono::seconds TTL7D = std::chrono::seconds(7 * 24 * 60 * 60);
}
#pragma once

#include <string>
#include <vector>

class MessageDAO
{
public:
    // Get方法 
    uint64_t GetMessageId() const { return message_id_; }
    uint64_t GetUserId() const { return user_id_; }
    std::string GetNickname() const { return nickname_; }
    std::string GetAvatar() const { return avatar_; }
    uint32_t GetType() const { return type_; }
    std::string GetContent() const { return content_; }
    time_t GetTimestamp() const { return timestamp_; }

    // Set方法
    void SetMessageId(uint64_t id) { message_id_ = id; }
    void SetUserId(uint64_t id) { user_id_ = id; }
    void SetNickname(std::string name) { nickname_ = std::move(name); }
    void SetAvatar(std::string img) { avatar_ = std::move(img); }
    void SetType(uint32_t type) { type_ = type; }
    void SetContent(std::string msg_content) { content_ = std::move(msg_content); }
    void SetTimestamp(time_t ts) { timestamp_ = ts; }

private:
    uint64_t message_id_;

    uint64_t user_id_;

    // 发信人的昵称和头像，这么做是为了当群聊中不认识的人出现更新头像之类的情况时，发送消息过来时可以做到延迟更新
    // 不然当它们更新头像之类的操作时还得将这种特殊消息发送给他所加入的所有群聊的所有人，不管认不认识，如果这个人
    // 恶意更新这些信息很快很频繁，会导致消息风暴，对这种更新用户信息的操作进行限制也不现实，所以才想着把这些信息
    // 存储到消息表中
    std::string nickname_;
    std::string avatar_;

    // 消息类型
    uint32_t type_;
    // 消息内容
    std::string content_;

    // 消息发送的时间戳
    time_t timestamp_;
};
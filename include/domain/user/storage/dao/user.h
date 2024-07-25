#pragma once

#include <string>

// 这里面的字段全是数据库表user表中的字段，可以对照user_dto.proto查看
class UserDAO
{
public:
    void SetUserID(uint64_t user_id);
    uint64_t GetUserID() const;

    std::string GetPassword() const;
    void SetPassword(std::string password);

    std::string GetNickname() const;
    void SetNickname(std::string nickname);

    std::string GetAvatar() const;
    void SetAvatar(std::string avatar);

    std::string GetSignature() const;
    void SetSignature(std::string signature);

    std::string GetFontSize() const;
    void SetFontSize(std::string font_size);

    bool GetDarkMode() const;
    void SetDarkMode(bool dark_mode);

    bool GetReceiveNotification() const;
    void SetReceiveNotification(bool receive_notification);

    std::string GetLanguage() const;
    void SetLanguage(std::string language);

    bool GetNotifications() const;
    void SetNotifications(bool notifications);

    std::string GetLocation() const;
    void SetLocation(std::string location);

    int32_t GetAge() const;
    void SetAge(int32_t age);

    std::string GetGender() const;
    void SetGender(std::string gender);

    std::string GetTags() const;
    void setTags(std::string tags);

private:
    uint64_t user_id_;

    /// @brief 用户个人资料信息
    std::string password_;
    std::string nickname_;
    std::string avatar_;
    std::string signature_;

    /// @brief 用户设置信息
    std::string font_size_;
    bool dark_mode_;
    bool receive_notification_;
    std::string language_;
    bool notifications_;

    /// @brief 用户详细资料信息
    std::string location_;
    int32_t age_;
    std::string gender_;
    std::string tags_;
};

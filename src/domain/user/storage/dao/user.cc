#include "user/storage/dao/user.h"
#include "user.h"

void UserDAO::SetUserID(uint64_t user_id)
{
    user_id_ = user_id;
}

uint64_t UserDAO::GetUserID() const
{
    return user_id_;
}

std::string UserDAO::GetPassword() const
{
    return password_;
}

void UserDAO::SetPassword(std::string password)
{
    password_ = password;
}

std::string UserDAO::GetNickname() const
{
    return nickname_;
}

void UserDAO::SetNickname(std::string nickname)
{
    nickname_ = nickname;
}

std::string UserDAO::GetAvatar() const
{
    return avatar_;
}

void UserDAO::SetAvatar(std::string avatar)
{
    avatar_ = avatar;
}

std::string UserDAO::GetSignature() const
{
    return signature_;
}

void UserDAO::SetSignature(std::string signature)
{
    signature_ = signature;
}

std::string UserDAO::GetFontSize() const
{
    return font_size_;
}

void UserDAO::SetFontSize(std::string font_size)
{
    font_size_ = font_size;
}

bool UserDAO::GetDarkMode() const
{
    return dark_mode_;
}

void UserDAO::SetDarkMode(bool dark_mode)
{
    dark_mode_ = dark_mode;
}

bool UserDAO::GetReceiveNotification() const
{
    return receive_notification_;
}

void UserDAO::SetReceiveNotification(bool receive_notification)
{
    receive_notification_ = receive_notification;
}

std::string UserDAO::GetLanguage() const
{
    return language_;
}

void UserDAO::SetLanguage(std::string language)
{
    language_ = language;
}

bool UserDAO::GetNotifications() const
{
    return notifications_;
}

void UserDAO::SetNotifications(bool notifications)
{
    notifications_ = notifications;
}

std::string UserDAO::GetLocation() const
{
    return location_;
}

void UserDAO::SetLocation(std::string location)
{
    location_ = location;
}

int32_t UserDAO::GetAge() const
{
    return age_;
}

void UserDAO::SetAge(int32_t age)
{
    age_ = age;
}

std::string UserDAO::GetGender() const
{
    return gender_;
}

void UserDAO::SetGender(std::string gender)
{
    gender_ = gender;
}

std::string UserDAO::GetTags() const
{
    return tags_;
}

void UserDAO::setTags(std::string tags)
{
    tags_ = tags;
}

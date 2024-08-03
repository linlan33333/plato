#include "common/config/messagedomain.h"
#include "messagedomain.h"

MessageDomainConfig &MessageDomainConfig::Get()
{
    static MessageDomainConfig config;
    return config;
}

std::string MessageDomainConfig::GetServiceName()
{
    return Conf::GetConf()["message_domain"]["writer"]["service_name"].as<std::string>();
}

std::string MessageDomainConfig::GetServiceAddr()
{
    return Conf::GetConf()["message_domain"]["writer"]["service_addr"].as<std::string>();
}

uint32_t MessageDomainConfig::GetServicePort()
{
    return Conf::GetConf()["message_domain"]["writer"]["service_port"].as<uint32_t>();
}

std::string MessageDomainConfig::GetDBHost()
{
    return std::string();
}

std::string MessageDomainConfig::GetUser()
{
    return std::string();
}

std::string MessageDomainConfig::GetPassword()
{
    return std::string();
}

std::string MessageDomainConfig::GetDataBase()
{
    return std::string();
}

uint32_t MessageDomainConfig::GetProtocolDowngradeThreshold()
{
    return Conf::GetConf()["message_domain"]["writer"]["protocol_downgrade_threshold"].as<uint32_t>();
}

uint32_t MessageDomainConfig::GetSuperSessionPushInterval()
{
    return Conf::GetConf()["message_domain"]["writer"]["super_session_push_interval"].as<uint32_t>();
}

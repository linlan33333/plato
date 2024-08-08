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

std::string MessageDomainConfig::GetMySQLHost()
{
    return std::string();
}

std::string MessageDomainConfig::GetMySQLUser()
{
    return std::string();
}

std::string MessageDomainConfig::GetMySQLPassword()
{
    return std::string();
}

std::string MessageDomainConfig::GetMySQLDataBase()
{
    return std::string();
}

std::string MessageDomainConfig::GetTiDBAddr()
{
    return Conf::GetConf()["message_domain"]["writer"]["db"]["TiDB"]["addr"].as<std::string>();
}

uint32_t MessageDomainConfig::GetTiDBPort()
{
    return Conf::GetConf()["message_domain"]["writer"]["db"]["TiDB"]["port"].as<uint32_t>();
}

std::string MessageDomainConfig::GetTiDBUser()
{
    return Conf::GetConf()["message_domain"]["writer"]["db"]["TiDB"]["user"].as<std::string>();
}

std::string MessageDomainConfig::GetTiDBDataBase()
{
    return Conf::GetConf()["message_domain"]["writer"]["db"]["TiDB"]["database"].as<std::string>();
}

uint32_t MessageDomainConfig::GetProtocolDowngradeThreshold()
{
    return Conf::GetConf()["message_domain"]["writer"]["protocol_downgrade_threshold"].as<uint32_t>();
}

uint32_t MessageDomainConfig::GetSuperSessionPushInterval()
{
    return Conf::GetConf()["message_domain"]["writer"]["super_session_push_interval"].as<uint32_t>();
}

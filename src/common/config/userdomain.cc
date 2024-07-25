#include "common/config/userdomain.h"
#include "userdomain.h"

UserDomainConfig &UserDomainConfig::Get()
{
    static UserDomainConfig config;
    return config;
}

std::string UserDomainConfig::GetServiceName()
{
    return Conf::GetConf()["user_domain"]["service_name"].as<std::string>();
}

std::string UserDomainConfig::GetServiceAddr()
{
    return Conf::GetConf()["user_domain"]["service_addr"].as<std::string>();
}

uint32_t UserDomainConfig::GetServicePort()
{
    return Conf::GetConf()["user_domain"]["service_port"].as<uint32_t>();
}

std::string UserDomainConfig::GetDBHost()
{
    return Conf::GetConf()["user_domain"]["db"]["host"].as<std::string>();
}

std::string UserDomainConfig::GetUser()
{
    return Conf::GetConf()["user_domain"]["db"]["user"].as<std::string>();
}

std::string UserDomainConfig::GetPassword()
{
    return Conf::GetConf()["user_domain"]["db"]["password"].as<std::string>();
}

std::string UserDomainConfig::GetDataBase()
{
    return Conf::GetConf()["user_domain"]["db"]["database"].as<std::string>();
}

uint32_t UserDomainConfig::GetThreadNumForWorkPool()
{
    return Conf::GetConf()["user_domain"]["workpool_thread_num"].as<uint32_t>();
}

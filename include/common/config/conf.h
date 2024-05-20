#pragma once

#include <yaml-cpp/yaml.h>
#include <string>

// 由于配置文件可能会换，读取配置文件的第三方库也可能换，所以这里单独抽出来做一个隔离
class Conf
{
public:
    /// @brief 加载配置文件
    /// @param conf_file_path 传入yaml配置文件的路径
    /// @return 
    static Conf& Init(std::string conf_file_path) {
        static Conf conf(conf_file_path);
        return conf;
    }

    /// @brief 获取配置项对象，该对象已经完全解析完数据了
    /// @return 
    static YAML::Node& GetConf() {
        return config;
    }

private:
    Conf(std::string conf_file_path) {
        config = YAML::LoadFile(conf_file_path);
    }

    Conf& operator= (const Conf& conf) = delete;
    Conf(const Conf& conf) = delete;
 
    // 配置项对象
    inline static YAML::Node config;
};
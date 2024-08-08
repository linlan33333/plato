#pragma once

#include <mysql-cppconn/mysqlx/xdevapi.h>
#include <string>
#include <memory>

using VariantType = std::vector<std::variant<bool, int, int64_t, uint32_t, uint64_t, double, std::string>>;

class TiDBCli
{
public:
    static TiDBCli& Get();

    /// @brief 插入数据，传入数据库表名称，因为一个会话对应一个表，还要传入列名和参数值
    /// 注意：该接口一次只能插入一条数据
    /// @param db_name 
    /// @param column 要插入的列名
    /// @param params 对应要插入的参数值
    /// @return 
    bool Insert(std::string& table_name, std::vector<std::string>& column, std::vector<VariantType>& params);

private:
    TiDBCli();
    TiDBCli(const TiDBCli&) = delete;
    TiDBCli& operator=(const TiDBCli&) = delete;

    // 连接TiDB数据库的句柄
    mysqlx::Session connector_;
    // TiDB的消息域数据库名称
    mysqlx::Schema database_;
};
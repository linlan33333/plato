#pragma once

#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <string>
#include <memory>
#include <variant>

using VariantType = std::vector<std::variant<bool, int, int64_t, uint32_t, uint64_t, double, std::string>>;

class MySQLCli
{
public:
    static MySQLCli& Get();

    /// @brief 查询接口，防止sql注入攻击采用参数绑定方式，但是鬼知道会传入什么类型的参数，所以只能用这种方式让vector覆盖所有类型参数
    /// @param query_sql 
    /// @param params 
    /// @return 
    std::shared_ptr<sql::ResultSet> Query(std::string& query_sql, VariantType& params);

    /// @brief 批量创建新用户的接口，由于MySQL Connector/C++本身不支持批量新增操作，所以暂时还只能一个个添加，后续想办法换成mysqlx的api，反正存储层做修改不影响领域层。
    /// @param insert_sql 
    /// @param params_list 
    /// @return 
    bool Create(std::string& insert_sql, std::vector<VariantType>& params_list);

    /// @brief 批量修改用户的接口，由于MySQL Connector/C++本身不支持批量修改操作，所以暂时还只能一个个修改，后续想办法换成其他API
    /// @param insert_sql 
    /// @param params_list 
    /// @return 
    bool Update(std::string& update_sql, std::vector<VariantType>& params_list);

private:
    MySQLCli();
    MySQLCli(const MySQLCli&) = delete;
    MySQLCli& operator=(const MySQLCli&) = delete;

    /// @brief 把params根据其参数类型设置进SQL语句的操作抽象出一个函数
    /// @param pstmt 
    /// @param params 
    void SetParamsToSQL(std::shared_ptr<sql::PreparedStatement>& pstmt, VariantType& params);

    sql::mysql::MySQL_Driver* driver_;
    std::unique_ptr<sql::Connection> connection_;
};
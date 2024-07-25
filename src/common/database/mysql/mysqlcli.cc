#include "database/mysql/mysqlcli.h"
#include "config/userdomain.h"
#include "spdlog/spdlog.h"
#include <cppconn/prepared_statement.h>
#include "mysqlcli.h"

MySQLCli::MySQLCli()
{
    try
    {
        driver_ = sql::mysql::get_mysql_driver_instance();
        connection_.reset(driver_->connect(UserDomainConfig::Get().GetDBHost(), UserDomainConfig::Get().GetUser(), UserDomainConfig::Get().GetPassword()));
        connection_->setSchema(UserDomainConfig::Get().GetDataBase());
    }
    catch(sql::SQLException& e)
    {
        spdlog::error("MySQLCli.cc::MySQLCli: MySQL connect error, {}", e.what());
    }
}

MySQLCli &MySQLCli::Get()
{
    static MySQLCli cli;
    return cli;
}

std::shared_ptr<sql::ResultSet> MySQLCli::Query(std::string &query_sql, VariantType &params)
{
    std::shared_ptr<sql::ResultSet> res;

    try 
    {
        std::shared_ptr<sql::PreparedStatement> pstmt(std::make_unique<sql::PreparedStatement>(connection_->prepareStatement(query_sql)));
        // 把参数装填入SQL语句中
        SetParamsToSQL(pstmt, params);

        // 装入执行结果
        res.reset(pstmt->executeQuery());
    }
    catch (sql::SQLException& e)
    {
        spdlog::error("MySQLCli.cc::Query: MySQL error, error code: {};\n Error info: {};\n SQLState: {}", e.getErrorCode(), e.what(), e.getSQLState());
    }

    return res;
}

bool MySQLCli::Create(std::string &insert_sql, std::vector<VariantType> &params_list)
{
    try
    {
        std::shared_ptr<sql::PreparedStatement> pstmt(std::make_unique<sql::PreparedStatement>(connection_->prepareStatement(insert_sql)));
        
        // 暂时是一行一行地插入新数据，如果后续有批量插入新数据的方式，直接改写这部分逻辑即可
        for (auto& params : params_list)
        {
            // 把参数装填入SQL语句中
            SetParamsToSQL(pstmt, params);

            pstmt->executeUpdate();
        }
    }
    catch(sql::SQLException& e)
    {
        spdlog::error("MySQLCli.cc::Create: MySQL error, error code: {};\n Error info: {};\n SQLState: {}", e.getErrorCode(), e.what(), e.getSQLState());
        return false;
    }
    
    return true;
}

bool MySQLCli::Update(std::string &update_sql, std::vector<VariantType> &params_list)
{
    try
    {
        std::shared_ptr<sql::PreparedStatement> pstmt(std::make_unique<sql::PreparedStatement>(connection_->prepareStatement(update_sql)));
        
        // 暂时是一行一行地插入新数据，如果后续有批量插入新数据的方式，直接改写这部分逻辑即可
        for (auto& params : params_list)
        {
            // 把参数装填入SQL语句中
            SetParamsToSQL(pstmt, params);

            pstmt->executeUpdate();
        }
    }
    catch(sql::SQLException& e)
    {
        spdlog::error("MySQLCli.cc::Update: MySQL error, error code: {};\n Error info: {};\n SQLState: {}", e.getErrorCode(), e.what(), e.getSQLState());
        return false;
    }
    
    return true;
}

void MySQLCli::SetParamsToSQL(std::shared_ptr<sql::PreparedStatement> &pstmt, VariantType &params)
{
    for (size_t i = 0; i < params.size(); i++) {
        if (std::holds_alternative<bool>(params[i])) 
        {
            pstmt->setBoolean(i + 1, std::get<bool>(params[i]));
            continue;
        }
        if (std::holds_alternative<int>(params[i])) 
        {
            pstmt->setInt(i + 1, std::get<int>(params[i]));
            continue;
        }
        if (std::holds_alternative<int64_t>(params[i])) 
        {
            pstmt->setInt64(i + 1, std::get<int64_t>(params[i]));
            continue;
        }
        if (std::holds_alternative<uint32_t>(params[i])) 
        {
            pstmt->setUInt(i + 1, std::get<uint32_t>(params[i]));
            continue;
        }
        if (std::holds_alternative<uint64_t>(params[i])) 
        {
            pstmt->setUInt64(i + 1, std::get<uint64_t>(params[i]));
            continue;
        }
        if (std::holds_alternative<double>(params[i])) 
        {
            pstmt->setDouble(i + 1, std::get<double>(params[i]));
            continue;
        }
        if (std::holds_alternative<std::string>(params[i])) 
        {
            pstmt->setString(i + 1, std::get<std::string>(params[i]));
            continue;
        }
    }
}

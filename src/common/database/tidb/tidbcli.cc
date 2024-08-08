#include "common/database/tidb/tidbcli.h"
#include "common/config/messagedomain.h"
#include <spdlog/spdlog.h>

TiDBCli &TiDBCli::Get()
{
    static TiDBCli cli;
    return cli;
}

TiDBCli::TiDBCli()
    : connector_(MessageDomainConfig::Get().GetTiDBAddr(), MessageDomainConfig::Get().GetTiDBPort(), 
        MessageDomainConfig::Get().GetTiDBUser(), "")
    , database_(connector_.getSchema(MessageDomainConfig::Get().GetTiDBDataBase()))
{
}

bool TiDBCli::Insert(std::string &table_name, std::vector<std::string>& column, std::vector<VariantType> &params)
{
    if (column.size() != params.size())
    {
        spdlog::error("TiDBCli.cc::Insert: The number of column is not equal to params!");
        return false;
    }

    // 拿到数据库表
    mysqlx::Table table = database_.getTable(table_name);

    try
    {
        table.insert(column.begin(), column.end()).values(params.begin(), params.end()).execute();
    }
    catch(const std::exception& e)
    {
        spdlog::error("TiDBCli.cc::Insert: Insert data failed!");
        return false;
    }
    

    return true;
}

// 插入多行数据的方法，如果好使就使用这种
// bool TiDBCli::Insert(std::string &table_name, std::vector<std::string>& columns, std::vector<std::vector<VariantType>> &data_rows)
// {
//     if (columns.size() != params.size())
//     {
//         spdlog::error("TiDBCli.cc::Insert: The number of columns is not equal to the number of parameters!");
//         return false;
//     }

//     // 拿到数据库表
//     mysqlx::Table table = database_.getTable(table_name);

//     try
//     {
//         auto insert_stmt = table.insert(columns.begin(), columns.end()); // 开始插入语句，先写好列名

//         // 遍历每一行数据
//         for (const auto &row : data_rows) {
//             insert_stmt.values();
//             // 遍历行中的每一个值
//             for (const auto &value : row) {
//                 // 使用 std::visit 或 if-else 结构来确定值的类型并插入
//                 std::visit([row](auto&& arg) {
//                     using T = std::decay_t<decltype(arg)>;
//                     if constexpr (std::is_same_v<T, std::string>) {
//                         insert_stmt.string(arg);
//                     } else if constexpr (std::is_same_v<T, int>) {
//                         insert_stmt.int_(arg);
//                     } else if constexpr (std::is_same_v<T, double>) {
//                         insert_stmt.double_(arg);
//                     }
//                 }, value);
//             }
//         }

//         // 执行插入语句
//         insert_stmt.execute();
//     }
//     catch(const std::exception& e)
//     {
//         spdlog::error("TiDBCli.cc::Insert: Insert data failed! Error: {}", e.what());
//         return false;
//     }

//     return true;
// }
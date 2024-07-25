#include "user/storage/model/usermodel.h"
#include "common/database/mysql/mysqlcli.h"
#include "usermodel.h"

std::vector<UserDAO> UserModel::Query(std::vector<uint64_t>& userID_list)
{
    std::vector<UserDAO> res;

    std::string query_sql = "select * from user where id=?";

    for (auto& user_id : userID_list)
    {
        // 这个类型在mysqlcli.h类中定义的
        VariantType params;
        params.push_back(user_id);
        // 去数据库中查询
        std::shared_ptr<sql::ResultSet> query_result = MySQLCli::Get().Query(query_sql, params);

        // 处理查询结果，将其转化为UserDAO
        while (query_result->next())
        {
            UserDAO user_dao;
            user_dao.SetUserID(query_result->getUInt64("id"));
            user_dao.SetNickname(query_result->getString("password"));
            user_dao.SetAvatar(query_result->getString("avatar"));
            user_dao.SetSignature(query_result->getString("signature"));
            user_dao.SetFontSize(query_result->getString("font_size"));
            user_dao.SetDarkMode(query_result->getBoolean("darkmode"));
            user_dao.SetReceiveNotification(query_result->getBoolean("receive_notification"));
            user_dao.SetLanguage(query_result->getString("language"));
            user_dao.SetNotifications(query_result->getBoolean("notifications"));
            user_dao.SetLocation(query_result->getString("location"));
            user_dao.SetAge(query_result->getInt("age"));
            user_dao.SetGender(query_result->getString("gender"));
            user_dao.setTags(query_result->getString("tags"));

            res.emplace_back(std::move(user_dao));
        }
    }

    return res;
}

bool UserModel::Create(std::vector<UserDAO> &user_dao_list)
{
    std::string insert_sql = "insert into user(id, password, avartar, signature, font_size, darkmode, receive_notification, language, notifications, location, age, gender, tags) \
                                    values (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)";

    std::vector<VariantType> params_list;
    for (auto& user_dao : user_dao_list)
    {
        VariantType params;

        params.emplace_back(user_dao.GetUserID());
        params.emplace_back(user_dao.GetPassword());
        params.emplace_back(user_dao.GetAvatar());
        params.emplace_back(user_dao.GetSignature());
        params.emplace_back(user_dao.GetFontSize());
        params.emplace_back(user_dao.GetDarkMode());
        params.emplace_back(user_dao.GetReceiveNotification());
        params.emplace_back(user_dao.GetLanguage());
        params.emplace_back(user_dao.GetNotifications());
        params.emplace_back(user_dao.GetLocation());
        params.emplace_back(user_dao.GetAge());
        params.emplace_back(user_dao.GetGender());
        params.emplace_back(user_dao.GetTags());
        

        params_list.emplace_back(std::move(params));
    }

    return MySQLCli::Get().Create(insert_sql, params_list);
}

bool UserModel::Update(std::vector<UserDAO> &user_dao_list)
{
    // 理论上应当是根据我传入的参数有哪些，智能生成sql语句才对，不应该是每次更新全部字段都要重新设置，这样会导致有些已经设置数据的字段由于
    // 这里没有传入参数给改成空值啥的，这样做就不合理，后续想想办法怎么改这个东西。
    std::string update_sql = "update user set password=?, avartar=?, signature=?, font_size=?, darkmode=?, receive_notification=?, language=?, notifications=?, location=?, age=?, gender=?, tags=?) \
                                    where id=?";

    std::vector<VariantType> params_list;
    for (auto& user_dao : user_dao_list)
    {
        VariantType params;

        params.emplace_back(user_dao.GetPassword());
        params.emplace_back(user_dao.GetAvatar());
        params.emplace_back(user_dao.GetSignature());
        params.emplace_back(user_dao.GetFontSize());
        params.emplace_back(user_dao.GetDarkMode());
        params.emplace_back(user_dao.GetReceiveNotification());
        params.emplace_back(user_dao.GetLanguage());
        params.emplace_back(user_dao.GetNotifications());
        params.emplace_back(user_dao.GetLocation());
        params.emplace_back(user_dao.GetAge());
        params.emplace_back(user_dao.GetGender());
        params.emplace_back(user_dao.GetTags());
        // userID作为查询索引，需要放到最后面
        params.emplace_back(user_dao.GetUserID());

        params_list.emplace_back(std::move(params));
    }

    return MySQLCli::Get().Update(update_sql, params_list);
}
#include "storage/model/messagemodel.h"
#include "common/database/tidb/tidbcli.h"

bool MessageModel::AddMessage(uint64_t session_id, MessageDAO &message_dao)
{
    // 数据库表名假设就叫session_id_ + session_id吧
    std::string table_name = "session_id_" + std::to_string(session_id);

    // 数据库表的属性字段，需要根据MessageDAO中哪些字段有数据来添加，防止没有数据的字段添加进去把表中原来的数据给覆盖了
    // 这里其实MessageDAO中的所有字段都有数据才对
    std::vector<std::string> column_names;
    std::vector<VariantType> params;

    column_names.emplace_back("id");
    params.emplace_back(message_dao.GetMessageId());

    column_names.emplace_back("user_id");
    params.emplace_back(message_dao.GetUserId());

    // 如果你觉得nickname这个字段设计的不合理，不传就行
    std::string nickname = message_dao.GetNickname();
    if (nickname.size() != 0)
    {
        column_names.emplace_back("nickname");
        params.emplace_back(std::move(nickname));
    }

    // 如果你觉得avatar这个字段设计的不合理，不传就行
    std::string avatar = message_dao.GetAvatar();
    if (avatar.size() != 0)
    {
        column_names.emplace_back("avatar");
        params.emplace_back(std::move(avatar));
    }

    column_names.emplace_back("type");
    params.emplace_back(message_dao.GetType());

    column_names.emplace_back("content");
    params.emplace_back(message_dao.GetContent());

    column_names.emplace_back("create_time");
    params.emplace_back(message_dao.GetTimestamp());

    return TiDBCli::Get().Insert(table_name, column_names, params);
}
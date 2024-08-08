#pragma once

#include "storage/dao/message.h"
#include "storage/model/messagemodel.h"
#include "common/idl/domain/message/message_dto.pb.h"

class Storage
{
public:
    static Storage& Get();

    /// @brief 调用存储层的接口存储新消息
    /// @param session_id 
    /// @param message_dto 
    /// @returns 插入数据成功就返回true
    bool InsertMessage(uint64_t session_id, message::MessageDTO& message_dto);

private:
    Storage() = default;
    Storage(const Storage&) = delete;
    Storage& operator=(const Storage&) = delete;

    /// @brief 将MessageDTO对象转换到传进来的MessageDAO对象中
    /// @param message_dto 
    /// @param message_dao 
    void ConvertMessageDTOToDAO(message::MessageDTO& message_dto, MessageDAO&  message_dao);

    /// @brief 操作数据库查询的接口对象
    MessageModel message_model_;
};
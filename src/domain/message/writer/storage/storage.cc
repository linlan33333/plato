#include "writer/storage/storage.h"

Storage &Storage::Get()
{
    static Storage storage;

    return storage;
}

bool Storage::InsertMessage(uint64_t session_id, message::MessageDTO &message_dto)
{
    MessageDAO message_dao;
    ConvertMessageDTOToDAO(message_dto, message_dao);

    return message_model_.AddMessage(session_id, message_dao);
}

void Storage::ConvertMessageDTOToDAO(message::MessageDTO &message_dto, MessageDAO &message_dao) 
{
    message_dao.SetMessageId(message_dto.messageid());
    message_dao.SetUserId(message_dto.userid());
    message_dao.SetAvatar(message_dto.information().nickname());
    message_dao.SetAvatar(message_dto.information().avatar());
    message_dao.SetType(message_dto.type());
    message_dao.SetContent(message_dto.content());
    message_dao.SetTimestamp(message_dto.timestamp());
}
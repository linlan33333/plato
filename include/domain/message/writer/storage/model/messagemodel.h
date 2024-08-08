#pragma once

#include "storage/dao/message.h"
#include <vector>

class MessageModel
{
public:
    bool AddMessage(uint64_t session_id, MessageDAO& message_dao);
};
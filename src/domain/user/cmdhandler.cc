#include "cmdhandler.h"

CmdHandler &CmdHandler::Get()
{
    static CmdHandler handler;
    return handler;
}

user::UserDTO CmdHandler::QueryUserInformation(uint64_t userID)
{
    // 整个UserDTO是存储层返回的数据，因此这里只要调用存储层的函数即可
    
}
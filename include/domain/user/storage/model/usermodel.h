#pragma once

#include "storage/dao/user.h"
#include <vector>

// user表的数据操作类
class UserModel
{
public:
    std::vector<UserDAO> Query(std::vector<uint64_t>& userID_list);

    /// @brief 底层调用的MySQL Connectior/C++本身不支持批量创建新用户，所以这个接口本质还是一个个创建的
    /// @param user_dao 
    /// @return 
    bool Create(std::vector<UserDAO>& user_dao_list);

    /// @brief 底层调用的MySQL Connectior/C++本身不支持批量更新用户信息，所以这个接口本质还是一个个修改的
    /// @param user_dao_list 
    /// @return 
    bool Update(std::vector<UserDAO>& user_dao_list);
};
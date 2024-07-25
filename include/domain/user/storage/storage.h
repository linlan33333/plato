#pragma once

#include "common/idl/domain/user/user_dto.pb.h"
#include "user/options.h"
#include "common/cache/manager.h"
#include "user/storage/model/usermodel.h"
#include <map>

/// @brief 提供查询各种UserDTO的接口
class Storage
{
public:
    static Storage& Get();

    /// @brief 查询用户数据，注意这里不区分查询用户个人资料还是用户设置啥的，因为存储层会将要查询的用户信息DAO整个缓存到redis中
    /// 因为保不准用户查询完个人资料后还要查询详细资料，所以单独给查询用户个人资料啥的DTO各设计一个接口的话可能会导致接口调用
    /// 频繁的问题，还不如一趟把用户数据全查出来缓存到redis中
    /// @param options  批量查询 
    /// @return 
    std::map<uint64_t, user::UserDTO> QueryUsers(std::vector<std::pair<uint64_t, Options>>& options);

    /// @brief 创建用户
    /// @param  
    /// @return 
    bool CreateUsers(std::vector<user::UserDTO>& user_dto_list);

    /// @brief 修改用户信息
    /// @param user_dto_list 
    /// @return 
    bool UpdateUsers(std::vector<user::UserDTO>& user_dto_list);

private:
    Storage();
    Storage(const Storage&) = delete;
    Storage& operator=(const Storage&) = delete;

    /// @brief 根据要查询的DTO修改整理UserDTO，只保留要查询的DTO，其他的去掉，节省网络带宽资源，但是做法比较呆，看看有什么优化的方法
    /// @param modes 
    /// @param user_dto 
    void SetUserDTOByMode(std::vector<UserDomain::Mode>& modes, user::UserDTO& user_dto);

    /// @brief 该函数将UserDAO对象转换进传入的UserDTO对象中，还有一个DeviceDAO转换进传入的UserDTO对象函数暂时没有做
    /// @param user_dao 
    /// @param user_dto 
    void ConvertUserDAOToDTO(UserDAO& user_dao, user::UserDTO& user_dto);

    /// @brief 该函数将传入的UserDTO对象转换成UserDAO对象
    /// @param user_dto 
    /// @param user_dao 
    void ConvertUserDTOToDAO(user::UserDTO& user_dto, UserDAO& user_dao);

    /// @brief 操作数据库查询的接口对象
    UserModel user_model_;

    /// @brief 操作缓存的接口对象
    CacheManager cache_manager_;
};
#include "user/storage/storage.h"

#include "common/cache/const.h"
#include "user/storage/dao/user.h"
#include "user/workpool.h"
#include <spdlog/spdlog.h>
#include <algorithm>
#include "storage.h"

Storage &Storage::Get()
{
    static Storage storage;

    return storage;
}

std::map<uint64_t, user::UserDTO> Storage::QueryUsers(std::vector<std::pair<uint64_t, Options>>& options)
{
    // 说明以下查询的过程：因为返回的数据按DTO划分，所以查用户的数据肯定不是将所有字段都查出来然后返回一个
    // 总的UserDTO，而是按照options中给出要查询的DTO去把数据组织起来，但是查数据库表还是查整个User表的字段
    // 然后把所有字段数据全部存储到Redis缓存中
    std::map<uint64_t, user::UserDTO> res;

    // 存储redis缓存中未命中的userID
    std::vector<uint64_t> miss_user;
    // 存储去redis中查询的user信息转化的key
    std::vector<std::string> keys;

    //////////////////////////////////////////////// 先查询缓存
    // 先将所有要查询的key都存放起来，待会采用pipeline的形式查询，加快速度
    for (auto& option_pair : options) 
    {
        char key[100];
        sprintf(key, cache::UserDomainCacheKey.c_str(), option_pair.first);
        keys.emplace_back(std::move(key));
    }
    // 查询缓存中有没有对应的UserDTO数据，注意：存到缓存中的UserDTO是整个user表所有字段转换称UserDTO往里面存
    std::vector<std::string> cache_table = cache_manager_.Mget(keys);
    for (int i = 0; i < cache_table.size(); i++) 
    {
        // 如果该key在redis中没查到缓存数据，那么就需要往下从数据库中查了，存储到miss_user中
        if (cache_table[i].size() == 0) 
        {
            miss_user.push_back(options[i].first);
        }
        else 
        {
            // 反序列化UserDTO
            user::UserDTO user_dto;
            if (!user_dto.ParseFromString(cache_table[i])) 
            {
                spdlog::warn("Storage.cc::QueryUsers: Parse from string error!");
                // 如果序列化失败，就去数据库中查，查完存回redis中覆盖原数据
                miss_user.push_back(options[i].first);

                continue;
            }

            res[options[i].first] = user_dto;
        }
    }

    //////////////////////////////////////////////////// 缓存中没有查到的数据去查DB
    if (miss_user.size() == 0)
    {
        return res;
    }

    std::vector<UserDAO> users;
    std::vector<std::pair<uint64_t, user::UserDTO>> miss_user_dto;
    // TODO: 这里没有查询device信息，校招在即实在是来不及做多端登录的业务，先放一下
    // 查询数据库，将所有miss_user的全查出来
    // TODO: 这里并不是批量查询多行数据，本质上还是一行行查询，一定要优化性能改成批量查询
    users = user_model_.Query(miss_user);
    // 转化为UserDTO
    for (auto& user : users)
    {
        user::UserDTO user_dto;
        ConvertUserDAOToDTO(user, user_dto);
        uint64_t user_id = user.GetUserID();
        res[user_id] = user_dto;
        miss_user_dto.emplace_back(std::make_pair(user_id, std::move(user_dto)));
    }
    //////////////////////////////////////////////////// 将数据存到redis缓存中，这件事异步去做
    WorkPool::Get().Push([miss_user_dto, this] () {
        // 待会扔到redis缓存中
        std::vector<std::pair<std::string, std::string>> kv_pairs;

        for (int i = 0; i < miss_user_dto.size(); i++) 
        {
            std::string user_dto_str;
            // 将UserDTO序列化后再存到redis中
            if (!miss_user_dto[i].second.SerializeToString(&user_dto_str))
            {
                spdlog::warn("Storage.cc::QueryUsers: Serialize to string error!");
                continue;
            }

            // 存储的key
            char key[100];
            sprintf(key, cache::UserDomainCacheKey.c_str(), miss_user_dto[i].first);

            kv_pairs.emplace_back(std::make_pair(std::move(key), std::move(user_dto_str)));
        }

        cache_manager_.Mset(kv_pairs, cache::TTL1D);
    });

    // 这里应当根据业务需要拿到需要查询的DTO放到UserDTO中
    for (int i = 0; i < options.size(); i++)
    {
        SetUserDTOByMode(options[i].second.GetModeList(), res[i]);
    }

    return res;
}

bool Storage::CreateUsers(std::vector<user::UserDTO>& user_dto_list)
{
    // TODO: 这里要有一个限流组件，在后面的基础设施层会详细讲解
	// 写DB一定要有一个限流的DB组件

    std::vector<UserDAO> user_dao_list;
    // 新创建的用户需要去缓存中删掉已有的空用户，因为为了防止缓存穿透，可能会在redis中添加这种空用户
    // 因此当这些用户真正创建账号时就需要去缓存中删掉对应的空用户
    std::vector<std::string> keys;
    for (auto& user_dto : user_dto_list)
    {
        UserDAO user_dao;
        ConvertUserDTOToDAO(user_dto, user_dao);
        char key[100];
        sprintf(key, cache::UserDomainCacheKey.c_str(), user_dto.userid());
        keys.emplace_back(key);
    }

    // TODO: 这里并不是批量创建多个用户，本质上还是一个个用户创建，一定要优化性能改成批量创建
    bool res = user_model_.Create(user_dao_list);
    if (!res)
    {
        return false;
    }

    // 删除缓存
    cache_manager_.Mdel(keys);

    // 创建事件
    // TODO: 领域事件后面会在异步任务框架处完善业务逻辑
    // 比如什么多个APP账号关联、头像审核啥的

    return true;
}

bool Storage::UpdateUsers(std::vector<user::UserDTO> &user_dto_list)
{
    // TODO: 这里要有一个限流组件，在后面的基础设施层会详细讲解
	// 写DB一定要有一个限流的DB组件

    std::vector<UserDAO> user_dao_list;
    // 新创建的用户需要去缓存中删掉已有的空用户，因为为了防止缓存穿透，可能会在redis中添加这种空用户
    // 因此当这些用户真正创建账号时就需要去缓存中删掉对应的空用户
    std::vector<std::string> keys;
    for (auto& user_dto : user_dto_list)
    {
        UserDAO user_dao;
        ConvertUserDTOToDAO(user_dto, user_dao);
        char key[100];
        sprintf(key, cache::UserDomainCacheKey.c_str(), user_dto.userid());
        keys.emplace_back(key);
    }

    // TODO: 这里并不是批量修改多个用户，本质上还是一个个用户修改，一定要优化性能改成批量修改
    bool res = user_model_.Create(user_dao_list);
    // 这里有一个小优化，就是出现err可以缓存一个空结果
    if (!res)
    {
        return false;
    }

    // 删除缓存，旁路模式保证缓存数据一致性
    cache_manager_.Mdel(keys);

    return true;
}

void Storage::SetUserDTOByMode(std::vector<UserDomain::Mode> &modes, user::UserDTO &user_dto)
{
    if (std::find(modes.begin(), modes.end(), UserDomain::Mode::INFORMATION) == modes.end())
    {
        user_dto.clear_information();
    }

    if (std::find(modes.begin(), modes.end(), UserDomain::Mode::SETTING) == modes.end())
    {
        user_dto.clear_setting();
    }

    if (std::find(modes.begin(), modes.end(), UserDomain::Mode::PROFILE) == modes.end())
    {
        user_dto.clear_pprofile();
    }
}

void Storage::ConvertUserDAOToDTO(UserDAO &user_dao, user::UserDTO& user_dto)
{
    user::InformationDTO* info_dto = user_dto.mutable_information();
    info_dto->set_nickname(user_dao.GetNickname());
    info_dto->set_password(user_dao.GetPassword());
    info_dto->set_avatar(user_dao.GetAvatar());
    info_dto->set_signature(user_dao.GetSignature());

    user::SettingDTO* setting_dto = user_dto.mutable_setting();
    setting_dto->set_fontsize(user_dao.GetFontSize());
    setting_dto->set_darkmode(user_dao.GetDarkMode());
    setting_dto->set_receivenotification(user_dao.GetReceiveNotification());
    setting_dto->set_language(user_dao.GetLanguage());
    setting_dto->set_notifications(user_dao.GetNotifications());
    
    user::ProfileDTO* profile_dto = user_dto.mutable_pprofile();
    profile_dto->set_location(user_dao.GetLocation());
    profile_dto->set_age(user_dao.GetAge());
    profile_dto->set_gender(user_dao.GetGender());
    profile_dto->set_tags(user_dao.GetTags());
}

void Storage::ConvertUserDTOToDAO(user::UserDTO &user_dto, UserDAO &user_dao)
{
    user_dao.SetUserID(user_dto.userid());

    user_dao.SetNickname(user_dto.information().nickname());
    user_dao.SetPassword(user_dto.information().password());
    user_dao.SetAvatar(user_dto.information().avatar());
    user_dao.SetSignature(user_dto.information().signature());

    user_dao.SetFontSize(user_dto.setting().fontsize());
    user_dao.SetDarkMode(user_dto.setting().darkmode());
    user_dao.SetReceiveNotification(user_dto.setting().receivenotification());
    user_dao.SetLanguage(user_dto.setting().language());
    user_dao.SetNotifications(user_dto.setting().notifications());

    user_dao.SetLocation(user_dto.pprofile().location());
    user_dao.SetAge(user_dto.pprofile().age());
    user_dao.SetGender(user_dto.pprofile().gender());
    user_dao.setTags(user_dto.pprofile().tags());
}

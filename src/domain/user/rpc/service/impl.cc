#include "user/rpc/service/impl.h"
#include "user/storage/storage.h"
#include "user/options.h"
#include "common/grpc/domain/code.h"
#include "impl.h"

grpc::Status UserDomainRpcServiceImpl::QueryUsers(grpc::ServerContext *context, const UserDomain::QueryUsersRequest *request, UserDomain::QueryUsersResponse *response)
{
    // 包装好批量查询的查询选项
    std::vector<std::pair<uint64_t, Options>> options;
    for (auto& opts_pair : request->opts())
    {
        // 用指针指向QueryUserOption对象，避免值拷贝操作
        const UserDomain::QueryUserOption* query_option = &opts_pair.second;
        // 组装Options对象
        Options opt;
        for (int i = 0; i < query_option->deviceidlist_size(); i++)
        {
            opt.PushDeviceID(query_option->deviceidlist(i));
        }
        opt.SetAllDevice(query_option->alldevice());
        opt.SetActiveDevice(query_option->activedevice());
        if (query_option->mode().device())
        {
            opt.PushMode(UserDomain::Mode::DEVICE);
        }
        if (query_option->mode().setting())
        {
            opt.PushMode(UserDomain::Mode::SETTING);
        }
        if (query_option->mode().information())
        {
            opt.PushMode(UserDomain::Mode::INFORMATION);
        }
        if (query_option->mode().profile())
        {
            opt.PushMode(UserDomain::Mode::PROFILE);
        }
        options.emplace_back(std::make_pair(opts_pair.first, std::move(opt)));
    }

    // 调用查询接口拿到结果
    std::map<uint64_t, user::UserDTO> user_dto_list = Storage::Get().QueryUsers(options);

    // 将结果放到response中
    for (auto& user_dto_pair : user_dto_list)
    {
        (*response->mutable_users())[user_dto_pair.first] = user_dto_pair.second;
    }

    // TODO: 没有设置base字段，个人没实习过没接触过流量治理等操作，以后补充上base字段

    return grpc::Status::OK;
}

grpc::Status UserDomainRpcServiceImpl::CreateUsers(grpc::ServerContext *context, const UserDomain::CreateUsersRequest *request, UserDomain::CreateUsersResponse *response)
{
    // 将批量创建的用户DTO打包到数组中
    std::vector<user::UserDTO> user_dto_list;
    for (auto& user_dto : request->users())
    {
        user_dto_list.emplace_back(user_dto);
    }

    bool res = Storage::Get().CreateUsers(user_dto_list);

    // 流量治理之类的base没有设置，目前也没有实现流量治理的相关功能
    if (res)
    {
        response->set_code(Domain::Code::SUCCESS);
        response->set_msg("CreateUsersRequest query success");
    }
    else 
    {
        response->set_code(Domain::Code::CREATEUSERERROR);
        response->set_msg("CreateUsersRequest query failed");
    }

    return grpc::Status::OK;
}

grpc::Status UserDomainRpcServiceImpl::UpdateUsers(grpc::ServerContext *context, const UserDomain::UpdateUsersRequest *request, UserDomain::UpdateUsersResponse *response)
{
    // 将批量更新的用户DTO打包到数组中
    std::vector<user::UserDTO> user_dto_list;
    for (auto& user_dto : request->users())
    {
        user_dto_list.emplace_back(user_dto);
    }

    bool res = Storage::Get().UpdateUsers(user_dto_list);

    // 流量治理之类的base没有设置，目前也没有实现流量治理的相关功能
    if (res)
    {
        response->set_code(Domain::Code::SUCCESS);
        response->set_msg("UpdateUsersRequest query success");
    }
    else 
    {
        response->set_code(Domain::Code::UPDATEUSERERROR);
        response->set_msg("UpdateUsersRequest query failed");
    }

    return grpc::Status::OK;
}
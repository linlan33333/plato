#pragma once

#include <grpcpp/grpcpp.h>
#include "common/grpc/domain/user/user.grpc.pb.h"

class UserDomainRpcServiceImpl final : public UserDomain::User::Service
{
public:
    /// @brief 用户域对外提供的查询用户数据接口，具体要查什么东西请在QueryUsersRequest中指明
    /// @param context 
    /// @param request 在这里面指明要查询什么DTO，字段看include/common/idl/domain/user/user_dto.proto
    /// @param response 返回一个UserDTO
    /// @return 
    grpc::Status QueryUsers(grpc::ServerContext* context, const UserDomain::QueryUsersRequest* request, UserDomain::QueryUsersResponse* response) override;

    /// @brief 用户域对外提供的创建用户接口
    /// @param context 
    /// @param request 
    /// @param response 
    /// @return 
    grpc::Status CreateUsers(grpc::ServerContext* context, const UserDomain::CreateUsersRequest* request, UserDomain::CreateUsersResponse* response) override;

    /// @brief 用户域对外提供的更新用户信息接口
    /// @param context 
    /// @param request 
    /// @param response 
    /// @return 
    grpc::Status UpdateUsers(grpc::ServerContext* context, const UserDomain::UpdateUsersRequest* request, UserDomain::UpdateUsersResponse* response) override;
};


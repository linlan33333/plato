#include "domain/user/rpc/service/service.h"
#include "common/config/userdomain.h"

UserDomainRpcService::UserDomainRpcService()
{
    std::string addr = UserDomainConfig::Get().GetServiceAddr() + ":" + std::to_string(UserDomainConfig::Get().GetServicePort());
    builder_.AddListeningPort(addr, grpc::InsecureServerCredentials());
    builder_.RegisterService(&impl_);
    server_ = builder_.BuildAndStart();
}

void UserDomainRpcService::Start()
{
    server_->Wait();
}
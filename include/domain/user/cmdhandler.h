#pragma once

#include "options.h"
#include "common/idl/domain/user/user_dto.pb.h"
#include <map>
#include <functional>

using RequestHandler = std::function<void(Options&)>;

class CmdHandler
{
public:
    static CmdHandler& Get();

private:
    CmdHandler();
    CmdHandler(const CmdHandler&) = delete;
    CmdHandler& operator=(const CmdHandler&) = delete;

    /// @brief 查询该用户的所有设备deviceID，根据传入的选项看查询的是全部设备还是在线的设备
    /// @param userID 
    /// @param query_all_device 为true则查询所有设备，为false则查询在线设备
    /// @return deviceID的列表
    std::vector<uint64_t> QueryDeviceList(uint64_t userID, bool query_all_device);

    user::UserDTO QueryUserInformation(uint64_t userID);

    user::UserDTO QueryUserSetting(uint64_t userID);

    user::UserDTO QueryUserDevice(uint64_t userID, std::vector<uint64_t> deviceID_list);

    user::UserDTO QueryUserProfile(uint64_t userID);

    /// @brief 处理用户域进程的RPC请求的函数处理表
    std::map<uint32_t, RequestHandler> request_handler_map_;
};
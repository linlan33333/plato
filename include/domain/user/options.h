#pragma once

#include <string>
#include <vector>

namespace UserDomain
{
    enum class Mode
    {
        INFORMATION,    // 用户个人资料
        PROFILE,        // 用户详细资料
        DEVICE,         // 用户设备
        SETTING         // 用户设置
    };
}

class Options
{
public:
    Options();

    void PushMode(UserDomain::Mode mode);
    std::vector<UserDomain::Mode>& GetModeList();

    void PushDeviceID(uint64_t device_id);
    std::vector<uint64_t> GetDeviceIDList();

    void SetAllDevice(bool all_device);
    bool IsAllDevice() const;

    void SetActiveDevice(bool active_device);
    bool IsActiveDevice() const;

private:
    // 这个modes_表示查询模式与对应的handler函数，查询模式有Information、Setting等，看调用方要查什么
    std::vector<UserDomain::Mode> modes_;

    std::vector<uint64_t> deviceID_list_;

    // 查询范围是该用户的所有设备
    bool all_device_;

    // 查询范围是该用户的在线设备
    bool active_device_;
};
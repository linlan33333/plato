#include "options.h"

Options::Options()
    : all_device_(false)
    , active_device_(true)
{
}

void Options::PushMode(UserDomain::Mode mode)
{
    modes_.push_back(mode);
}

std::vector<UserDomain::Mode> &Options::GetModeList()
{
    return modes_;
}

void Options::PushDeviceID(uint64_t device_id)
{
    deviceID_list_.push_back(device_id);
}

std::vector<uint64_t> Options::GetDeviceIDList()
{
    return deviceID_list_;
}

void Options::SetAllDevice(bool all_device)
{
    all_device_ = all_device;
}

bool Options::IsAllDevice() const
{
    return all_device_;
}

void Options::SetActiveDevice(bool active_device)
{
    active_device_ = active_device;
}

bool Options::IsActiveDevice() const
{
    return active_device_;
}

#include "bizflow/meta.h"
#include <spdlog/spdlog.h>
#include "meta.h"

std::size_t ErrorHash::operator()(const Error &error) const
{
    // 如果error_no_为负数，那么说明没有设置对应的错误编号，那就只能比较字符串了
    if (error.GetErrorNo() == -1)
    {
        return std::hash<std::string> ()(error.GetDescription());
    }
    
    return std::hash<int> ()(error.GetErrorNo());
}

bool ErrorEqual::operator()(const Error &lhs, const Error &rhs) const
{
    // 如果error_no_为负数，那么说明没有设置对应的错误编号，那就只能比较字符串了
    if (lhs.GetErrorNo() == -1 && rhs.GetErrorNo() == -1)
    {
        return lhs.GetDescription() == rhs.GetDescription();
    }

    return lhs.GetErrorNo() == rhs.GetErrorNo();
}

Meta::Meta(int retry_num)
    : retry_num_(retry_num)
{
}

void Meta::AddRetryError(Error &err)
{
    err_map_[err] = bizflow::ErrorType::RetryErr;
}

void Meta::AddNonRetryError(Error &err)
{
    err_map_[err] = bizflow::ErrorType::NonRetryErr;
}

void Meta::AdddAbortError(Error &err)
{
    err_map_[err] = bizflow::ErrorType::AbortErr;
}

void Meta::SetRetryNum(int retry_num)
{
    retry_num_ = retry_num;
}

int Meta::GetRetryNum()
{
    return retry_num_;
}

bizflow::ErrorType Meta::GetErrorType(Error &err)
{
    auto err_pair = err_map_.find(err);
    if (err_pair == err_map_.end())
    {
        spdlog::error("Meta.cc::GetErrorType: Can\'t find target error type!");

        return bizflow::ErrorType::AbortErr;
    }

    return err_pair->second;
}

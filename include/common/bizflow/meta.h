#pragma once

#include "bizflow/error.h"
#include <string>
#include <unordered_map>

namespace bizflow
{
    // 错误类型，可以自行扩展
    enum class ErrorType
    {
        RetryErr,
        NonRetryErr,
        AbortErr
    };
}

struct ErrorHash
{
    std::size_t operator() (const Error& error) const;
};

struct ErrorEqual
{
    bool operator() (const Error& lhs, const Error& rhs) const;
};

class Meta
{
public:
    Meta(int retry_num = 3);

    /// @brief 添加可重试错误
    /// @param err 
    void AddRetryError(Error& err);

    /// @brief 添加不可重试错误
    /// @param err 
    void AddNonRetryError(Error& err);

    /// @brief 添加终止进程错误
    /// @param err 
    void AdddAbortError(Error& err);

    /// @brief 设置重试次数
    /// @param retry_num 
    void SetRetryNum(int retry_num);
    int GetRetryNum();

    /// @brief 查询某个错误是哪种类型
    /// @param err 
    /// @return 
    bizflow::ErrorType GetErrorType(Error& err);

private:

    /// @brief 将所有类型的错误都存放到这里，方便快速查找某个错误对应哪种类型
    /// 注意要自定义哈希函数
    std::unordered_map<Error, bizflow::ErrorType, ErrorHash, ErrorEqual> err_map_;

    /// @brief 可重试错误的重试次数
    int retry_num_;
};
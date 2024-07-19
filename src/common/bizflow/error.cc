#include "bizflow/error.h"
#include "error.h"

Error::Error(std::string description, int error_no)
    : description_(description)
    , error_no_(error_no)
{
}

bool Error::operator==(const Error &error)
{
    if (error_no_ == -1)
    {
        return description_ == error.GetDescription();
    }
    
    return error_no_ == error.GetErrorNo();
}

void Error::Reset()
{
    error_no_ = -1;
    description_.clear();
}

void Error::SetErrorNo(int error_no)
{
    error_no_ = error_no;
}

int Error::GetErrorNo()
{
    return error_no_;
}

int Error::GetErrorNo() const
{
    return error_no_;
}

void Error::SetDescription(std::string& description)
{
    description_ = description;
}

std::string Error::GetDescription()
{
    return description_;
}

std::string Error::GetDescription() const
{
    return description_;
}


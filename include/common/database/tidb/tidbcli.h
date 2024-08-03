#pragma once

#include <string>

class TiDBCli
{
public:
    static TiDBCli& Get();

private:
    TiDBCli(const TiDBCli&) = delete;
    TiDBCli& operator=(const TiDBCli&) = delete;
};
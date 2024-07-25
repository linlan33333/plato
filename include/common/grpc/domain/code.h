#pragma once

// 这里提前约定好领域层的RPC请求状态码含义，这里只是随手写的，有更好的设计自行修改
// 因为可能出现跨领域进行RPC请求的情况，所以这里把user、message、session三个领域的
// 状态码放在一起了
namespace Domain
{
    namespace Code {
        const int SUCCESS = 1;
        const int CREATEUSERERROR = 2;
        const int QUERYUSERERROR = 3;
        const int UPDATEUSERERROR = 4;
    }
}
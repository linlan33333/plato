#pragma once

#include <string>

// 每个Node可以定制化一些Error对象，设置错误号以及错误描述信息
// 每个Node对应一个Meta类，可以设置Meta类中的错误类型，并设置该Error对象属于哪种错误类型，添加进去
// 想想分布式链路跟踪如何监控并记录这里发生的错误，怎么对该类进行扩展
class Error
{
public:
    Error() = default;
    Error(std::string description, int error_no = -1);

    /// @brief 重载==号，因为Meta中涉及到判断两个Error对象是否相等，相等才能说明error map表中存在该类型的错误。
    /// 相等的逻辑是两个Error对象的description_相等则相等，但显然不合理，应当是Error类中有一个ErrorNo之类的东西
    /// 比如值为1表示密码错误，以枚举类型的形式在其他地方定义好，这里只留个接口，觉得不合理可以自行修改
    /// @param error 
    /// @return 
    bool operator== (const Error& error);

    /// @brief 复位函数，清空Error对象中的所有状态，如果某个Node节点需要retry，请先调用该函数清空错误
    void Reset();

    /// @brief 设置错误类型，可以传入枚举类型
    /// @param error_no 
    void SetErrorNo(int error_no);

    /// @brief 返回错误编号，注意：如果你传入的是枚举类型的值，你需要自己将结果转换成枚举类型
    /// @return 
    int GetErrorNo();
    int GetErrorNo() const;

    void SetDescription(std::string& description);
    /// @brief 获取该错误类型的描述
    /// @return 
    std::string GetDescription();
    std::string GetDescription() const;
    
private:
    /// @brief 该错误信息的描述
    std::string description_;

    /// @brief 错误编号，留出来给用户设置的，比如error_no_为1表示密码错误，用于比较两个Error对象是否相等
    int error_no_;
};
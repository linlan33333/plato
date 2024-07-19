#pragma once

/// @brief Node节点的输入输出对象的父类，你可以根据Node节点的输入和输出分别设计、创建对应的子类
/// 将字段类型和名称定义在其中，然后需要的时候直接取即可
struct CallbackCtx
{
virtual ~CallbackCtx() {}
};
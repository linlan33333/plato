# 设置cmake的最低版本和项目名称
cmake_minimum_required(VERSION 3.0)
project(plato)

# 使用grpc得把这玩意包进来，不然报错找不到protobuf之类的库文件
include(common.cmake)

# 设置gdb调试生成debug版本
set(CMAKE_BUILD_TYPE "Debug")

# 设置C++标准为C++17，common.cmake文件中也得设置一下，要改记得改一下common.cmake的
# set(CMAKE_CXX_STANDARD 17)

# 将-std=c++17之类的添加到编译选项
add_compile_options(-std=c++17)
# add_compile_options(-fsanitize=address)
# add_compile_options(-fno-omit-frame-pointer)

# 设置项目可执行文件输出路径
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
# 设置项目库文件输出路径
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

# 设置项目编译头文件搜索路径 相当于g++编译命令的-I
# 这样在其他目录下引入头文件就不需要写路径了，随便引用
include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/include/ipconfig)
# include_directories(${PROJECT_SOURCE_DIR}/include/ipconfig/domain)
# include_directories(${PROJECT_SOURCE_DIR}/include/ipconfig/source)
include_directories(${PROJECT_SOURCE_DIR}/include/gateway)
include_directories(${PROJECT_SOURCE_DIR}/include/state)
include_directories(${PROJECT_SOURCE_DIR}/include/common)
# include_directories(${PROJECT_SOURCE_DIR}/include/common/config)

# 设置项目库文件搜索路径 相当于g++编译命令的-L 
link_directories(${PROJECT_SOURCE_DIR}/lib)

# cmake的用法就是从顶级目录开始往下去找子目录的cmake文件，逐层确定最终编译的文件范围
add_subdirectory(src)
# 将当前目录下的所有源文件定义为SRC_LIST
# 主要就一个server.cc需要算进去
aux_source_directory(. SRC_LIST)

# 将里面的source目录下的所有源文件定义为SOURCE_LIST
aux_source_directory(./source SOURCE_LIST)
# 将里面的domain目录下的db目录下的所有源文件定义为DOMAIN_LIST
aux_source_directory(./domain DOMAIN_LIST)

# 由于用到了config通用配置模块相关的东西，得把他们包含进来
aux_source_directory(../common/config CONFIG_LIST)
aux_source_directory(../common/discovery DISCOVERY_LIST)

# 设置生成的可执行文件的名称
add_executable(IpConfigServer ${SRC_LIST} ${SOURCE_LIST} ${DOMAIN_LIST} ${CONFIG_LIST} ${DISCOVERY_LIST})
# 指定可执行文件链接时需要依赖的动态库文件
target_link_libraries(IpConfigServer muduo_net muduo_base muduo_http pthread zookeeper_mt yaml-cpp)

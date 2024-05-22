# 将当前目录下的所有源文件定义为SRC_LIST
# 主要就一个server.cc需要算进去
aux_source_directory(. SRC_LIST)

# 将里面的source目录下的所有源文件定义为SOURCE_LIST
aux_source_directory(./rpc/client RPC_CLIENT_LIST)
# 将里面的domain目录下的db目录下的所有源文件定义为DOMAIN_LIST
aux_source_directory(./rpc/service RPC_SERVICE_LIST)

# 由于用到了config通用配置模块相关的东西，得把他们包含进来
aux_source_directory(../common/config CONFIG_LIST)
aux_source_directory(../common/srpc/state SRPC_STATE_LIST)
aux_source_directory(../common/srpc/gateway SRPC_GATEWAY_LIST)
aux_source_directory(../common/threadpool THREAD_POOL_LIST)

# 设置生成的可执行文件的名称
add_executable(State ${SRC_LIST} ${RPC_CLIENT_LIST} ${RPC_SERVICE_LIST} ${CONFIG_LIST} ${SRPC_STATE_LIST} ${THREAD_POOL_LIST} ${SRPC_GATEWAY_LIST})
# 指定可执行文件链接时需要依赖的动态库文件
target_link_libraries(State muduo_net muduo_base srpc workflow pthread zookeeper_mt protobuf yaml-cpp)
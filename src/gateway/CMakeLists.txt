# 将当前目录下的所有源文件定义为SRC_LIST
# 主要就一个server.cc需要算进去
aux_source_directory(. SRC_LIST)

# 将里面的source目录下的所有源文件定义为SOURCE_LIST
aux_source_directory(./rpc/client RPC_CLIENT_LIST)
# 将里面的domain目录下的db目录下的所有源文件定义为DOMAIN_LIST
aux_source_directory(./rpc/service RPC_SERVICE_LIST)

# 由于用到了config通用配置模块相关的东西，得把他们包含进来
aux_source_directory(../common/config CONFIG_LIST)
aux_source_directory(../common/grpc/gateway GRPC_GATEWAY_LIST)
aux_source_directory(../common/grpc/state GRPC_STATE_LIST)
aux_source_directory(../common/threadpool THREAD_POOL_LIST)
aux_source_directory(../common/tcp TCP_LIST)
aux_source_directory(../common/utils UTILS_LIST)

# 设置生成的可执行文件的名称
add_executable(Gateway ${SRC_LIST} ${RPC_CLIENT_LIST} ${RPC_SERVICE_LIST} ${CONFIG_LIST} ${GRPC_GATEWAY_LIST} 
                ${THREAD_POOL_LIST} ${GRPC_STATE_LIST} ${TCP_LIST} ${UTILS_LIST})

# 指定可执行文件链接时需要依赖的动态库文件，最后那三个得主目录的cmake文件引入common.cmake才能这么写
target_link_libraries(Gateway muduo_net muduo_base pthread zookeeper_mt yaml-cpp
${_REFLECTION}  
${_GRPC_GRPCPP}
${_PROTOBUF_LIBPROTOBUF})

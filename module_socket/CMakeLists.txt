cmake_minimum_required(VERSION 3.4.1)

AUX_SOURCE_DIRECTORY(. DIR_SRC_SOCKET)
ADD_LIBRARY(lib_socket SHARED ${DIR_SRC_SOCKET})

target_link_libraries(
        lib_socket
        lib_log 
        uv 
        -lpthread )
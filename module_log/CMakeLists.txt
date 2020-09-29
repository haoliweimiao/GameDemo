cmake_minimum_required(VERSION 3.4.1)

AUX_SOURCE_DIRECTORY(. DIR_SRC_LOG)
ADD_LIBRARY(lib_log SHARED ${DIR_SRC_LOG})

target_link_libraries(
    lib_log )
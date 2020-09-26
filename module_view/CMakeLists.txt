cmake_minimum_required(VERSION 3.4.1)

AUX_SOURCE_DIRECTORY(. DIR_SRC_VIEW)
ADD_LIBRARY(lib_view SHARED ${DIR_SRC_VIEW})

target_link_libraries(
    lib_view 
    lib_base 
    lib_db 
    lib_cache )
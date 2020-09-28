cmake_minimum_required(VERSION 3.4.1)

include_directories( json )

AUX_SOURCE_DIRECTORY(. DIR_SRC_JSON)
ADD_LIBRARY(lib_json SHARED ${DIR_SRC_JSON})

target_link_libraries(
    lib_json 
    lib_base )
cmake_minimum_required(VERSION 3.4.1)

AUX_SOURCE_DIRECTORY(. DIR_SRC_DEMO)
ADD_LIBRARY(lib_demo SHARED ${DIR_SRC_DEMO})

target_link_libraries(
	lib_demo 
	lib_base
	lib_db 
	lib_cache
    uv    )

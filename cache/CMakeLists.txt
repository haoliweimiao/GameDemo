cmake_minimum_required(VERSION 3.4.1)

AUX_SOURCE_DIRECTORY(. DIR_SRC_CACHE)
ADD_LIBRARY(lib_cache SHARED ${DIR_SRC_CACHE})

target_link_libraries(
	lib_cache 
	lib_base )
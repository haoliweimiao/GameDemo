cmake_minimum_required(VERSION 3.4.1)

AUX_SOURCE_DIRECTORY(. DIR_SRC_BASE)
ADD_LIBRARY(lib_base SHARED ${DIR_SRC_BASE})

target_link_libraries(
	lib_base )
cmake_minimum_required(VERSION 3.4.1)

AUX_SOURCE_DIRECTORY(. DIR_SRC_CONFIG)
ADD_LIBRARY(lib_config SHARED ${DIR_SRC_CONFIG})

target_link_libraries(
	lib_config)
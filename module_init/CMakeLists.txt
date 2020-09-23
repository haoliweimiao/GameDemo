cmake_minimum_required(VERSION 3.4.1)

AUX_SOURCE_DIRECTORY(. DIR_SRC_INIT)
ADD_LIBRARY(lib_init SHARED ${DIR_SRC_INIT})

target_link_libraries(
	lib_init 
	lib_base )
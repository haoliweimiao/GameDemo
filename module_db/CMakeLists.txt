cmake_minimum_required(VERSION 3.4.1)

AUX_SOURCE_DIRECTORY(. DIR_SRC_DB)
ADD_LIBRARY(lib_db SHARED ${DIR_SRC_DB})
include_directories(${DIR_SRC_BASE})


target_link_libraries(
	lib_db 
	lib_base 
	-lsqlite3 )
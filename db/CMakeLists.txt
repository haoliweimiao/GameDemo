cmake_minimum_required(VERSION 3.4.1)

AUX_SOURCE_DIRECTORY(. DIR_SRC_DB)
ADD_LIBRARY(lib_db SHARED ${DIR_SRC_DB})


#add_library(lib_db SHARED test.cpp)
##依赖库
# find_library(log-lib log)
##
target_link_libraries(
	lib_db 
	-lsqlite3 )
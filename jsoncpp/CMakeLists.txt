cmake_minimum_required(VERSION 3.4.1)

include_directories( include )

AUX_SOURCE_DIRECTORY(./src/lib_json DIR_SRC_JSON)
ADD_LIBRARY(jsoncpp SHARED ${DIR_SRC_JSON})

target_link_libraries(
	jsoncpp )
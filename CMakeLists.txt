# CMakeLists.txt
# CMake 最低版本号要求
cmake_minimum_required(VERSION 3.15)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c11 -Wall")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -fno-rtti -fno-exceptions -fexceptions -Wall")

# 项目信息
project(GameDemo)

# 设置debug模式
# set(CMAKE_BUILD_TYPE Debug CACHE STRING "set build type to debug")

# 指定头文件搜索路径
include_directories( ${PROJECT_SOURCE_DIR}/ )
include_directories(
     module_db 
     module_base 
     module_cache 
     module_init 
     module_view 
     module_json 
     module_log 
     module_socket )

#使用命令 ADD_SUBDIRECTORY 指明本项目包含一个子目录 db
# 指定 编译子目录
ADD_SUBDIRECTORY( ${PROJECT_SOURCE_DIR}/module_db )
ADD_SUBDIRECTORY( ${PROJECT_SOURCE_DIR}/module_base )
ADD_SUBDIRECTORY( ${PROJECT_SOURCE_DIR}/module_cache )
ADD_SUBDIRECTORY( ${PROJECT_SOURCE_DIR}/module_init )
ADD_SUBDIRECTORY( ${PROJECT_SOURCE_DIR}/module_view )
ADD_SUBDIRECTORY( ${PROJECT_SOURCE_DIR}/module_json )
ADD_SUBDIRECTORY( ${PROJECT_SOURCE_DIR}/module_log )
ADD_SUBDIRECTORY( ${PROJECT_SOURCE_DIR}/module_socket )

# 指定源码目录
# 查找当前目录下的所有源文件
# 并将名称保存到 DIR_LIB_SRCS 变量
aux_source_directory(. DIR_SRCS)

# 指定生成目标 
#ADD_EXECUTABLE 指示变量 DIR_SRCS 中的源文件需要编译 成一个名称为 GameDemo 的可执行文件。
ADD_EXECUTABLE(GameDemo ${DIR_SRCS})

TARGET_LINK_LIBRARIES( 
    GameDemo 
    lib_base 
    lib_db 
    lib_cache 
    lib_init 
    lib_view 
    lib_json 
    lib_log 
    lib_socket )
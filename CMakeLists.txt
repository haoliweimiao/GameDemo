# CMakeLists.txt
# CMake 最低版本号要求
cmake_minimum_required(VERSION 3.15)

# 项目信息
project(GameDemo)

# 设置debug模式
# set(CMAKE_BUILD_TYPE Debug CACHE STRING "set build type to debug")

# include路径
include_directories(
    ${PROJECT_SOURCE_DIR}/ )
include_directories( db )

# 把 第三方 库 的 .a 文件和 .h 文件放到 代码的 lib 文件夹
link_directories(
    ${PROJECT_SOURCE_DIR}/)

#使用命令 ADD_SUBDIRECTORY 指明本项目包含一个子目录 db f
ADD_SUBDIRECTORY( ${PROJECT_SOURCE_DIR}/db )

# 查找当前目录下的所有源文件
# 并将名称保存到 DIR_LIB_SRCS 变量
aux_source_directory(. DIR_SRCS)

# 指定生成目标 
#ADD_EXECUTABLE 指示变量 DIR_SRCS 中的源文件需要编译 成一个名称为 GameDemo 的可执行文件。
ADD_EXECUTABLE(GameDemo ${DIR_SRCS})

TARGET_LINK_LIBRARIES( 
	GameDemo 
	lib_db )
#cmake版本3.18及以上
cmake_minimum_required(VERSION 3.18)

#指定项目名 采用C++语言  version 1.0
project(SunEngine LANGUAGES C CXX VERSION 1.0)

set(CMAKE_BUILD_TYPE Debug)

message(STATUS "Build Type: ${CMAKE_BUILD_TYPE}")
	
#指定C++20标准
set(CMAKE_CXX_STANDARD 20)			
set(CMAKE_CXX_STANDARD_REQUIRED True)		

include_directories(${CMAKE_SOURCE_DIR}/includes)
#添加执行源码文件夹
add_subdirectory(src)


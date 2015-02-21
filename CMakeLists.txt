cmake_minimum_required(VERSION 2.8.12)
project(boost-spirit-bits)


#-Wall -Werror
set (CMAKE_BUILD_TYPE "DEBUG")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 ")
set (CMAKE_CXX_COMPILER_ARG1 "-std=c++11")
set (EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}) 

add_subdirectory(src) 


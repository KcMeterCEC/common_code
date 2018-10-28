cmake_minimum_required(VERSION 3.5.1)
project(unidir_list)

#output path
set(CMAKE_BINART_DIR ${CMAKE_SOURCE_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})

#source path
include_directories(${PROJECT_SOURCE_DIR})

SET(CMAKE_BUILD_TYPE "Debug") 

#GLOB is used to create a list of all of the files that meet the globbing expression(i.e.. src/*.cpp)
# and add them to a variable SOURCES
file(GLOB SOURCES ${PROJECT_SOURCE_DIR}/*.c)

add_executable(unidir_list ${SOURCES})
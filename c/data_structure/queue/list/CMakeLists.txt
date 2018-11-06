cmake_minimum_required(VERSION 3.5.1)
project(queue_list)

#output path
set(CMAKE_BINART_DIR ${CMAKE_SOURCE_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIST_PATH "../../list/circular/")

#source path
include_directories(${PROJECT_SOURCE_DIR} ${LIST_PATH})

SET(CMAKE_BUILD_TYPE "Debug") 

#GLOB is used to create a list of all of the files that meet the globbing expression(i.e.. src/*.cpp)
# and add them to a variable SOURCES
file(GLOB SOURCES ${PROJECT_SOURCE_DIR}/*.c ${LIST_PATH}/list.c)

add_executable(queue_list ${SOURCES})

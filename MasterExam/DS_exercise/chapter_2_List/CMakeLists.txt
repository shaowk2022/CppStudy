cmake_minimum_required(VERSION 3.10)
project(Lists_exercise)
if(NOT DEFINED COMPLIER_PATH)
    set(COMPLIER_PATH /usr/bin/g++)
endif()
file(GLOB SRC_LIST ${CMAKE_CURRENT_SOURCE_DIR}/src/*.c)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/bin)

add_executable(Lists_CRUD_main ${SRC_LIST})
target_include_directories(
    Lists_CRUD_main PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)
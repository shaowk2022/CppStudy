cmake_minimum_required(VERSION 3.10)
project(SqList_exercise)
set(CMAKE_CXX_COMPILER /usr/bin/gcc)
file(GLOB SRC_LIST ${CMAKE_CURRENT_SOURCE_DIR}/src/*.c)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/bin)

add_executable(main ${SRC_LIST})
target_include_directories(
    main PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)
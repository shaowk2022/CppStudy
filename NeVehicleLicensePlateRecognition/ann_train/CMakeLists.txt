# CMakeList.txt: ann_train 的 CMake 项目，在此处包括源代码并定义
# 项目特定的逻辑。
#
cmake_minimum_required (VERSION 3.8)
include_directories(
    "/home/wenke/lib/opencv4.1.2_install/include/opencv4"
)

link_directories("/home/wenke/lib/opencv4.1.2_install/lib")

file(GLOB src_files ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
add_executable (ann_train ${src_files})

# TODO: 如有需要，请添加测试并安装目标。
target_link_libraries(ann_train opencv_world) 
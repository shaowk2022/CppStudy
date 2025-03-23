# CMakeList.txt: 
# NeVehicleLicensePlateRecognition 的 CMake 项目，在此处包括源代码并定义
# 项目特定的逻辑。
#

cmake_minimum_required (VERSION 3.8)
project(NeVehicleLicensePlateRecognition)
set(CMAKE_CXX_COMPILER /usr/bin/g++)

# set(WITH_GTK ON)
# set(WITH_GTK_2_X ON)

include_directories(
    "/home/wenke/lib/opencv4.1.2_install/include/opencv4"
)

# 链接opencv库文件
link_directories("/home/wenke/lib/opencv4.1.2_install/lib")

# 查找源文件
file(GLOB srcs ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp) 

# 设置可执行文件输出目录
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/bin)

# 将源代码添加到此项目的可执行文件。
add_executable(NeVehicleLicensePlateRecognition ${srcs})

# TODO: 如有需要，请添加测试并安装目标。
#       cmake -DWITH_GTK=ON -DWITH_GTK_2_X=ON .. 编译时opencv时启用gtk支持
#       cmake使用-DBUILD_opencv_world=ON选项来生成opencv_world库，包含opencv的所有模块
target_link_libraries(NeVehicleLicensePlateRecognition opencv_world)
# cmake -DCMAKE_INSTALL_PREFIX=~/lib/opencv4.1.2_install -DBUILD_opencv_world=ON -DWITH_GTK_2_X=ON -DWITH_GTK=ON -DCMAKE_CXX_STANDARD=11 -DCMAKE_CXX_COMPILER=/usr/bin/g++ ..
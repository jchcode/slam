cmake_minimum_required(VERSION 3.5)

project(RealsenseExamplesSaveToDisk)

set(CMAKE_CXX_FLAGS "-std=c++11")
set(CMAKE_BUILD_TYPE Debug)     # 添加后可进行调试

find_package(OpenCV REQUIRED)
message(STATUS "The destination of OpenCV header file is " ${OpenCV_INCLUDE_DIRS})

include_directories(${OpenCV_INCLUDE_DIRS})
include_directories(/home/myubuntu/Softwares/thirdparty/librealsense/third-party)

add_executable(rs-save-to-disk rs-save-to-disk.cpp)
target_link_libraries(rs-save-to-disk ${OpenCV_LIBS} realsense2 )

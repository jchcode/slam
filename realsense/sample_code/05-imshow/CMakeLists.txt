cmake_minimum_required(VERSION 3.5)

project(RealsenseExamplesImshow)

set(CMAKE_CXX_FLAGS "-std=c++11")
set(CMAKE_BUILD_TYPE Debug)     # 添加后可进行调试

find_package(OpenCV REQUIRED)
message(STATUS "The destination of OpenCV header file is " ${OpenCV_INCLUDE_DIRS})

include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(rs-imshow rs-imshow.cpp)
target_link_libraries(rs-imshow ${OpenCV_LIBS} realsense2 )
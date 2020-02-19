cmake_minimum_required(VERSION 3.5.0)

project(RealsenseExamplesHelloRealSense)

set(CMAKE_CXX_FLAGS "-std=c++11")
set(CMAKE_BUILD_TYPE Debug)     # 添加后可进行调试
set(DEPENDENCIES realsense2)

add_executable(rs-hello-realsense rs-hello-realsense.cpp)
target_link_libraries(rs-hello-realsense ${DEPENDENCIES})
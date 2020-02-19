cmake_minimum_required(VERSION 3.5)

project(display-color-infrared-depth-frame-instantly)

aux_source_directory(. SRC_LIST)     # 设置显示变量指向当前目录下的所有源文件
set(CMAKE_CXX_FLAGS "-std=c++11")
set(CMAKE_BUILD_TYPE Debug)     # 添加后可进行调试
set(DEPENDENCIES realsense2)

find_package(OpenCV REQUIRED)
message(STATUS "The destination of OpenCV header file is " ${OpenCV_INCLUDE_DIRS})
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(${PROJECT_NAME} ${SRC_LIST})
target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS})
target_link_libraries(${PROJECT_NAME} ${DEPENDENCIES})
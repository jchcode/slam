cmake_minimum_required(VERSION 3.5)
project(useOpenCV)
set(CMAKE_CXX_FLAGS "-std=c++11")       # 添加C++ 11支持

# 寻找OpenCV库的头文件与库文件指令，如果找到它就会提供头文件与库文件所在目录的变量
# 在这个例子中就是OpenCV_INCLUDE_DIRS和OpenCV_LIBRARIES这两个变量
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

#添加一个可执行程序
add_executable(useOpenCV useOpenCV.cpp)
target_link_libraries(useOpenCV ${OpenCV_LIBS})

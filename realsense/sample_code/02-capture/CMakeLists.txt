cmake_minimum_required(VERSION 3.5)

project(RealsenseExamplesCapture)

set(CMAKE_CXX_FLAGS "-std=c++11")
set(CMAKE_BUILD_TYPE Debug)     # 添加后可进行调试

find_package(OpenGL REQUIRED)

include_directories(/home/myubuntu/Softwares/thirdparty/librealsense/examples)
include_directories(${OPENGL_INCLUDE_DIRS})

add_executable(rs-capture rs-capture.cpp)
target_link_libraries(rs-capture realsense2 glfw ${OPENGL_gl_LIBRARY} ${OPENGL_glu_LIBRARY})
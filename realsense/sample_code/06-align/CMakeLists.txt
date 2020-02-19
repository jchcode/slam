cmake_minimum_required(VERSION 3.5.0)

project(RealsenseExamplesAlign)

set(CMAKE_CXX_FLAGS "-std=c++11")
set(CMAKE_BUILD_TYPE Debug)     # 添加后可进行调试

find_package(OpenGL REQUIRED)

include_directories(/home/myubuntu/Softwares/thirdparty/librealsense/examples)
include_directories(/home/myubuntu/Softwares/thirdparty/librealsense/third-party/imgui)
include_directories(${OPENGL_INCLUDE_DIRS})

# 将执行源代码rs-align.cpp和所需调用的函数库源代码
# imgui.cpp,imgui_draw.cpp,imgui_impl_glfw.cpp同时进行编译
# 这样可以无须事先编译生成所调用函数的共享库
add_executable( rs-align rs-align.cpp 
                /home/myubuntu/Softwares/thirdparty/librealsense/third-party/imgui/imgui.cpp
                /home/myubuntu/Softwares/thirdparty/librealsense/third-party/imgui/imgui_draw.cpp
                /home/myubuntu/Softwares/thirdparty/librealsense/third-party/imgui/imgui_impl_glfw.cpp )
target_link_libraries(rs-align realsense2 glfw ${OPENGL_gl_LIBRARY} ${OPENGL_glu_LIBRARY})
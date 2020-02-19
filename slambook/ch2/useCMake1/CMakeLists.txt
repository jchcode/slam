# 声明要求的cmake的最低版本
cmake_minimum_required(VERSION 3.5)

# 声明一个cmake工程
project(useCmake)

# 添加共享库文件(将源码编译成共享库文件)
add_library(helloworld SHARED funHelloWorld.cpp)
add_library(helloslam SHARED funHelloSLAM.cpp)

# 添加一个可执行程序
add_executable(useCmake useCmake.cpp)
# 将可执行程序链接到共享库文件上
target_link_libraries(useCmake helloworld helloslam )

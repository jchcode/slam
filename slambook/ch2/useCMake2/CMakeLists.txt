# 声明要求的cmake的最低版本
cmake_minimum_required(VERSION 3.5)

# 声明一个cmake工程
project(useCmake)

# 添加一个可执行程序
add_executable(useCmake useCmake.cpp funHelloWorld.cpp funHelloSLAM.cpp)


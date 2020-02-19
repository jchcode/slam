#声明要求的cmake最低版本（视自己安装的cmake版本而定）
cmake_minimum_required(VERSION 3.5)

#声明一个cmake工程
project(useEigen)

#添加Eigen头文件，注意自己头文件的安装位置
#Eigen库只有头文件，没有库文件，所以无需添加库
include_directories("/usr/include/eigen3")

#添加一个可执行程序
add_executable(useEigen useEigen.cpp)

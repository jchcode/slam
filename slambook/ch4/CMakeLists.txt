cmake_minimum_required( VERSION 3.5 )
project( useSophus )

# 寻找Sophus库的头文件与库文件指令，如果找到它就会提供头文件与库文件所在目录的变量
# 在这个例子中就是Sophus_INCLUDE_DIRS和Sophus_LIBRARIES这两个变量
find_package(Sophus REQUIRED)                      
include_directories( ${Sophus_INCLUDE_DIRS} )      

add_executable( useSophus useSophus.cpp )
target_link_libraries( useSophus ${Sophus_LIBRARIES} )

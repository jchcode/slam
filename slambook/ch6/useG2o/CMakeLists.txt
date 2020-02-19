cmake_minimum_required( VERSION 3.5 )
project( useG2o )

set( CMAKE_BUILD_TYPE "Release" )
set( CMAKE_CXX_FLAGS "-std=c++11 -O3" )

# 添加cmake模块以使用ceres库
list( APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake_modules )

# 寻找G2O（此处不是0，而是大写的O）
find_package( G2O REQUIRED )
include_directories( 
    ${G2O_INCLUDE_DIRS}
    "/usr/include/eigen3"
)

# OpenCV
find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_DIRS} )

add_executable( useG2o useG2o.cpp )
# 与G2O和OpenCV链接
target_link_libraries( useG2o 
    ${OpenCV_LIBS}
    g2o_core g2o_stuff
)


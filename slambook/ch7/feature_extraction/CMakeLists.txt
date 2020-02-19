cmake_minimum_required( VERSION 3.5 )

project( feature_extraction )

set( CMAKE_BUILD_TYPE "Release" )
set( CMAKE_CXX_FLAGS "-std=c++11 -O3" )

find_package( OpenCV 3.4 REQUIRED )     
# 此处必须指定opencv版本号，不然会报错
include_directories( ${OpenCV_INCLUDE_DIRS} )

add_executable( feature_extraction feature_extraction.cpp  )
target_link_libraries( feature_extraction ${OpenCV_LIBS} )

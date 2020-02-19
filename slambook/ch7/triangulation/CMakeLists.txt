cmake_minimum_required( VERSION 3.5 )

project( triangulation )

set( CMAKE_BUILD_TYPE "Release" )
set( CMAKE_CXX_FLAGS "-std=c++11 -O3" )

find_package( OpenCV 3.4 REQUIRED )

include_directories( ${OpenCV_INCLUDE_DIRS} )

add_library(FeatureMatch_shared SHARED func_FeatureMatch.cpp)
add_library(PoseEst2d2d_shared SHARED func_PoseEst2d2d.cpp)
add_library(Pixel2Cam_shared SHARED func_Pixel2Cam.cpp)
add_library(TriangMeasure_shared SHARED func_TriangMeasure.cpp)

add_executable( triangulation triangulation.cpp )
target_link_libraries( triangulation
                       ${OpenCV_LIBS}
                       FeatureMatch_shared
                       PoseEst2d2d_shared
                       Pixel2Cam_shared
                       TriangMeasure_shared )

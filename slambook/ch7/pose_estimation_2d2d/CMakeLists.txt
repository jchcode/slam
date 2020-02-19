cmake_minimum_required( VERSION 3.5 )

project( pose_estimation_2d2d )

set( CMAKE_BUILD_TYPE "Release" )
set( CMAKE_CXX_FLAGS "-std=c++11 -O3" )

find_package( OpenCV 3.1 REQUIRED )

include_directories( ${OpenCV_INCLUDE_DIRS} )

add_library(FeatureMatch_shared SHARED funFeatureMatch.cpp)
add_library(PoseEst2d2d_shared SHARED funPoseEst2d2d.cpp)
add_library(Pixel2Cam_shared SHARED funPixel2Cam.cpp)

add_executable( pose_estimation_2d2d pose_estimation_2d2d.cpp )
target_link_libraries( pose_estimation_2d2d
                       ${OpenCV_LIBS}
                       FeatureMatch_shared
                       PoseEst2d2d_shared
                       Pixel2Cam_shared )

#include <iostream>                 // for cout
#include <librealsense2/rs.hpp>     // include the librealsense C++ header file

using namespace std;
using namespace rs2;

// Hello RealSense example demonstrates the basics of connecting to a RealSense device and taking advantage of depth data
int main(int argc, char* argv[]) try
{
    // Create a Pipeline - this serves as a top-level API for streaming and processing frames
    rs2::pipeline pipe;
    // Configure and start the pipeline
    pipe.start();

    std::cout << "hello, intel realsense" << "\n";     // \n --- 换行，将当前位置移到下一行开头
    while (true)
    {
        // Block program until frames arrive
        rs2::frameset frames = pipe.wait_for_frames();

        // Try to get a frame of a depth image
        rs2::depth_frame depth = frames.get_depth_frame();

        // Get the depth frame's dimensions
        float width = depth.get_width();
        float height = depth.get_height();

        // Query the distance from the camera to the object in the center of the image
        float dist_to_center = depth.get_distance(width/2, height/2);

        // Print the distance
        std::cout << "The camera is facing an object " << dist_to_center << " meters away \r";     
        // \r --- 回车，将当前位置移到本行开头，等价于将本条命令不断刷新
    }

    return EXIT_SUCCESS;     // 等价于"return 0"
}

catch (const rs2::error & e)
{
    std::cerr << "RealSense error calling " << e.get_failed_function() << "(" << e.get_failed_args() << "):\n    " << e.what() << std::endl;
    return EXIT_FAILURE;     // 等价于"return 1"
}
catch (const std::exception& e)
{
    std::cerr << e.what() << std::endl;
    return EXIT_FAILURE;
}
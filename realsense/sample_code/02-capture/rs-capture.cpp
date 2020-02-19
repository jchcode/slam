#include <iostream>
#include <librealsense2/rs.hpp>
#include "example.hpp"

using namespace std;
using namespace rs2;

int main(int argc, char* argv[]) try
{
    // Create a simple OpenGL window for rendering:
    window app(1920, 1080, "RealSense Capture Example");

    // Depth data is usually provided on a 12-bit grayscale which is not very useful for visualization.
    // To enhance visualization, we provide an API that converts the grayscale image to RGB:
    // Declare depth colorizer for enhanced color visualization of depth data
    rs2::colorizer color_map;
    
    // Declare rates printer for showing streaming rates of the enabled streams.
    // rs2::rates_printer printer;

    // Declare the RealSense pipeline, encapsulating the actual device and sensors
    rs2::pipeline pipe;
    
    // Start streaming with default recommended configuration
    // The default video configuration contains Depth and Color streams
    // If a device is capable to stream IMU data, both Gyro and Accelerometer are enabled by default 
    pipe.start(); 

    while (app)
    {
        rs2::frameset data = pipe.wait_for_frames().    // Wait for next set of frames from the camera
                             apply_filter(color_map);   // Find and colorize the depth data   
                             // apply_filter(printer);     // Print each enabled stream frame rate

        /*****
        rs2::frameset data = pipe.wait_for_frames().    // Wait for next set of frames from the camera
                             apply_filter(color_map).   // Find and colorize the depth data   
                             apply_filter(printer);     // Print each enabled stream frame rate
        *****/

        // The show method, when applied on frameset, break it to frames and upload each frame into a gl textures
        // Each texture is displayed on different viewport according to it's stream unique id
        app.show(data);
    }

    return EXIT_SUCCESS;
}

catch (const rs2::error & e)
{
    std::cerr << "RealSense error calling " << e.get_failed_function() << "(" << e.get_failed_args() << "):\n    " << e.what() << std::endl;
    return EXIT_FAILURE;
}
catch (const std::exception& e)
{
    std::cerr << e.what() << std::endl;
    return EXIT_FAILURE;
}
#include <iostream>
#include <opencv2/opencv.hpp>       // include OpenCV header file
#include <librealsense2/rs.hpp>     // include the librealsense C++ header file

using namespace std;
using namespace cv;
using namespace rs2;

int main(int argc, char* argv[]) try
{
    // Contruct a pipeline which abstracts the device
    rs2::pipeline pipe;
    // Create a configuration for configuring the pipeline with a non default profile
    rs2::config cfg;
    // Add desired streams to configuration
    cfg.enable_stream(RS2_STREAM_COLOR, 640, 480, RS2_FORMAT_BGR8, 30);
    cfg.enable_stream(RS2_STREAM_INFRARED, 640, 480, RS2_FORMAT_Y8, 30);
    cfg.enable_stream(RS2_STREAM_DEPTH, 640, 480, RS2_FORMAT_Z16, 30);
    // Instruct pipeline to start streaming with the requested configuration
    pipe.start(cfg);

    // Camera warmup - dropping several first frames to let auto-exposure stabilize
    rs2::frameset frames;
    for (int i = 0; i < 30; i++)
        frames = pipe.wait_for_frames();     // Wait for all configured streams to produce a frame

    // Get each frame
    rs2::frame color_frame = frames.get_color_frame();
    rs2::frame ir_frame = frames.first(RS2_STREAM_INFRARED);
    rs2::frame depth_frame = frames.get_depth_frame();

    // Creating OpenCV Matrix from a color image, IR image and depth image
    Mat color(Size(640, 480), CV_8UC3, (void*)color_frame.get_data(), Mat::AUTO_STEP);
    Mat ir(Size(640, 480), CV_8UC1, (void*)ir_frame.get_data(), Mat::AUTO_STEP);
    Mat depth(Size(640, 480), CV_16UC1, (void*)depth_frame.get_data(), Mat::AUTO_STEP);

    // Display in a GUI
    imshow("Color Image", color);
    imshow("Infrared Image", ir);
    imshow("Depth Image", depth);

    waitKey(0);

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
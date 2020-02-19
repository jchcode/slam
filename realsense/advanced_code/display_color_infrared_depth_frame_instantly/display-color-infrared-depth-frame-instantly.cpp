#include <iostream>
#include <opencv2/opencv.hpp>       // include OpenCV header file
#include <librealsense2/rs.hpp>     // include the librealsense C++ header file

using namespace std;
using namespace cv;
using namespace rs2;

int main(int argc, char* argv[]) try
{
    // Declare depth colorizer for pretty visualization of depth data
    // Colorizer generate color image based on input depth frame
    rs2::colorizer color_map;     

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

    while (waitKey(1)<0)
    {
        rs2::frameset frames = pipe.wait_for_frames();      // Wait for next set of frames from the camera

        // Get each frame
        rs2::frame color_frame = frames.get_color_frame();
        rs2::frame ir_frame = frames.first(RS2_STREAM_INFRARED);
        rs2::frame depth_frame = frames.get_depth_frame().apply_filter(color_map);

        // Get width and height of a color image, infrared image and depth image
        const int color_w = color_frame.as<rs2::video_frame>().get_width();
        const int color_h = color_frame.as<rs2::video_frame>().get_height();
        const int ir_w = ir_frame.as<rs2::video_frame>().get_width();
        const int ir_h = ir_frame.as<rs2::video_frame>().get_height();
        const int depth_w = depth_frame.as<rs2::video_frame>().get_width();
        const int depth_h = depth_frame.as<rs2::video_frame>().get_height();

        // Creating OpenCV Matrix from a color image, IR image and depth image
        Mat color(Size(color_w, color_h), CV_8UC3, (void*)color_frame.get_data(), Mat::AUTO_STEP);
        Mat ir(Size(ir_w, ir_h), CV_8UC1, (void*)ir_frame.get_data(), Mat::AUTO_STEP);
        Mat depth(Size(depth_w, depth_h), CV_8UC3, (void*)depth_frame.get_data(), Mat::AUTO_STEP);

        // infrared image: Apply Histogram Equalization
        equalizeHist( ir, ir );
        applyColorMap(ir, ir, COLORMAP_JET);

        // Display in a GUI
        imshow("Color Image", color);
        imshow("Infrared Image", ir);
        imshow("Depth Image", depth);
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
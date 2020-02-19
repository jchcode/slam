#include <librealsense2/rs.hpp> // Include RealSense Cross Platform API
#include <opencv2/opencv.hpp>   // Include OpenCV API

using namespace std;
using namespace cv;
using namespace rs2;

int main(int argc, char * argv[]) try
{
    // Declare depth colorizer for pretty visualization of depth data
    rs2::colorizer color_map;

    // Declare RealSense pipeline, encapsulating the actual device and sensors
    rs2::pipeline pipe;
    // Start streaming with default recommended configuration
    pipe.start();
    
    const auto depth_windowname = "Display depth Image";
    const auto color_windowname = "Display color Image";

    namedWindow(color_windowname, WINDOW_AUTOSIZE);
    namedWindow(depth_windowname, WINDOW_AUTOSIZE);

    while (waitKey(1)<0 && getWindowProperty(depth_windowname, WND_PROP_AUTOSIZE)>=0)
    {
        // Wait for next set of frames from the camera
        rs2::frameset data = pipe.wait_for_frames(); 

        // Get each frame
        rs2::frame depth_frame = data.get_depth_frame().apply_filter(color_map);
        rs2::frame color_frame = data.get_color_frame();

        // Query frame size (width and height)
        const int depth_width = depth_frame.as<rs2::video_frame>().get_width();
        const int depth_height = depth_frame.as<rs2::video_frame>().get_height();
        const int color_width = color_frame.as<rs2::video_frame>().get_width();
        const int color_height = color_frame.as<rs2::video_frame>().get_height();

        // Create OpenCV matrix of size (width, height) from the colorized depth data
        Mat depth(Size(depth_width, depth_height), CV_8UC3, (void*)depth_frame.get_data(), Mat::AUTO_STEP);
        Mat color(Size(color_width, color_height), CV_8UC3, (void*)color_frame.get_data(), Mat::AUTO_STEP);

        // Update the window with new data
        imshow(depth_windowname, depth);
        imshow(color_windowname, color);
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


// 需要进一步完成的工作：
// 如何实时显示陀螺仪和加速度计的数据；
// 如何将几个分离的窗口显示为一个大窗口的子窗口；如何设置每个子窗口的大小
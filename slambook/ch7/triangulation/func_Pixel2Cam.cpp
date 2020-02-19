#include <iostream>
#include <opencv2/core/core.hpp>

using namespace std;
using namespace cv;



// 像素坐标转相机归一化坐标
Point2d pixel2cam ( const Point2d& p, const Mat& K )
{
    return Point2d
           (
               ( p.x - K.at<double> ( 0,2 ) ) / K.at<double> ( 0,0 ),
               ( p.y - K.at<double> ( 1,2 ) ) / K.at<double> ( 1,1 )
           );

}

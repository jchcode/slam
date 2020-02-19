#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/calib3d/calib3d.hpp>

#include "myLibFunc.h"

using namespace std;
using namespace cv;



void triangulation (
                     const vector< KeyPoint >& keypoint_1,
                     const vector< KeyPoint >& keypoint_2,
                     const vector< DMatch >& matches,
                     const Mat& R, const Mat& t,
                     vector< Point3d >& points )
{
    Mat T1 = (Mat_<float> (3,4) <<
        1,0,0,0,
        0,1,0,0,
        0,0,1,0);
    Mat T2 = (Mat_<float> (3,4) <<
        R.at<double>(0,0), R.at<double>(0,1), R.at<double>(0,2), t.at<double>(0,0),
        R.at<double>(1,0), R.at<double>(1,1), R.at<double>(1,2), t.at<double>(1,0),
        R.at<double>(2,0), R.at<double>(2,1), R.at<double>(2,2), t.at<double>(2,0)
    );

    Mat K = ( Mat_<double> ( 3,3 ) << 520.9, 0, 325.1, 0, 521.0, 249.7, 0, 0, 1 );

    vector<Point2f> pts_1, pts_2;
    for ( DMatch m:matches )
    {
        // 将像素坐标转换至相机的归一化坐标
        pts_1.push_back ( pixel2cam( keypoint_1[m.queryIdx].pt, K) );
        pts_2.push_back ( pixel2cam( keypoint_2[m.trainIdx].pt, K) );
    }

    Mat pts_4d;
    triangulatePoints( T1, T2, pts_1, pts_2, pts_4d );
    /*****
    void triangulatePoints( InputArray projMatr1, InputArray projMatr2,
                            InputArray projPoints1, InputArray projPoints2,
                            OutputArray points4D );

    projMatr1     3x4 projection matrix of the first camera.
    projMatr2     3x4 projection matrix of the second camera.
    projPoints1   2xN array of feature points in the first image.
                  In case of c++ version it can be also a vector of feature points
                  or two-channel matrix of size 1xN or Nx1.
    projPoints2   2xN array of corresponding points in the second image.
                  In case of c++ version it can be also a vector of feature points
                  or two-channel matrix of size 1xN or Nx1.
    points4D      4xN array of reconstructed points in homogeneous coordinates.

    @note
       Keep in mind that all input data should be of float type
       in order for this function to work.
    *****/

    // 转换成非齐次坐标
    for ( int i=0; i<pts_4d.cols; i++ )
    {
        Mat x = pts_4d.col(i);
        x = x / x.at<float>(3,0);    // 归一化
        Point3d p (x.at<float>(0,0), x.at<float>(1,0), x.at<float>(2,0));
        points.push_back( p );
    }

}

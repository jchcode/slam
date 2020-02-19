#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/calib3d/calib3d.hpp>

using namespace std;
using namespace cv;

/****************************************************
    本程序演示了，根据得到的匹配点，使用2D-2D：对级约束来估计相机的运动
*****************************************************/



void pose_estimation_2d2d ( vector<KeyPoint> keypoints_1,
                            vector<KeyPoint> keypoints_2,
                            vector< DMatch > matches,
                            Mat& R, Mat& t )
{
    // 相机内参,TUM Freiburg2
    Mat K = ( Mat_<double> ( 3,3 ) << 520.9, 0, 325.1, 0, 521.0, 249.7, 0, 0, 1 );
    //fx = 520.9, fy = 521.0, cx = 325.1, cy = 249.7

    vector<Point2f> points1;
    vector<Point2f> points2;
    for ( int i = 0; i < ( int ) matches.size(); i++ )
    {
        //-- 把匹配点转换为vector<Point2f>的形式
        points1.push_back ( keypoints_1[matches[i].queryIdx].pt );
        points2.push_back ( keypoints_2[matches[i].trainIdx].pt );
    }



    //-- 第1步：计算基础矩阵
    Mat fundamental_matrix;
    fundamental_matrix = findFundamentalMat ( points1, points2, CV_FM_8POINT );
    /*****
    Mat findFundamentalMat( InputArray points1, InputArray points2,
                            int method = FM_8POINT,
                            OutputArray mask = noArray() );

    Method can be supported by OpenCV for computing a fundamental matrix.
    CV_FM_7POINT    for a 7-point algorithm.
    CV_FM_8POINT    for an 8-point algorithm.
    CV_FM_RANSAC    for the RANSAC algorithm.
    CV_FM_LMEDS     for the LMedS algorithm.
    *****/



    //-- 第2步：计算本质矩阵
    double focal_length = 521;			//相机焦距, TUM dataset标定值
    Point2d principal_point ( 325.1, 249.7 );	//相机光心, TUM dataset标定值
    Mat essential_matrix;
    essential_matrix = findEssentialMat ( points1, points2,
                                          focal_length, principal_point );
    /*****
    Mat findEssentialMat( InputArray points1, InputArray points2,
                          double focal = 1.0, Point2d pp = Point2d(0, 0),
                          int method = RANSAC, double prob = 0.999,
                          double threshold = 1.0, OutputArray mask = noArray() );
                          where pp is principle point of the camera

    Mat findEssentialMat( InputArray points1, InputArray points2,
                          InputArray cameraMatrix, int method = RANSAC,
                          double prob = 0.999, double threshold = 1.0,
                          OutputArray mask = noArray() );

    Method can be supported by OpenCV for computing a essential matrix.
    RANSAC    for the RANSAC algorithm.
    LMEDS     for the LMedS algorithm.
    *****/



    //-- 第3步：计算单应矩阵
    Mat homography_matrix;
    homography_matrix = findHomography ( points1, points2, RANSAC, 3 );
    /*****
    Mat findHomography( InputArray srcPoints, InputArray dstPoints,
                        int method = RANSAC, double threshold = 3.0);

    Method can be supported by OpenCV for computing a homography matrix.
    0       a regular method using all the points, i.e., the least squares method
    RANSAC  RANSAC-based robust method
    LMEDS   Least-Median robust method
    RHO     PROSAC-based robust method
    *****/



    //-- 第4步：从本质矩阵中恢复旋转和平移信息.
    recoverPose ( essential_matrix, points1, points2,
                  R, t, focal_length, principal_point );
    /*****
    int recoverPose( InputArray E, InputArray points1, InputArray points2,
                     OutputArray R, OutputArray t,
                     double focal = 1.0, Point2d pp = Point2d(0, 0),
                     InputOutputArray mask = noArray() );

    int recoverPose( InputArray E, InputArray points1, InputArray points2,
                     InputArray cameraMatrix, OutputArray R, OutputArray t,
                     InputOutputArray mask = noArray() );
    *****/

    return;

}

#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "myLibFunc.h"

using namespace std;
using namespace cv;



/****************************************************
    本程序演示了如何使用三角测量法
    根据相机的运动估计特征点的空间位置
*****************************************************/



int main ( int argc, char** argv )
{
    if ( argc != 3 )
    {
        cout<<"usage: pose_estimation_2d2d img1 img2"<<endl;
        return 1;
    }

    //-- 读取图像
    Mat img_1 = imread ( argv[1], CV_LOAD_IMAGE_COLOR );
    Mat img_2 = imread ( argv[2], CV_LOAD_IMAGE_COLOR );



    //-- 第1步：特征提取与匹配
    vector<KeyPoint> keypoints_1, keypoints_2;
    vector<DMatch> matches;
    find_feature_matches ( img_1, img_2, keypoints_1, keypoints_2, matches );
    cout<<"一共找到了"<<matches.size() <<"组匹配点"<<endl<<endl;



    //-- 第2步：使用2D-2D：对极约束估计两张图像间相机的运动
    Mat R,t;
    pose_estimation_2d2d ( keypoints_1, keypoints_2, matches, R, t );



    //-- 第3步：使用三角测量法估计特征点的空间位置
    vector<Point3d> points;
    triangulation(keypoints_1, keypoints_2, matches, R, t, points);



    //-- 验证特征点与三角化点的重投影（投影到归一化平面）关系
     Mat K = ( Mat_<double> ( 3,3 ) << 520.9, 0, 325.1, 0, 521.0, 249.7, 0, 0, 1 );
     for ( int i=0; i<matches.size(); i++ )
     {
         // 第一张图
         Point2f pt1_cam = pixel2cam( keypoints_1[ matches[i].queryIdx ].pt, K );
         Point2f pt1_cam_3d(points[i].x/points[i].z, points[i].y/points[i].z);
         cout<<"point in the first camera frame: "<<pt1_cam<<endl;
         cout<<"point projected from first frame: "<< \
                pt1_cam_3d<<", d="<<points[i].z<<endl;

         // 第二张图
         Point2f pt2_cam = pixel2cam( keypoints_2[ matches[i].trainIdx ].pt, K );
         Mat pt2_trans = R*( Mat_<double>(3,1) << points[i].x, \
                             points[i].y, points[i].z ) + t;
         Point2f pt2_cam_3d(pt2_trans.at<double>(0,0)/pt2_trans.at<double>(2,0),
                            pt2_trans.at<double>(1,0)/pt2_trans.at<double>(2,0));
         cout<<"point in the second camera frame: "<<pt2_cam<<endl;
         cout<<"point reprojected from second frame: "<< \
                pt2_cam_3d<<", d="<<pt2_trans.at<double>(2,0)<<endl;

        cout<<endl;
     }

     return 0;
}

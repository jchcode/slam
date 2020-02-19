#ifndef MYLIBFUNC_H_

#define MYLIBFUNC_H_

#include <opencv2/core/core.hpp>
using namespace cv;
using namespace std;

void find_feature_matches ( const Mat& img_1, const Mat& img_2,
                            vector<KeyPoint>& keypoints_1,
                            vector<KeyPoint>& keypoints_2,
                            vector< DMatch >& matches );

void pose_estimation_2d2d ( vector<KeyPoint> keypoints_1,
                            vector<KeyPoint> keypoints_2,
                            vector< DMatch > matches,
                            Mat& R, Mat& t );

Point2d pixel2cam ( const Point2d& p, const Mat& K );

void triangulation (
                     const vector< KeyPoint >& keypoint_1,
                     const vector< KeyPoint >& keypoint_2,
                     const vector< DMatch >& matches,
                     const Mat& R, const Mat& t,
                     vector< Point3d >& points );

#endif

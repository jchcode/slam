
#ifndef FUNFEATUREMATCH_H_
#define FUNFEATUREMATCH_H_

#include <opencv2/core/core.hpp>
using namespace std;
using namespace cv;

void find_feature_matches ( const Mat& img_1,
                            const Mat& img_2,
                            vector<KeyPoint>& keypoints_1,
                            vector<KeyPoint>& keypoints_2,
                            vector< DMatch >& matches );

void pose_estimation_2d2d ( vector<KeyPoint> keypoints_1,
                            vector<KeyPoint> keypoints_2,
                            vector< DMatch > matches,
                            Mat& R, Mat& t );

Point2d pixel2cam ( const Point2d& p, const Mat& K );

#endif

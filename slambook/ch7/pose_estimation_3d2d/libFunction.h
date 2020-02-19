#ifndef LIBFUNCTION_H_

#define LIBFUNCTION_H_


#include <opencv2/core/core.hpp>
using namespace std;
using namespace cv;

void find_feature_matches (
    const Mat& img_1, const Mat& img_2,
    std::vector<KeyPoint>& keypoints_1,
    std::vector<KeyPoint>& keypoints_2,
    std::vector< DMatch >& matches );

Point2d pixel2cam ( const Point2d& p, const Mat& K );

void bundleAdjustment (
    const vector<Point3f> points_3d,
    const vector<Point2f> points_2d,
    const Mat& K,
    Mat& R, Mat& t
);

#endif

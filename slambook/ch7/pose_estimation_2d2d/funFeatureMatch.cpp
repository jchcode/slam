#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/features2d/features2d.hpp>

using namespace std;
using namespace cv;

/****************************************************
    本程序演示了如何使用ORB特征进行特征提取与匹配

    本程序可能用到的数据结构的定义：

    KeyPoint(Point2f _pt, float _size, float _angle=-1,
             float _response=0, int _octave=0, int _class_id=-1);
    _pt         coordinate of the keypoint
    _size       keypoint diameter
    _angle      keypoint orientation
    _response   keypoint detector response on the keypoint
                (that is, strength of the keypoint)
    _octave     pyramid octave in which the keypoint has been detected
    _class_id   object id

    DMatch(int _queryIdx, int _trainIdx, int _imgIdx, float _distance);
    _queryIdx    query descriptor index
    _trainIdx    train descriptor index
    _imgIdx      train image index
    _distance    distance between descriptors.
*****************************************************/



void find_feature_matches ( const Mat& img_1, const Mat& img_2,
                            vector<KeyPoint>& keypoints_1,
                            vector<KeyPoint>& keypoints_2,
                            vector< DMatch >& matches )
{
    //-- 第1步:检测 Oriented FAST 关键点位置
    Ptr<FeatureDetector> detector = ORB::create();
    detector->detect ( img_1,keypoints_1 );
    detector->detect ( img_2,keypoints_2 );
    /*****
    void detect( InputArray image,
                 CV_OUT std::vector<KeyPoint>& keypoints,
                 InputArray mask=noArray() );
    *****/


    //-- 第2步:根据 Oriented FAST 关键点位置计算 BRIEF 描述子
    Mat descriptors_1, descriptors_2;
    Ptr<DescriptorExtractor> descriptor = ORB::create();
    descriptor->compute ( img_1, keypoints_1, descriptors_1 );
    descriptor->compute ( img_2, keypoints_2, descriptors_2 );
    /*****
    void compute( InputArray image,
                  CV_OUT CV_IN_OUT std::vector<KeyPoint>& keypoints,
                  OutputArray descriptors );
    *****/


    //-- 第3步:对两幅图像中的 BRIEF 描述子进行匹配，使用 Hamming 距离
    vector<DMatch> match;
    Ptr<DescriptorMatcher> matcher  = DescriptorMatcher::create ( "BruteForce-Hamming" );
    matcher->match ( descriptors_1, descriptors_2, match );
    /*****
    void match( InputArray queryDescriptors,
                InputArray trainDescriptors,
                CV_OUT std::vector<DMatch>& matches,
                InputArray mask=noArray() ) const;
    *****/

    //-- 第4步:匹配点对筛选
    double min_dist=10000, max_dist=0;

    //找出所有匹配之间的最小距离和最大距离, 即是最相似的和最不相似的两组点之间的距离
    for ( int i = 0; i < descriptors_1.rows; i++ )
    {
        double dist = match[i].distance;
        if ( dist < min_dist ) min_dist = dist;
        if ( dist > max_dist ) max_dist = dist;
    }

    //当描述子之间的距离大于两倍的最小距离时,即认为匹配有误.
    //但有时候最小距离会非常小,设置一个经验值30作为下限.
    for ( int i = 0; i < descriptors_1.rows; i++ )
    {
        if ( match[i].distance <= max ( 2*min_dist, 30.0 ) )
        {
            matches.push_back ( match[i] );
        }
    }

    return;
}

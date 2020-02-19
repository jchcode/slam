#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/features2d/features2d.hpp>

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

int main ( int argc, char** argv )
{
    if ( argc != 3 )
    {
        std::cout<<"usage: feature_extraction img1 img2"<<std::endl;
        return 1;
    }

    //-- 读取图像   CV_LOAD_IMAGE_COLOR -- 载入三通道彩色图像
    cv::Mat img_1 = cv::imread ( argv[1], CV_LOAD_IMAGE_COLOR );
    cv::Mat img_2 = cv::imread ( argv[2], CV_LOAD_IMAGE_COLOR );



    //-- 第1步:检测提取 Oriented FAST 角点位置
    std::vector<cv::KeyPoint> keypoints_1, keypoints_2;                 //定义关键点
    cv::Ptr<cv::FeatureDetector> detector = cv::ORB::create();          //关键点检测
    detector->detect ( img_1,keypoints_1 );     // -> 符号通过指针法操作
    detector->detect ( img_2,keypoints_2 );
    /*****
    void detect
    ( 
        InputArray image,
        CV_OUT std::vector<KeyPoint>& keypoints,
        InputArray mask=noArray()
    );
    *****/

    // 在img_1上显示输出关键点位置
    cv::Mat outimg1;
    drawKeypoints( img_1, keypoints_1, outimg1, 
                   cv::Scalar::all(-1), cv::DrawMatchesFlags::DEFAULT );
    // Scalar::all(-1) 表示颜色随机
    /*****
    void drawKeypoints
    ( 
        InputArray image,
        const std::vector<KeyPoint>& keypoints,
        InputOutputArray outImage,
        const Scalar& color=Scalar::all(-1),
        int flags=DrawMatchesFlags::DEFAULT 
    );
    *****/
    cv::imshow("ORB关键点",outimg1);



    //-- 第2步:根据关键点位置计算 Rotated BRIEF 描述子
    cv::Mat descriptors_1, descriptors_2;                               //定义描述子
    cv::Ptr<cv::DescriptorExtractor> descriptor = cv::ORB::create();    //描述子提取
    descriptor->compute ( img_1, keypoints_1, descriptors_1 );
    descriptor->compute ( img_2, keypoints_2, descriptors_2 );
    /*****
    void compute
    ( 
        InputArray image,
        CV_OUT CV_IN_OUT std::vector<KeyPoint>& keypoints,
        OutputArray descriptors 
    );
    *****/



    //-- 第3步:对两幅图像中提取的 Rotated BRIEF 描述子进行匹配，使用Hamming距离
    std::vector<cv::DMatch> matches;           //存储匹配信息的结构体
    cv::Ptr<cv::DescriptorMatcher> matcher = \
        cv::DescriptorMatcher::create ( "BruteForce-Hamming" );     //使用Hamming距离
    matcher->match ( descriptors_1, descriptors_2, matches );
    /*****
    void match
    ( 
        InputArray queryDescriptors,
        InputArray trainDescriptors,
        CV_OUT std::vector<DMatch>& matches,
        InputArray mask=noArray() 
    ) const;
    *****/



    //-- 第4步:匹配点对筛选（使用Hamming距离）
    double min_dist=10000, max_dist=0;
    // 找出所有匹配matches之间的最小距离和最大距离,即是最相似的和最不相似的两组点之间的距离，
    // 而两个二进制串匹配之间的距离指的是二进制不同的位数
    for ( int i = 0; i < descriptors_1.rows; i++ )
    {
        double dist = matches[i].distance;
        if ( dist < min_dist )
            min_dist = dist;
        if ( dist > max_dist )
            max_dist = dist;
    }

    // 仅供娱乐的写法
    min_dist = min_element( matches.begin(), matches.end(), [](const cv::DMatch& m1, \
         const cv::DMatch& m2) {return m1.distance<m2.distance;} )->distance;
    max_dist = max_element( matches.begin(), matches.end(), [](const cv::DMatch& m1, \
         const cv::DMatch& m2) {return m1.distance<m2.distance;} )->distance;
    std::cout<<"-- Max dist : "<<max_dist<<std::endl;
    std::cout<<"-- Min dist : "<<min_dist<<std::endl;
    std::cout<<std::endl;

    // 当描述子之间的距离大于两倍的最小距离时,即认为匹配有误，但有时候最小距离会非常小,设置一个经验值30作为下限
    // 汉明距离小于最小距离的两倍只是工程上的经验做法，即使如此依旧可能有误匹配，后期还需加入去除误匹配的算法
    std::vector< cv::DMatch > good_matches;
    for ( int i = 0; i < descriptors_1.rows; i++ )
        if ( matches[i].distance <= cv::max ( 2*min_dist, 30.0 ) )
            good_matches.push_back ( matches[i] );    //将元素添加到矩阵底部



    //-- 第5步:绘制匹配结果
    cv::Mat img_match;
    cv::Mat img_goodmatch;
    drawMatches ( img_1, keypoints_1, img_2, keypoints_2, matches, img_match );
    drawMatches ( img_1, keypoints_1, img_2, keypoints_2, good_matches, img_goodmatch );
    /*****
    void drawMatches
    ( 
        const Mat& img1,
        const vector<KeyPoint>& keypoints1,
        const Mat& img2,
        const vector<KeyPoint>& keypoints2,
        const vector<DMatch>& matches1to2,
        Mat& outIm,
        const Scalar& matchColor=Scalar::all(-1),
        const Scalar& singlePointColor=Scalar::all(-1),
        const vector<char>& matchesMask=vector<char>(),
        int flags=DrawMatchesFlags::DEFAULT 
    );
    *****/



    cv::imshow ( "所有匹配点对", img_match );
    cv::imshow ( "优化后匹配点对", img_goodmatch );
    cv::waitKey(0);

    return 0;
}

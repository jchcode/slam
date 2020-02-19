#include <iostream>
#include <chrono>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;

int main(int argc, char** argv)
{
    //读取argv[1]指定的图像
    Mat image;
    image = imread(argv[1]);
	//image = imread("ubuntu", ubuntu.png);

    //判断图像文件是否读取正确
    if (image.data == nullptr)
    {
	     cerr << "文件" << argv[1] << "不存在。" << endl;
	     return 0;
    }

    if (image.type() != CV_8UC1 && image.type() != CV_8UC3)
    {
        cout << "请输入一张灰色图像或彩色图像" << endl;
        return 0;
    }

    //文件读取顺利，输出图像的一些基本信息
    cout << "image_width = " << image.cols << endl;
    cout << "image_height = " << image.rows << endl;
    cout << "image_channel = " << image.channels() << endl;

    //使用std::chrono来给算法计时
    chrono::steady_clock::time_point t1 = chrono::steady_clock::now();

    //遍历图像，请注意以下的遍历方式也可用于随机访问
    for (size_t y=0; y<image.rows; y++)
    {
    	for (size_t x=0; x<image.cols; x++)
    	{
    	    //访问位于坐标(x,y)处的像素
    	    //用Mat::ptr获得图像的行指针
    	    uchar* row_ptr = image.ptr<uchar> (y);
    	    //指针指向代访问的数据
    	    uchar* data_ptr = &row_ptr[x*image.channels()];
    	    for (int c = 0; c != image.channels(); c++)
    	    {
          		//第c个通道的像素值
          		uchar data = data_ptr[c];
    	    }
    	}
    }

    chrono::steady_clock::time_point t2 = chrono::steady_clock::now();
    chrono::duration<double> time_used = chrono::duration_cast<\
    chrono::duration<double>>(t2 - t1);
    cout << "遍历图像用时" << time_used.count() << "秒。" << endl;

    imshow("image", image);
    waitKey(0);   //无限等待，按Enter键结束

    //关于Mat的拷贝，直接复制只复制头指针部分，并不复制数据部分
    Mat image_another = image;
    //故修改image_another会导致image发生变化
    //将图像左上角起100*100的方块像素值置为0
    image_another(Rect(0, 0, 100, 100)).setTo(0);

    imshow("image_another", image_another);
    waitKey(0);

    //要想对Mat进行拷贝，可使用clone来进行
    Mat image_clone = image.clone();
    image_clone(Rect(0, 0, 100, 100)).setTo(255);

    imshow("image", image);
	waitKey(0);
	
    imshow("image_clone", image_clone);
    waitKey(0);

    destroyAllWindows();

    return 0;

}


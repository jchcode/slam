#include <iostream>
#include <opencv2/core/core.hpp>
#include <ceres/ceres.h>
#include <chrono>

// 代价函数的计算模型
struct CURVE_FITTING_COST
{
    CURVE_FITTING_COST ( double x, double y ) : _x ( x ), _y ( y ) {}
    // 残差的计算
    template <typename T>
    bool operator() (
        const T* const abc,     // 模型参数，有3维
        T* residual ) const     // 残差
    {
        // y-exp(ax^2+bx+c)
        residual[0] = T ( _y ) - ceres::exp ( abc[0]*T ( _x ) *T ( _x ) + abc[1]*T ( _x ) + abc[2] ); 
        return true;
    }
    const double _x, _y;    // x,y数据
};

int main ( int argc, char** argv )
{
    double a=1.0, b=2.0, c=1.0;         // 真实参数值
    int N=100;                          // 数据点
    double w_sigma=1.0;                 // 噪声Sigma值
    cv::RNG rng;                        // OpenCV随机数产生器
    double abc[3] = {0,0,0};            // abc参数的估计值（设定的abc的初始值）
    std::vector<double> x_data, y_data;

    // 产生带有噪声的数据
    std::cout << "generating data: " << std::endl;
    for ( int i=0; i<N; i++ )
    {
        double x = i/100.0;
        x_data.push_back ( x );
        y_data.push_back ( exp ( a*x*x + b*x + c ) + rng.gaussian ( w_sigma ) );
        std::cout<< x_data[i] << " " << y_data[i] << std::endl; 
    }

    // 构建最小二乘问题
    ceres::Problem problem;
    for ( int i=0; i<N; i++ )
    {
        problem.AddResidualBlock 
        (     
            // 向问题中添加误差项
            // 使用自动求导，使用数值求导，自行推导解析的导数形式
            // 误差项和优化变量的维度：误差是标量，维度为1；优化的是abc三个量，维度为3
            new ceres::AutoDiffCostFunction<CURVE_FITTING_COST, 1, 3> ( new CURVE_FITTING_COST ( x_data[i], y_data[i] ) ),
            nullptr,            // 核函数，这里不使用，为空
            abc                 // 待估计参数
        );
    }

    // 配置求解器
    ceres::Solver::Options options;                     // 这里有很多配置项可以填
    options.linear_solver_type = ceres::DENSE_QR;       // 增量方程如何求解(采用QR分解)
    options.minimizer_progress_to_stdout = true;        // 输出到cout

    ceres::Solver::Summary summary;                     // 优化信息
    std::chrono::steady_clock::time_point t1 = std::chrono::steady_clock::now();
    ceres::Solve ( options, &problem, &summary );       // 开始优化
    std::chrono::steady_clock::time_point t2 = std::chrono::steady_clock::now();
    std::chrono::duration<double> time_used = std::chrono::duration_cast<std::chrono::duration<double>>( t2-t1 );
    std::cout<<"solve time cost = "<<time_used.count()<<" seconds. "<<std::endl;

    // 输出结果
    std::cout<<summary.BriefReport() <<std::endl;
    std::cout<<"estimated a,b,c = ";
    for ( auto a:abc ) 
        std::cout<<a<<" ";
    std::cout<<std::endl;

    return 0;
}


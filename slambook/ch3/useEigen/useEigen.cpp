#include <iostream>
#include <ctime>

//Eigen部分
#include <Eigen/Core>
#include <Eigen/Dense>   //稠密矩阵的代数运算

using namespace std;
using namespace Eigen;

#define MATRIX_SIZE 50

int main(int argc, char** aggv)
{
    //Eigen以矩阵为基本数据单元，它是一个模板类
    //前三个参数分别是：数据类型，行，列
    //同时，Eigen通过typedef提供了许多内置类型
    //不过底层仍是Eigen::Matrix

    //声明一个2*3的float类型矩阵
    Matrix<float, 2, 3> matrix_23;

    //Vector3d实质上是Eigen::Matrix<double, 3, 1>，声明一个三维向量
    Vector3d vector_3d;

    //Matrix3d实质上是Eigen::Matrix<double, 3, 3>，声明一个三维方阵
    Matrix3d matrix_33;

    //如果不确定矩阵大小，可以使用动态大小矩阵
    Matrix<double, Dynamic, Dynamic> matrix_dynamic;

    //矩阵的初始化操作
    matrix_23 << 1, 2, 3, 4, 5, 6;
    vector_3d << 7, 8, 9;
    matrix_33  = Matrix3d::Zero();

    cout << "matrix_23 = " << endl << matrix_23 << endl;
    cout << "vector_3d = " << endl << vector_3d << endl;
    cout << "matrix_33 = " << endl << matrix_33 << endl;

    //访问矩阵中的元素
    for (int i=0; i<2; i++)
	{
	    for (int j=0; j<3; j++)
	    {
            cout << "matrix_23(" << i+1 << ", " << j+1 << ") = " << matrix_23(i, j) << endl;
	    }
	}

    //矩阵和向量相乘本质上也是矩阵与矩阵相乘
    //除了要维度匹配外，还要数据类型一致，不一致要进行数据类型转换
    Matrix<double, 2, 1> result;
    result = matrix_23.cast<double>() * vector_3d;
    cout << "matrix_23 * vector_3d = " << endl << result << endl;

    //产生一个随机数矩阵
    Matrix3d matrix_ran = Matrix3d::Random();
    cout << "matrix_ran = " << endl << matrix_ran << endl;

    //矩阵的常见操作
    cout << "matrix_ran' = " << endl << matrix_ran.transpose() << endl;   //转置
    cout << "sum(matrix_ran) = " << endl << matrix_ran.sum() << endl;   //矩阵内所有元素之和
    cout << "tr(matrix_ran) = " << endl << matrix_ran.trace() << endl;   //迹
    cout << "inv(matrix_ran) = " << endl << matrix_ran.inverse() << endl;   //逆
    cout << "det(matrix_ran) = " << endl << matrix_ran.determinant() << endl;   //行列式

    //特征值与特征向量
    SelfAdjointEigenSolver<Matrix3d> eigen_solver( matrix_ran.transpose()*matrix_ran );
    //实对称矩阵可保证对角化成功
    cout << "Eigen_Values = \n" << eigen_solver.eigenvalues() << endl;
    cout << "Eigen_Vectors = \n" << eigen_solver.eigenvectors() << endl;

    //求解方程组：直接求解和QR分解法求解
    //比较两种方法求解所花的时间
    Matrix<double, MATRIX_SIZE, MATRIX_SIZE> matrix_Nd = MatrixXd::Random(MATRIX_SIZE, MATRIX_SIZE);     // 产生一个随机矩阵的第二种用法
    Matrix<double, MATRIX_SIZE, 1> vector_Nd = MatrixXd::Random(MATRIX_SIZE, 1);

    clock_t time_stt1 = clock();   //计时
    Matrix<double, MATRIX_SIZE, 1> x = matrix_Nd.inverse() * vector_Nd;
    double time_normal = 1000 * (clock() - time_stt1) / (double)CLOCKS_PER_SEC;
    cout << "time use in normal inverse is: " << time_normal << "ms" << endl;

    clock_t time_stt2 = clock();
    Matrix<double, MATRIX_SIZE, 1> y = matrix_Nd.colPivHouseholderQr().solve(vector_Nd);
    double time_Qr = 1000 * (clock() - time_stt2) / (double)CLOCKS_PER_SEC;
    cout << "time use in Qr decomposition is: " << time_Qr << "ms" << endl;

    return 0;
}

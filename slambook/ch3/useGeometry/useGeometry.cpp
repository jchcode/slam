#include <iostream>
#include <cmath>

#include <Eigen/Core>
#include <Eigen/Geometry>   //Eigen几何模块

using namespace std;
using namespace Eigen;

//本程序演示Eigen几何模块的使用方法

int main(int argc, char** argv)
{
	//旋转向量使用AngleAxisd，它的底层不直接是Matrix
	//但运算可以当作矩阵（因为重载了运算符）
	//此旋转向量是沿z轴旋转45度
	AngleAxisd rotation_vector(M_PI/4, Vector3d(0, 0, 1));

	//旋转矩阵使用Matrix3d或Matrix3f
	Matrix3d rotation_matrix = Matrix3d::Identity();   //用单位矩阵初始化
	//用matrix()将旋转向量转换成旋转矩阵
	rotation_matrix = rotation_vector.matrix();
	cout << "rotation_matrix = \n" << rotation_vector.matrix() << endl;
	//用toRotationMatrix()将旋转向量转换成旋转矩阵
	rotation_matrix = rotation_vector.toRotationMatrix();
	cout << "rotation_matrix = \n" << rotation_matrix << endl;

    //变换矩阵使用Isometry3d，虽称3d,实质上是4*4的矩阵
    Isometry3d T = Isometry3d::Identity();
    T.rotate(rotation_vector);   //旋转向量按照rotation_vector进行旋转
    T.pretranslate(Vector3d::Zero());   //平移向量设置为0

	//欧拉角使用Vector3d，将旋转矩阵转化为欧拉角
	Vector3d euler_angles = rotation_matrix.eulerAngles(0, 1, 2);
    //(0, 1, 2)是XYZ顺序，(2, 1, 0)是ZYX顺序
	cout << "(roll, pitch, yaw) = \n" << euler_angles << endl;

	//四元数使用Quaterniond，将旋转向量转化为四元数
	Quaterniond qua1 = Quaterniond(rotation_vector);
	cout << "quaternion1 = \n" << qua1.coeffs() << endl;   //虚部在前，实部在后
	//将旋转矩阵转化为四元数
	Quaterniond qua2 = Quaterniond(rotation_matrix);
	cout << "quaternion2 = \n" << qua2.coeffs() << endl;   //虚部在前，实部在后

    //试验所用的待旋转向量
	Vector3d vector_3d(1, 0, 0);
	Vector3d vector_3d_totated;

	//使用旋转向量进行旋转
	vector_3d_totated = rotation_vector * vector_3d;
	cout << "(1, 0, 0) after rotation = \n" << vector_3d_totated << endl;

	//使用旋转矩阵进行旋转
	vector_3d_totated = rotation_matrix * vector_3d;
	cout << "(1, 0, 0) after rotation = \n" << vector_3d_totated << endl;

	//用变换矩阵进行坐旋转
	Eigen::Vector3d vector_transformed = T * vector_3d;
	cout << "vector_transformed = \n" << vector_transformed << endl;

	//使用四元数进行旋转
	vector_3d_totated = qua1 * vector_3d;
	cout << "(1, 0, 0) after rotation = \n" << vector_3d_totated << endl;

	return 0;
}

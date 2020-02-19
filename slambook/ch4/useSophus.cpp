#include <iostream>
#include <cmath>

#include <Eigen/Core>
#include <Eigen/Geometry>

#include "sophus/so3.h"
#include "sophus/se3.h"

using namespace std;
using namespace Eigen;
using namespace Sophus;

int main( int argc, char** argv )
{
	//沿着z轴旋转90度的旋转矩阵
	AngleAxisd  rotation_vector(M_PI/2, Vector3d(0,0,1));    			 //旋转向量
	Matrix3d    rotation_matrix = rotation_vector.toRotationMatrix();    //旋转矩阵
	Quaterniond q = Quaterniond(rotation_matrix);    					 //四元数 
	
	SO3 SO3_v(0, 0, M_PI/2);    	//特殊正交群SO(3)可由旋转向量构建
	SO3 SO3_R(rotation_matrix);     //特殊正交群SO(3)可由旋转矩阵构建
	SO3 SO3_q(q);                   //特殊正交群SO(3)可由四元数构建

	//输出SO(3)时，以so(3)形式输出
	//上述三种SO(3)的表达方式都是等价的
	cout << "SO(3) from rotation_vector:" << SO3_v << endl;
	cout << "SO(3) from rotation_matrix:" << SO3_R << endl;
	cout << "SO(3) from quaterniond:" << SO3_q << endl;

	//对于特殊正交群使用对数映射得到它对应的李代数
	Vector3d so3 = SO3_R.log();
	cout << "so(3) from SO(3):" << so3.transpose() << endl << endl;

	//hat由向量到反对称矩阵，vee由反对称矩阵到向量
	cout << "so3 hat:" << endl << SO3::hat(so3) << endl << endl;
	cout << "so3 vee:" << endl << SO3::vee(SO3::hat(so3)) << endl << endl;
	
	//增量扰动模型的更新
	Vector3d update_so3(1e-4, 0, 0);
	SO3 SO3_update = SO3::exp(update_so3) * SO3_R;    //左乘更新
	cout << "SO3 update:" << SO3_update << endl;


	/*******************分割线*******************/
	cout << "***********我是分割线***********" << endl << endl;


	//对SE(3)的操作大同小异
	Vector3d t(1, 0, 0);    			//平移向量，沿x轴平移1个单位
	SE3 SE3_Rt(rotation_matrix, t);		//由旋转矩阵和平移向量构造SE(3)
	SE3 SE3_qt(q, t);					//由四元数和平移向量构造SE(3)

	//输出SE(3)，输出一个2×3的矩阵，第一个行向量是旋转向量，第二个行向量是平移向量
	cout << "SE3 from R,t:" << endl << SE3_Rt << endl;
	cout << "SE3 from q,t:" << endl << SE3_qt << endl;

	typedef Matrix<double, 6, 1> Vector6d;

	//对特殊欧式群使用对数映射得到它对应的李代数
	Vector6d se3 = SE3_Rt.log();
	cout << "se(3) from SE(3)" << se3.transpose() << endl << endl;

	//hat由向量到反对称矩阵，vee由反对称矩阵到向量
	cout << "se3 hat:" << endl << SE3::hat(se3) << endl << endl;
	cout << "se3 vee:" << endl << SE3::vee(SE3::hat(se3)) << endl << endl;

	//增量扰动模型的更新
	Vector6d update_se3;
	update_se3.setZero();
	cout << update_se3 << endl;
	update_se3(0, 0) = 1e-4d;    //1e-4类型转换为double类型
	SE3 SE3_update = SE3::exp(update_se3) * SE3_Rt;
	cout << "SE3_update:" << endl << SE3_update << endl;

	return 0;		
 }

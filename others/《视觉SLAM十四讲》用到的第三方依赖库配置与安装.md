# 《视觉SLAM十四讲》用到的第三方依赖库配置与安装  
<br>



**以下所有的操作指令依赖的操作系统是Ubuntu 16.04LTS。**
<br>



## Eigen
Eigen is a C++ template library for linear algebra.
**1.  安装方法**
```shell
sudo apt install libeigen3-dev
```
**2. 安装位置**
Eigen是一个纯用头文件搭建起来的库（没有库文件），其头文件的默认位置在`/usr/include/eigen3`。
<br>



## Pangolin
Pangolin is a lightweight portable rapid development library for managing OpenGL display / interaction and abstracting video input.
**1.  安装方法**
```shell
git clone https://github.com/stevenlovegrove/Pangolin.git    
cd [path-to-Pangolin]
 
# required dependencies  
sudo apt install libgl1-mesa-dev libglew-dev cmake  

# recommneded dependencies      
sudo apt install libpython2.7-dev python-pip           
git submodule init && git submodule update                    # for pybind11
sudo python -mpip install numpy pyopengl Pillow pybind11      # useful modules            
sudo apt install pkg-config                                   # pkg-config
sudo apt install libegl1-mesa-dev libwayland-dev libxkbcommon-dev wayland-protocols     # Wayland and EGL

# very optional dependencies: Eigen, CUDA Toolkit, Doxygen
              
# building and installing               
mkdir build
cd build                                      
cmake ..
cmake --build .
cmake --build . --target doc     # build the documentation and you have Doxygen installed
sudo make install
```
**2. 安装位置**
头文件的默认位置在`/usr/local/include/pango`，库文件的默认位置在`/usr/lib/x86_64-linux-gnu`下。
<br>



## Sophus
Sophus is a C++ implementation of Lie groups commonly used for 2d or 3d geometric problems.
**1.  安装方法**
```shell
git clone https://github.com/strasdat/Sophus.git
cd [path-to-Sophus]
git checkout a621ff			# 将Sophus库切换到非模板类/双精度版本
mkdir build
cd build
cmake ..                            
make                        # Sophus库只需编译无需安装（编译的build文件夹不可删除）
# 可能遇见的错误解决方案参考：https://github.com/uzh-rpg/rpg_svo/issues/237
```
**2. 安装位置**
头文件的默认位置在`[path-to-Sophus]/sophus`，库文件的默认位置在`[path-to-Sophus]/build`下，我们可找到名为libSophus.so的库文件。
<br>



## OpenCV
OpenCV is a library of programming functions mainly aimed at computer vision.
**1.  安装方法**
```shell
git clone https://github.com/opencv/opencv.git
cd [path-to-OpenCV]
git checkout 3.4.3     # 将openCV退回到你想要的版本，此处退回到 openCV 3.4.3

# required packages
sudo apt install build-essential     # compiler            
sudo apt install cmake git libgtk2.0-dev pkg-config libavcodec-dev libavformat-dev libswscale-dev     # required
sudo apt install python-dev python-numpy libtbb2 libtbb-dev libjpeg-dev libpng-dev libtiff-dev libjasper-dev libdc1394-22-dev     # optional

# building and installing
mkdir build
cd build
cmake -D CMAKE_BUILD_TYPE=Release -D CMAKE_INSTALL_PREFIX=/usr/local ..
make -j12     # 取决于你CPU的线程数			
sudo make install
```
**2. 安装位置**
头文件的默认位置在`/usr/local/include`，我们我可以看到opencv和opencv2两个文件夹里存放着头文件，库文件的默认位置在`/usr/local/lib`下。
<br>



## PCL
The Point Cloud Library (PCL) is a standalone, large scale, open project for 2D/3D image and point cloud processing.
**1.  安装方法**
```shell
sudo apt install libpcl-dev
sudo apt install pcl-tools      # 安装用来打开pcd文件的可视化工具：pcl_viewer xxx.pcd
```
**2. 安装位置**
头文件的默认位置在`/usr/include/pcl-1.7`，库文件的默认位置在`/usr/lib/x86_64-linux-gnu`下。
<br>



## Ceres Solver
Ceres Solver is an open source C++ library for modeling and solving large, complicated optimization problems. Ceres Solver can solve two kinds of problems: Non-linear Least Squares problems with bounds constraints; General unconstrained optimization problems.
**1.  安装方法**
```shell
git clone https://github.com/ceres-solver/ceres-solver.git
cd [path-to-ceres-solver]

# dependencies
sudo apt install cmake libeigen3-dev 
sudo apt install libgoogle-glog-dev libatlas-base-dev libsuitesparse-dev

# building and installing
mkdir build
cd build
cmake ..
make -j12
sudo make install
```
**2. 安装位置**
头文件的默认位置在`/usr/local/include/ceres`，库文件的默认位置在`/usr/local/lib`下，我们可找到名为libceres.a的库文件。
<br>



## g2o
g2o(general graph optimization) is an open-source C++ framework for optimizing graph-based nonlinear error functions. The current implementation provides solutions to several variants of SLAM and BA.
**1. 安装方法**
```shell
git clone https://github.com/RainerKuemmerle/g2o.git
cd [path-to-g2o]

# dependencies
sudo apt install cmake libeigen3-dev 
sudo apt install libsuitesparse-dev qtdeclarative5-dev qt5-qmake libqglviewer-dev

# building and installing
mkdir build
cd build
cmake ..
make -j12
sudo make install
```
**2. 安装位置**
头文件的默认位置在`/usr/local/include/g2o`，库文件的默认位置在`/usr/local/lib`。
<br>



## 参考
[1] [Installing Dependencies on Ubuntu 16.04 LTS towards SLAM Projects (Updating)](https://youjiexia.github.io/2018/03/10/Installing-Dependencies-on-Ubuntu-towards-SLAM-Projects/)
[2] [GitHub: Connecting to GitHub with SSH](https://help.github.com/en/articles/connecting-to-github-with-ssh)
[3] [廖雪峰的Git教程：添加远程库](https://www.liaoxuefeng.com/wiki/0013739516305929606dd18361248578c67b8067c8c017b000/0013752340242354807e192f02a44359908df8a5643103a000)
[4] [廖雪峰的Git教程：从远程库克隆](https://www.liaoxuefeng.com/wiki/0013739516305929606dd18361248578c67b8067c8c017b000/001375233990231ac8cf32ef1b24887a5209f83e01cb94b000)
[5] [Eigen: Getting started](http://eigen.tuxfamily.org/dox/GettingStarted.html)
[6] [Pangolin Official Website](https://github.com/stevenlovegrove/Pangolin)
[7] [Sophus Official Website](https://github.com/strasdat/Sophus)
[8] [OpenCV: Installation in Linux ](https://docs.opencv.org/3.4.3/d7/d9f/tutorial_linux_install.html)
[9] [PCL Official Website](http://pointclouds.org/)
[10] [Ceres-Solver Official Website](http://ceres-solver.org/)
[11] [g2o Official Website](https://github.com/RainerKuemmerle/g2o)
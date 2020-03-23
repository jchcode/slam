# 安装配置Intel Realsense D435i并在其上跑ORB-SLAM2  
<br>



**配置安装环境：Ubuntu16.04LTS, Linux Kernel 4.15**
<br>



## 一、安装Intel Realsense SDK
**方式一** —— 直接安装官方已经编译好的包，可参考[教程](https://github.com/IntelRealSense/librealsense/blob/master/doc/distribution_linux.md)
```shell
# Register the server's public key
sudo apt-key adv --keyserver keys.gnupg.net --recv-key C8B3A55A6F3EFCDE || sudo apt-key adv --keyserver hkp://keyserver.ubuntu.com:80 --recv-key C8B3A55A6F3EFCDE
# Add the server to the list of repositories
sudo add-apt-repository "deb http://realsense-hw-public.s3.amazonaws.com/Debian/apt-repo xenial main" -u
# Install the libraries
sudo apt install librealsense2-dkms
sudo apt install librealsense2-utils
# Optionally install the developer and debug packages
sudo apt install librealsense2-dev
sudo apt install librealsense2-dbg
# Reconnect the Intel RealSense depth camera and run: realsense-viewer to verify the installation.
```
**方式二** —— 下载源代码自行编译安装，可参考[教程](https://github.com/IntelRealSense/librealsense/blob/master/doc/installation.md)
```shell
# ***************************Prerequisites***************************** #
# Update Ubuntu distribution, including getting the latest stable kernel
sudo apt update && sudo apt upgrade && sudo apt dist-upgrade
# Download the complete source tree with git
git clone https://github.com/IntelRealSense/librealsense.git
# Navigate to librealsense root directory and Unplug any connected Intel RealSense camera
# Install the core packages required to build librealsense binaries and the affected kernel modules
sudo apt install git libssl-dev libusb-1.0-0-dev pkg-config libgtk-3-dev
sudo apt install libglfw3-dev libgl1-mesa-dev libglu1-mesa-dev
# certain librealsense CMAKE flags (e.g. CUDA) require version 3.8+(check: cmake --version)
# Run Intel Realsense permissions script located from librealsense root directory
./scripts/setup_udev_rules.sh
# Build and apply patched kernel modules
./scripts/patch-realsense-ubuntu-lts.sh
# Tracking Module requires hid_sensor_custom kernel module to operate properly.
echo 'hid_sensor_custom' | sudo tee -a /etc/modules

# ***************************Building and Installing librealsense2 SDK***************************** #
# Navigate to librealsense root directory
mkdir build && cd build
# Builds librealsense along with the demos and tutorials
cmake ../ -DBUILD_EXAMPLES=true
# Recompile and install librealsense binaries
sudo make uninstall && make clean && make -jX && sudo make install
# Use make -jX for parallel compilation, where X stands for the number of CPU cores available
# The shared object will be installed in /usr/local/lib, header files in /usr/local/include
# The binary demos, tutorials and test files will be copied into /usr/local/bin

# ***************************Testing librealsense2 SDK***************************** #
# Navigate to librealsense root directory
 cd build/examples/capture
./rs-capture 
```
<br>



## 二、安装ROS Wrapper for Intel RealSense
可参考[教程](https://github.com/IntelRealSense/realsense-ros)
```shell
# Step 1: Install the latest Intel RealSense SDK

# Step 2: Install the ROS Kinetic --- http://wiki.ros.org/kinetic/Installation/Ubuntu

# Step 3: Install Intel RealSense ROS from Sources
# Create a catkin workspace
mkdir -p ~/catkin_ws/src
cd ~/catkin_ws/src/
# Clone the latest Intel RealSense ROS into 'catkin_ws/src/'
git clone https://github.com/IntelRealSense/realsense-ros.git
cd realsense-ros/
git checkout `git tag | sort -V | grep -P "^\d+\.\d+\.\d+" | tail -1`
cd ../..
# Make sure all dependent ros packages are installed. You can check .travis.yml file for reference.
sudo apt install ros-kinetic-cv-bridge ros-kinetic-image-transport ros-kinetic-tf ros-kinetic-diagnostic-updater ros-kinetic-ddynamic-reconfigure
catkin_make -DCATKIN_ENABLE_TESTING=False -DCMAKE_BUILD_TYPE=Release
catkin_make install
echo source $(pwd)/devel/setup.bash >> ~/.bashrc
source ~/.bashrc

# Step 4:检验是否能在ros使用realsense相机：
# 通过usb连接相机到电脑
sudo apt install ros-kinetic-rgbd-launch
roslaunch realsense2_camera rs_rgbd.launch
# 查看一下相机发布的topic
rostopic list
# 查看相机内参信息的两种方式
rostopic echo /camera/color/camera_info
rostopic echo /camera/aligned_depth_to_color/camera_info
# 再打开一个终端
rviz
# 此时并不能看到什么结果，左上角 Displays 中 Fixed Frame 选项中，下拉菜单选择 camera_link，这是主要到Global Status变成了绿色
# 点击该框中的Add -> 上方点击 By topic -> /depth_registered 下的 /points 下的/PointCloud2
# 点击该框中的Add -> 上方点击 By topic -> /color 下的 /image_raw 下的image
```
<br>



## 三、使用公开数据集配置测试ORB_SLAM2
可参考[教程](https://github.com/raulmur/ORB_SLAM2)
```shell
# Prerequisites
# Pangolin, OpenCV, Eigen3 安装见我的另一篇文章：https://blog.csdn.net/jiangchuanhu/article/details/89163864

# Building ORB-SLAM2 library and examples
git clone https://github.com/raulmur/ORB_SLAM2.git ORB_SLAM2
cd ORB_SLAM2 && chmod +x build.sh && ./build.sh
# 编译时可能遇到的错误参考：https://github.com/raulmur/ORB_SLAM2/issues/337

# 使用网上公开的数据集测试ORB_SLAM2

# 1、Monocular Examples --- TUM Dataset
# Download a sequence from http://vision.in.tum.de/data/datasets/rgbd-dataset/download and uncompress it.
# Change TUMX.yaml to TUM1.yaml,TUM2.yaml or TUM3.yaml for freiburg1, freiburg2 and freiburg3 sequences respectively. Change PATH_TO_SEQUENCE_FOLDERto the uncompressed sequence folder.
./Examples/Monocular/mono_tum Vocabulary/ORBvoc.txt Examples/Monocular/TUMX.yaml PATH_TO_SEQUENCE_FOLDER

# 3、RGB-D Example --- TUM Dataset
# Download a sequence from http://vision.in.tum.de/data/datasets/rgbd-dataset/download and uncompress it.
# We already provide associations for some of the sequences in Examples/RGB-D/associations/. You can generate your own associations file executing:
python associate.py PATH_TO_SEQUENCE/rgb.txt PATH_TO_SEQUENCE/depth.txt > associations.txt
# Execute the following command. Change TUMX.yaml to TUM1.yaml,TUM2.yaml or TUM3.yaml for freiburg1, freiburg2 and freiburg3 sequences respectively. Change PATH_TO_SEQUENCE_FOLDERto the uncompressed sequence folder. Change ASSOCIATIONS_FILE to the path to the corresponding associations file.
./Examples/RGB-D/rgbd_tum Vocabulary/ORBvoc.txt Examples/RGB-D/TUMX.yaml PATH_TO_SEQUENCE_FOLDER ASSOCIATIONS_FILE
```
<br>



## 四、在D435i设备上配置跑通ORB_SLAM2
可参考[教程](https://github.com/raulmur/ORB_SLAM2)
```shell
# Add the path including Examples/ROS/ORB_SLAM2 to the ROS_PACKAGE_PATH environment variable. 
# Open .bashrc file and add at the end the following line. Replace PATH by the folder where you cloned ORB_SLAM2
export ROS_PACKAGE_PATH=${ROS_PACKAGE_PATH}:PATH/ORB_SLAM2/Examples/ROS
# Execute build_ros.sh script
chmod +x build_ros.sh
./build_ros.sh
# 编译时可能遇到的错误参考：https://github.com/raulmur/ORB_SLAM2/issues/337
```
上述步骤中在执行`./build_ros.sh`出现关于boost库的错误时，在`/Examples/ROS/ORB-SLAM2/CMakeLists.txt`文件下修改，加上`-lboost_system`，然后重新执行`./build_ros.sh`
```shell
set(LIBS 
${OpenCV_LIBS} 
${EIGEN3_LIBS}
${Pangolin_LIBRARIES}
${PROJECT_SOURCE_DIR}/../../../Thirdparty/DBoW2/lib/libDBoW2.so
${PROJECT_SOURCE_DIR}/../../../Thirdparty/g2o/lib/libg2o.so
${PROJECT_SOURCE_DIR}/../../../lib/libORB_SLAM2.so
-lboost_system              # here
)
```
按照以下步骤我们可获取相机参数，通过usb连接相机到电脑，然后执行
```shell
roslaunch realsense2_camera rs_rgbd.launch
rostopic echo /camera/color/camera_info
```
它的数据结构形式如下：
```shell
---
header: 
  seq: 17
  stamp: 
    secs: 1560907148
    nsecs: 588988566
  frame_id: "camera_color_optical_frame"
height: 480
width: 640
distortion_model: "plumb_bob"
D: [0.0, 0.0, 0.0, 0.0, 0.0]
K: [615.9417724609375, 0.0, 322.3533630371094, 0.0, 616.0935668945312, 240.44674682617188, 0.0, 0.0, 1.0]
R: [1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0]
P: [615.9417724609375, 0.0, 322.3533630371094, 0.0, 0.0, 616.0935668945312, 240.44674682617188, 0.0, 0.0, 0.0, 1.0, 0.0]
binning_x: 0
binning_y: 0
roi: 
  x_offset: 0
  y_offset: 0
  height: 0
  width: 0
  do_rectify: False
---
```
根据网上看到的[参考文章1](https://impulsiverobotics.com/2018/04/ros-enabled-omnidirectional-robot/)、[参考文章2](https://github.com/IntelRealSense/librealsense/blob/165ae36b350ca950e4180dd6ca03ca6347bc6367/third-party/realsense-file/rosbag/msgs/sensor_msgs/CameraInfo.h#L268)，我们根据D435i的相机参数写出对应的D435i.yaml文件，相对于ORB-SLAM2中的yaml文件，主要修改相机参数Camera Parameters部分。
```shell
%YAML:1.0

#--------------------------------------------------------------------------------------------
# Camera Parameters. Adjust them!
#--------------------------------------------------------------------------------------------

# Camera calibration and distortion parameters (OpenCV) 
Camera.fx: 615.9417724609375
Camera.fy: 616.0935668945312
Camera.cx: 322.3533630371094
Camera.cy: 240.44674682617188

Camera.k1: 0.0
Camera.k2: 0.0
Camera.p1: 0.0
Camera.p2: 0.0
Camera.p3: 0.0

Camera.width: 640
Camera.height: 480

# Camera frames per second 
Camera.fps: 30.0

# IR projector baseline times fx (aprox.)
# bf = baseline (in meters) * fx, D435i的 baseline = 50 mm 
Camera.bf: 30.797   

# Color order of the images (0: BGR, 1: RGB. It is ignored if images are grayscale)
Camera.RGB: 1

# Close/Far threshold. Baseline times.
ThDepth: 40.0

# Deptmap values factor
DepthMapFactor: 1000.0

#--------------------------------------------------------------------------------------------
# ORB Parameters
#--------------------------------------------------------------------------------------------

# ORB Extractor: Number of features per image
ORBextractor.nFeatures: 1000

# ORB Extractor: Scale factor between levels in the scale pyramid 	
ORBextractor.scaleFactor: 1.2

# ORB Extractor: Number of levels in the scale pyramid	
ORBextractor.nLevels: 8

# ORB Extractor: Fast threshold
# Image is divided in a grid. At each cell FAST are extracted imposing a minimum response.
# Firstly we impose iniThFAST. If no corners are detected we impose a lower value minThFAST
# You can lower these values if your images have low contrast			
ORBextractor.iniThFAST: 20
ORBextractor.minThFAST: 7

#--------------------------------------------------------------------------------------------
# Viewer Parameters
#--------------------------------------------------------------------------------------------
Viewer.KeyFrameSize: 0.05
Viewer.KeyFrameLineWidth: 1
Viewer.GraphLineWidth: 0.9
Viewer.PointSize:2
Viewer.CameraSize: 0.08
Viewer.CameraLineWidth: 3
Viewer.ViewpointX: 0
Viewer.ViewpointY: -0.7
Viewer.ViewpointZ: -1.8
Viewer.ViewpointF: 500
```
摄像头节点发布的rgbd图和depth图话题名与ORB-SLAM2的订阅RGB图和depth图话题名不同，在ORB-SLAM2/Examples/ROS/ORB-SLAM2/src中修改ros_rgbd.cc的topic订阅
```shell
message_filters::Subscriber<sensor_msgs::Image> rgb_sub(nh, "/camera/color/image_raw", 1);
message_filters::Subscriber<sensor_msgs::Image> depth_sub(nh, "/camera/aligned_depth_to_color/image_raw", 1);
```
最后在ORB_SLAM2工作目录下
```shell
# 重新编译build_ros.sh
chmod +x build_ros.sh
./build_ros.sh
# 运行ORB_SLAM2
rosrun ORB_SLAM2 RGBD Vocabulary/ORBvoc.txt Examples/RGB-D/D435i.yaml
```
# EUROC格式转ROSBAG

## 安装编译

```
mkdir -p ~/catkin_ws/src
cd ~/catkin_ws/src
git clone git@github.com:Jerry-locker/rosbag_make.git
cd ..
catkin_make
```

## 运行

```
修改config.yaml文件中的cam_path、imu_path、image_topic、imu_topic、tobag_path
cd ~/catkin_ws
source devel/setup.bash
roslaunch rosbag_make rosbag_make.launch
```

# 注意事项

1.ROS时间戳转换

```
//ros时间戳转为浮点格式
double time = ros::Time::now().toSec();

//浮点格式转为ros时间戳
img_msg.header.stamp = ros::Time.fromSec(time);
```

2.csv文件读写

data.csv用gedit打开，euroc时间显示的是19位的纳秒，如果用excel打开则是科学计数法。

csv文件其实就是文本文件，每行字段用逗号分隔，每行最后一个元素会带一个换行符。

3.cv::imread

用cv::imread读图时一定要加cv::IMREAD_UNCHANGED防止改变图像通道数，否则灰度图很有可能由原本的单通道变为三通道。

4.ros消息智能指针

```
sensor_msgs::ImuPtr imu_msg(new sensor_msgs::Imu); //即使是ros的智能指针也要new
```
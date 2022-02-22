#include <stdio.h>
#include <fstream>
#include <ros/ros.h>
#include <rosbag/bag.h>
#include <rosbag/view.h>
#include <std_msgs/Header.h>
#include <sensor_msgs/Imu.h>
#include <sensor_msgs/PointCloud2.h>
#include <sensor_msgs/Image.h>
#include <sensor_msgs/image_encodings.h>
#include <cv_bridge/cv_bridge.h>

#include "parameters.h"

int main(int argc, char** argv)
{
  ros::init(argc, argv, "rosbag_make");
  ros::NodeHandle n("~");
  readParameters(n);

  rosbag::Bag newbag;
  newbag.open(TOBAG_PATH, rosbag::bagmode::Write);

  ///save image to bag
  std::string cam_data_csv = CAM_PATH + "/data.csv";
  std::fstream cam_file(cam_data_csv);
  //scan every line
  std::string current_line_cam;
  while (std::getline(cam_file, current_line_cam))
  {
    std::stringstream sline(current_line_cam);
    std::string element;
    std::vector<std::string> vec;

    while (std::getline(sline, element, ','))
    {
      if (element.empty())
        continue;
      vec.push_back(element);
    }

    assert(vec.size() == 2);
    long timestamp = std::stol(vec[0]);
    std::string pic_path = CAM_PATH + "/data/" + vec[1].substr(0, vec[1].size() - 1); //vec[1]尾部带有换行符

    cv::Mat image = cv::imread(pic_path, cv::IMREAD_UNCHANGED); //不要改变通道数
    //std::cout << image.type() << std::endl;
    if (image.data == nullptr)
    {
      std::cout << "文件" << pic_path << "不存在\n";
      ros::shutdown();
    }
    std_msgs::Header header;
    header.stamp = ros::Time().fromNSec(timestamp);
    sensor_msgs::ImagePtr img_msg = cv_bridge::CvImage(header, "mono8", image).toImageMsg();

    newbag.write(IMAGE_TOPIC, img_msg->header.stamp, img_msg);
  }

  ///save imu to bag
  std::string imu_data_csv = IMU_PATH + "/data.csv";
  std::fstream imu_file(imu_data_csv);
  //scan every line
  std::string current_line_imu;
  while (std::getline(imu_file, current_line_imu))
  {
    static int cnt = 0;
    cnt++;
    if (cnt == 1)
      continue;

    std::stringstream sline(current_line_imu);
    std::string element;
    std::vector<std::string> vec;

    while (std::getline(sline, element, ','))
    {
      if (element.empty())
        continue;
      vec.push_back(element);
    }

    assert(vec.size() == 7);
    long timestamp = std::stol(vec[0]);

    sensor_msgs::ImuPtr imu_msg(new sensor_msgs::Imu); //即使是ros的智能指针也要new
    imu_msg->header.stamp = ros::Time().fromNSec(timestamp);
    imu_msg->angular_velocity.x = std::stof(vec[1]);
    imu_msg->angular_velocity.y = std::stof(vec[2]);
    imu_msg->angular_velocity.z = std::stof(vec[3]);
    imu_msg->linear_acceleration.x = std::stof(vec[4]);
    imu_msg->linear_acceleration.y = std::stof(vec[5]);
    imu_msg->linear_acceleration.z = std::stof(vec[6]);

    newbag.write(IMU_TOPIC, imu_msg->header.stamp, imu_msg);

//    sensor_msgs::Imu imu_msg;
//    imu_msg.header.stamp = ros::Time().fromNSec(timestamp);
//    imu_msg.angular_velocity.x = std::stof(vec[1]);
//    imu_msg.angular_velocity.y = std::stof(vec[2]);
//    imu_msg.angular_velocity.z = std::stof(vec[3]);
//    imu_msg.linear_acceleration.x = std::stof(vec[4]);
//    imu_msg.linear_acceleration.y = std::stof(vec[5]);
//    imu_msg.linear_acceleration.z = std::stof(vec[6].substr(0, vec[6].size() - 1));

    //newbag.write(IMU_TOPIC, imu_msg->header.stamp, imu_msg);
  }


  newbag.close();

  std::cout << "[make bag ok]\n";

  return 0;
}

#pragma once

#include <ros/ros.h>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>

extern std::string CAM_PATH;
extern std::string IMU_PATH;

extern std::string IMAGE_TOPIC;
extern std::string IMU_TOPIC;
extern std::string TOBAG_PATH;

void readParameters(ros::NodeHandle &n);

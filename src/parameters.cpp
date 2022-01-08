#include "parameters.h"

std::string CAM_PATH;
std::string IMU_PATH;

std::string IMAGE_TOPIC;
std::string IMU_TOPIC;
std::string TOBAG_PATH;

template <typename T>
T readParam(ros::NodeHandle &n, std::string name)
{
  T ans;
  if (n.getParam(name, ans))
  {
    ROS_INFO_STREAM("Loaded " << name << ": " << ans);
  }
  else
  {
    ROS_ERROR_STREAM("Failed to load " << name);
    n.shutdown();
  }
  return ans;
}

void readParameters(ros::NodeHandle &n)
{
  std::string config_file = readParam<std::string>(n, "config_file");
  std::cout << "[config_file] " << config_file << std::endl;
  cv::FileStorage fsSettings(config_file, cv::FileStorage::READ);
  if(!fsSettings.isOpened())
  {
      std::cerr << "ERROR: Wrong path to settings" << std::endl;
  }

  fsSettings["cam_path"] >> CAM_PATH;
  fsSettings["imu_path"] >> IMU_PATH;

  fsSettings["image_topic"] >> IMAGE_TOPIC;
  fsSettings["imu_topic"] >> IMU_TOPIC;
  fsSettings["tobag_path"] >> TOBAG_PATH;
}

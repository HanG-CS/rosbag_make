cmake_minimum_required(VERSION 3.0.2)
project(rosbag_make)

find_package(catkin REQUIRED COMPONENTS
  cv_bridge
  rosbag
  roscpp
  std_msgs
)

find_package(Eigen3 REQUIRED)
find_package(OpenCV REQUIRED)

catkin_package(
)

include_directories(
  ${catkin_INCLUDE_DIRS}
  ${EIGEN3_INCLUDE_DIR}
  ${OpenCV_INCLUDE_DIRS}
)

add_executable(rosbag_make
               src/rosbag_make.cpp
               src/parameters.cpp)
target_link_libraries(rosbag_make ${catkin_LIBRARIES} ${OpenCV_LIBS})



/*
 * TraversabilityChecker.hpp
 *
 *  Created on: Mar 24, 2015
 *      Author: Péter Fankhauser
 *   Institute: ETH Zurich, Autonomous Systems Lab
 */

#pragma once

// ROS
#include <ros/ros.h>
#include <geometry_msgs/PoseWithCovarianceStamped.h>
#include <geometry_msgs/PoseStamped.h>
#include <geometry_msgs/TwistWithCovarianceStamped.h>
#include <geometry_msgs/TwistStamped.h>
#include <tf/transform_listener.h>

// STD
#include <string>

namespace traversability_checker {

class TraversabilityChecker
{
 public:
  TraversabilityChecker(const ros::NodeHandle& nodeHandle);
  virtual ~TraversabilityChecker();
  bool readParameters();
  void check(const ros::TimerEvent& timerEvent);
  void updateRobotPose(const geometry_msgs::PoseWithCovarianceStamped& pose);
  void updateRobotTwist(const geometry_msgs::TwistWithCovarianceStamped& twist);

 private:
  ros::NodeHandle nodeHandle_;
  tf::TransformListener tfListener_;
  ros::Publisher safetyPublisher_;
  ros::Timer timer_;
  ros::Duration timerDuration_;
  ros::ServiceClient serviceClient_;
  std::string serviceName_;
  ros::Subscriber robotPoseSubscriber_;
  std::string robotPoseTopic_;
  ros::Subscriber robotTwistSubscriber_;
  std::string robotTwistTopic_;
  double extrapolationDuration_;
  double footprintRadius_;
  geometry_msgs::PoseStamped robotPose_;
  geometry_msgs::TwistStamped robotTwist_;
};

} /* namespace traversability_checker */

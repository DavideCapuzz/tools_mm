#include "tools_mm/execute_path.hpp"
#include "behaviortree_ros2/plugins.hpp"


BT::PortsList ExecutePath::providedPorts()
{
  RCLCPP_INFO(rclcpp::get_logger("ExecutePath"),"init prots get path");
  return {
    BT::InputPort<nav_msgs::msg::Path>("path")
  };
}

bool ExecutePath::setGoal(RosActionNode::Goal& goal) 
{
  nav_msgs::msg::Path path;
  // get "order" from the Input port
  getInput("path", path);
  
  RCLCPP_INFO(rclcpp::get_logger("ExecutePath"),"init prots get path %f", path.poses[0].pose.position.x);
  goal.path = path;
  // return true, if we were able to set the goal correctly.
  return true;
}

BT::NodeStatus ExecutePath::onResultReceived(const WrappedResult& wr)
{
  /*std::stringstream ss;
  ss << "Result received: ";
  for (auto number : wr.result->path.poses) {
    //ss << number.pose.x << " ";
  }
  RCLCPP_INFO(rclcpp::get_logger("ExecutePath"), ss.str().c_str());*/
  return BT::NodeStatus::SUCCESS;
}

BT::NodeStatus ExecutePath::onFailure(BT::ActionNodeErrorCode error)
{
  RCLCPP_ERROR(rclcpp::get_logger("ExecutePath"), "Error: %d", error);
  return BT::NodeStatus::FAILURE;
}

BT::NodeStatus ExecutePath::onFeedback(const std::shared_ptr<const Feedback> feedback)
{
  //RCLCPP_INFO(rclcpp::get_logger("ExecutePath"), "Publishing: '%s'",feedback->state.data.c_str());
  return BT::NodeStatus::RUNNING;
}
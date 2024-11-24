#include "tools_mm/execute_path.hpp"
#include "behaviortree_ros2/plugins.hpp"


BT::PortsList ExecutePath::providedPorts()
{
  // initialize blackboard ports
  RCLCPP_INFO(rclcpp::get_logger("ExecutePath"),"init prots get path");
  return {
    BT::InputPort<nav_msgs::msg::Path>("path")
  };
}

bool ExecutePath::setGoal(RosActionNode::Goal& goal) 
{
  // get the target from the blackboard
  nav_msgs::msg::Path path;  
  getInput("path", path);  
  goal.path = path;
  // return true, if we were able to set the goal correctly.
  return true;
}

BT::NodeStatus ExecutePath::onResultReceived(const WrappedResult& wr)
{
  // TODO add the check on the result
  return BT::NodeStatus::SUCCESS;
}

BT::NodeStatus ExecutePath::onFailure(BT::ActionNodeErrorCode error)
{
  RCLCPP_ERROR(rclcpp::get_logger("ExecutePath"), "Error: %d", error);
  return BT::NodeStatus::FAILURE;
}

BT::NodeStatus ExecutePath::onFeedback(const std::shared_ptr<const Feedback> feedback)
{
  // TODO add the check on the feedback
  return BT::NodeStatus::RUNNING;
}
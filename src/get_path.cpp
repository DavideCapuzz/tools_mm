#include "tools_mm/get_path.hpp"
#include "behaviortree_ros2/plugins.hpp"


BT::PortsList GetPath::providedPorts()
{
  // initialize blackboard ports
  RCLCPP_INFO(rclcpp::get_logger("GetPath"),"init ports get path");
  return {
    BT::OutputPort<nav_msgs::msg::Path>("path"),
    BT::InputPort<geometry_msgs::msg::Point>("target")
  };
}

bool GetPath::setGoal(RosActionNode::Goal& goal) 
{
  // get the target from the blackboard
  geometry_msgs::msg::Point target;
  getInput("target", target);      
  goal.target.x = target.x;
  goal.target.y = target.y;
  goal.target.z = target.z;
  // return true, if we were able to set the goal correctly.
  return true;
}

BT::NodeStatus GetPath::onResultReceived(const WrappedResult& wr)
{
  // TODO add the check on the result
  if(auto any_ptr = getLockedPortContent("path"))
  {
    // check if the exist the lock to the black board target
    if(any_ptr->empty())
    {
      // The entry hasn't been initialized by any other node, yet.
      // Let's initialize it ourselves
      any_ptr.assign(wr.result->path);
    }
    else if(auto* vect_ptr = any_ptr->castPtr<nav_msgs::msg::Path>())
    {
      // NOTE: vect_ptr would be nullptr, if we try to cast it to the wrong type
      * vect_ptr = wr.result->path;
    }
    return BT::NodeStatus::SUCCESS;
  }
  else
  {
    return BT::NodeStatus::FAILURE;
  }
}

BT::NodeStatus GetPath::onFailure(BT::ActionNodeErrorCode error)
{
  RCLCPP_ERROR(rclcpp::get_logger("GetPath"), "Error: %d", error);
  return BT::NodeStatus::FAILURE;
}

BT::NodeStatus GetPath::onFeedback(const std::shared_ptr<const Feedback> feedback)
{
  // TODO add the check on the feedback
  return BT::NodeStatus::RUNNING;
}
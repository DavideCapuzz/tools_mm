#include "tools_mm/get_path.hpp"
#include "behaviortree_ros2/plugins.hpp"


BT::PortsList GetPath::providedPorts()
{
  RCLCPP_INFO(rclcpp::get_logger("GetPath"),"init prots get path");
  return {
    BT::OutputPort<geometry_msgs::msg::Point>("path"),
    BT::InputPort<geometry_msgs::msg::Point>("target")
  };
}

bool GetPath::setGoal(RosActionNode::Goal& goal) 
{
  geometry_msgs::msg::Point target;
  // get "order" from the Input port
  getInput("target", target);
  
  RCLCPP_INFO(rclcpp::get_logger("GetPath"),"init prots get path %f", target.x);
  goal.target.x=target.x;
  goal.target.y=target.y;
  goal.target.z=target.z;
  // return true, if we were able to set the goal correctly.
  return true;
}

BT::NodeStatus GetPath::onResultReceived(const WrappedResult& wr)
  {
    std::stringstream ss;
    ss << "Result received: ";
    for (auto number : wr.result->path.poses) {
      //ss << number.pose.x << " ";
    }
    RCLCPP_INFO(rclcpp::get_logger("GetPath"), ss.str().c_str());
    return BT::NodeStatus::SUCCESS;
  }

BT::NodeStatus GetPath::onFailure(BT::ActionNodeErrorCode error)
{
  RCLCPP_ERROR(rclcpp::get_logger("GetPath"), "Error: %d", error);
  return BT::NodeStatus::FAILURE;
}

BT::NodeStatus GetPath::onFeedback(const std::shared_ptr<const Feedback> feedback)
{
  RCLCPP_INFO(rclcpp::get_logger("GetPath"), "Publishing: '%s'",feedback->state.data.c_str());
  return BT::NodeStatus::RUNNING;
}
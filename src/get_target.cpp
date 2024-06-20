#include "tools_mm/get_target.hpp"
#include "behaviortree_ros2/plugins.hpp"

bool GetTarget::setRequest(Request::SharedPtr& request)
{
  RCLCPP_INFO(logger(), "setRequest");
  return true;
}

BT::NodeStatus GetTarget::onResponseReceived(const Response::SharedPtr& response)
{
  RCLCPP_INFO(rclcpp::get_logger("GetTarget"), "onResponseReceived %ld", response->result);
  if(response->result)
  {
    RCLCPP_INFO(rclcpp::get_logger("GetTarget"), "SetBool service succeeded.: %ld", response->result);
    return BT::NodeStatus::SUCCESS;
  }
  else
  {
    RCLCPP_INFO(rclcpp::get_logger("GetTarget"), "SetBool service failed: %ld", response->result);
    return BT::NodeStatus::FAILURE;
  }
}

BT::NodeStatus GetTarget::onFailure(BT::ServiceNodeErrorCode error)
{
  RCLCPP_ERROR(rclcpp::get_logger("GetTarget"), "Error: %d", error);
  return BT::NodeStatus::FAILURE;
}
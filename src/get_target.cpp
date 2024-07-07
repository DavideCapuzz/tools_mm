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
    setOutput("target", response->target );
    if(auto any_ptr = getLockedPortContent("target"))
    {
      // inside this scope (as long as any_ptr exists) the access to
      // the entry in the blackboard is mutex-protected and thread-safe.

      // check if the entry contains a valid element
      if(any_ptr->empty())
      {
        // The entry hasn't been initialized by any other node, yet.
        // Let's initialize it ourselves
        any_ptr.assign(response->target);
        RCLCPP_INFO(rclcpp::get_logger("GetTarget"), "SetBool service ok: %ld", response->result);
      }
      else if(auto* vect_ptr = any_ptr->castPtr<geometry_msgs::msg::Point>())
      {
        // NOTE: vect_ptr would be nullptr, if we try to cast it to the wrong type
        vect_ptr = &response->target ;
      }
      return BT::NodeStatus::SUCCESS;
    }
    else
    {
      return BT::NodeStatus::FAILURE;
  }
  }
  else
  {
    RCLCPP_INFO(rclcpp::get_logger("GetTarget"), "SetBool service failed: %ld", response->result);
    return BT::NodeStatus::FAILURE;
  }
  
  
}

BT::NodeStatus GetTarget::onFailure(BT::ServiceNodeErrorCode error)
{
  RCLCPP_ERROR(rclcpp::get_logger("GetTarget"), "Error: %s", BT::toStr(error));
  return BT::NodeStatus::FAILURE;
}
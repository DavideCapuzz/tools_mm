#include "tools_mm/get_target.hpp"
#include "behaviortree_ros2/plugins.hpp"

bool GetTarget::setRequest(Request::SharedPtr& request)
{
  // set and send the request for the service to get the target
  RCLCPP_INFO(logger(), "setRequest");
  return true;
}

BT::NodeStatus GetTarget::onResponseReceived(const Response::SharedPtr& response)
{
  // check if we have received the result
  if(response->result)
  { 
    // check if the it existe the lock to the black board target
    if(auto any_ptr = getLockedPortContent("target"))
    {      
      // the entry in the blackboard is mutex-protected and thread-safe.
      // check if the entry contains a valid element
      if(any_ptr->empty())
      {
        // The entry hasn't been initialized by any other node, yet.
        // Let's initialize it ourselves
        any_ptr.assign(response->target);
      }
      else if(auto* vect_ptr = any_ptr->castPtr<geometry_msgs::msg::Point>())
      {
        // NOTE: vect_ptr would be nullptr, if we try to cast it to the wrong type
        * vect_ptr = response->target ;
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
    RCLCPP_INFO(rclcpp::get_logger("GetTarget"), "SetBool service failed: %d", response->result);
    return BT::NodeStatus::FAILURE;
  }
  
  
}

BT::NodeStatus GetTarget::onFailure(BT::ServiceNodeErrorCode error)
{
  RCLCPP_ERROR(rclcpp::get_logger("GetTarget"), "Error: %s", BT::toStr(error));
  return BT::NodeStatus::FAILURE;
}
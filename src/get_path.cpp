#include "tools_mm/get_path.hpp"
#include "behaviortree_ros2/plugins.hpp"


BT::PortsList GetPath::providedPorts()
{
  RCLCPP_INFO(rclcpp::get_logger("GetPath"),"init prots get path");
  return {
    BT::OutputPort<nav_msgs::msg::Path>("path"),
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
   /* for(int i =0; i<wr.result->path_.poses.size(); i++)
	{
		RCLCPP_INFO(get_logger(), " distance %f , %f",wr.result->path_.poses[i].pose.position.x, wr.result->path_.poses[i].pose.position.y);
	}*/
    if(auto any_ptr = getLockedPortContent("path"))
    {
      // inside this scope (as long as any_ptr exists) the access to
      // the entry in the blackboard is mutex-protected and thread-safe.

      // check if the entry contains a valid element
      if(any_ptr->empty())
      {
        // The entry hasn't been initialized by any other node, yet.
        // Let's initialize it ourselves
        any_ptr.assign(wr.result->path);
        RCLCPP_INFO(rclcpp::get_logger("GetPath"), "SetBool service ok:");
      }
      else if(auto* vect_ptr = any_ptr->castPtr<nav_msgs::msg::Path>())
      {
        // NOTE: vect_ptr would be nullptr, if we try to cast it to the wrong type
        vect_ptr = &wr.result->path;
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
  RCLCPP_INFO(rclcpp::get_logger("GetPath"), "Publishing: '%s'",feedback->state.data.c_str());
  return BT::NodeStatus::RUNNING;
}
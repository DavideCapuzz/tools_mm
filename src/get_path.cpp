#include "tools_mm/get_path.hpp"
#include "behaviortree_ros2/plugins.hpp"

bool GetPath::setRequest(Request::SharedPtr& request)
{
  RCLCPP_INFO(logger(), "set request");
  getInput("A", request->a);
  getInput("B", request->b);
  getInput("C", request->c);
  RCLCPP_INFO(logger(), "setRequest" , request);
  return true;
}

BT::NodeStatus GetPath::onResponseReceived(const Response::SharedPtr& response)
{
  RCLCPP_INFO(rclcpp::get_logger("GetPath"), "onResponseReceived %ld", response->sum);
  if(response->sum !=0)
  {
    RCLCPP_INFO(rclcpp::get_logger("GetPath"), "SetBool service succeeded.: %ld", response->sum);
    return BT::NodeStatus::SUCCESS;
  }
  else
  {
    RCLCPP_INFO(rclcpp::get_logger("GetPath"), "SetBool service failed: %ld", response->sum);
    return BT::NodeStatus::FAILURE;
  }
}

BT::NodeStatus GetPath::onFailure(BT::ServiceNodeErrorCode error)
{
  RCLCPP_ERROR(rclcpp::get_logger("GetPath"), "Error: %d", error);
  return BT::NodeStatus::FAILURE;
}

bool SetBoolService::setRequest(Request::SharedPtr& request)
{
  getInput("value", request->data);
  std::cout << "setRequest " << std::endl;
  return true;
}

BT::NodeStatus SetBoolService::onResponseReceived(const Response::SharedPtr& response)
{
  std::cout << "onResponseReceived " << std::endl;
  if(response->success)
  {
    RCLCPP_INFO(logger(), "SetBool service succeeded.");
    return BT::NodeStatus::SUCCESS;
  }
  else
  {
    RCLCPP_INFO(logger(), "SetBool service failed: %s", response->message.c_str());
    return BT::NodeStatus::FAILURE;
  }
}

BT::NodeStatus SetBoolService::onFailure(BT::ServiceNodeErrorCode error)
{
  RCLCPP_ERROR(logger(), "Error: %d", error);
  return BT::NodeStatus::FAILURE;
}

//-----------------------------------------------------------

BT::NodeStatus SetRobotBoolService::tick()
{
  std::string robot;
  if(getInput("robot", robot) && !robot.empty())
  {
    setServiceName(robot + "/" + service_suffix_);
  }
  return SetBoolService::tick();
}
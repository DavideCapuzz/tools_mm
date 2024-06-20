#include <behaviortree_ros2/bt_service_node.hpp>
#include "btcpp_ros2_interfaces/action/sleep.hpp"
#include "tools_nav/srv/add_three_ints.hpp"
#include "rclcpp/rclcpp.hpp"
#include "std_srvs/srv/set_bool.hpp"

class GetPath : public BT::RosServiceNode<tools_nav::srv::AddThreeInts>
{
public:
  explicit GetPath(const std::string& name, const BT::NodeConfig& conf,
                          const BT::RosNodeParams& params)
    : RosServiceNode<tools_nav::srv::AddThreeInts>(name, conf, params)
  {
   RCLCPP_INFO(rclcpp::get_logger("GetPath"), "init");
  }

  static BT::PortsList providedPorts()
  {
    RCLCPP_INFO(rclcpp::get_logger("GetPath"), "providedPorts");
    return providedBasicPorts({
        BT::InputPort<unsigned>("A"),
        BT::InputPort<unsigned>("B"),
        BT::InputPort<unsigned>("C")});
  }

  bool setRequest(Request::SharedPtr& request) override;

  BT::NodeStatus onResponseReceived(const Response::SharedPtr& response) override;

  virtual BT::NodeStatus onFailure(BT::ServiceNodeErrorCode error) override;

private:
  std::string service_suffix_;
};



using SetBool = std_srvs::srv::SetBool;

class SetBoolService : public BT::RosServiceNode<SetBool>
{
public:
  explicit SetBoolService(const std::string& name, const BT::NodeConfig& conf,
                          const BT::RosNodeParams& params)
    : RosServiceNode<SetBool>(name, conf, params)
  {}

  static BT::PortsList providedPorts()
  {
    return providedBasicPorts({ BT::InputPort<bool>("value") });
  }

  bool setRequest(Request::SharedPtr& request) override;

  BT::NodeStatus onResponseReceived(const Response::SharedPtr& response) override;

  virtual BT::NodeStatus onFailure(BT::ServiceNodeErrorCode error) override;

private:
  std::string service_suffix_;
};

//----------------------------------------------

class SetRobotBoolService : public SetBoolService
{
public:
  explicit SetRobotBoolService(const std::string& name, const BT::NodeConfig& conf,
                               const rclcpp::Node::SharedPtr& node,
                               const std::string& port_name)
    : SetBoolService(name, conf, BT::RosNodeParams(node)), service_suffix_(port_name)
  {}

  static BT::PortsList providedPorts()
  {
    return { BT::InputPort<std::string>("robot"), BT::InputPort<bool>("value") };
  }

  BT::NodeStatus tick() override;

private:
  std::string service_suffix_;
};
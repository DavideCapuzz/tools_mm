#include <behaviortree_ros2/bt_service_node.hpp>
#include "btcpp_ros2_interfaces/action/sleep.hpp"
#include "interfaces/srv/get_target.hpp"
#include "rclcpp/rclcpp.hpp"
#include "std_srvs/srv/set_bool.hpp"
#include "geometry_msgs/msg/point.hpp"

class GetTarget : public BT::RosServiceNode<interfaces::srv::GetTarget>
{
public:
  explicit GetTarget(const std::string& name, const BT::NodeConfig& conf,
                          const BT::RosNodeParams& params)
    : RosServiceNode<interfaces::srv::GetTarget>(name, conf, params)
  {
   RCLCPP_INFO(rclcpp::get_logger("GetTarget"), "init");
  }

  static BT::PortsList providedPorts()
  {
    // initialize blackboard ports
    RCLCPP_INFO(rclcpp::get_logger("GetTarget"), "providedPorts");
    return {BT::OutputPort<geometry_msgs::msg::Point>("target")};
  }

  bool setRequest(Request::SharedPtr& request) override;

  BT::NodeStatus onResponseReceived(const Response::SharedPtr& response) override;

  virtual BT::NodeStatus onFailure(BT::ServiceNodeErrorCode error) override;

private:
  std::string service_suffix_;
};
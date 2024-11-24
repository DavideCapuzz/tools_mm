#include "btcpp_ros2_interfaces/action/sleep.hpp"
#include "rclcpp/rclcpp.hpp"
#include <behaviortree_ros2/bt_action_node.hpp>
#include "geometry_msgs/msg/point.hpp"
#include <functional>
#include <future>
#include <memory>
#include <string>
#include <sstream>

#include "interfaces/action/get_path.hpp"

class GetPath: public BT::RosActionNode<interfaces::action::GetPath>
{
public:
  GetPath(const std::string& name,
                  const BT::NodeConfig& conf,
                  const BT::RosNodeParams& params)
    : BT::RosActionNode<interfaces::action::GetPath>(name, conf, params)
  {}

  // The specific ports of this Derived class
  // should be merged with the ports of the base class,
  // using RosActionNode::providedBasicPorts()
  static BT::PortsList providedPorts();

  // This is called when the TreeNode is ticked and it should
  // send the request to the action server
  bool setGoal(RosActionNode::Goal& goal) override;
  
  // Callback executed when the reply is received.
  // Based on the reply you may decide to return SUCCESS or FAILURE.
  BT::NodeStatus onResultReceived(const WrappedResult& wr) override;

  // Callback invoked when there was an error at the level
  // of the communication between client and server.
  // This will set the status of the TreeNode to either SUCCESS or FAILURE,
  // based on the return value.
  // If not overridden, it will return FAILURE by default.
  virtual BT::NodeStatus onFailure(BT::ActionNodeErrorCode error) override;
  // we also support a callback for the feedback, as in
  // the original tutorial.
  // Usually, this callback should return RUNNING, but you
  // might decide, based on the value of the feedback, to abort
  // the action, and consider the TreeNode completed.
  // In that case, return SUCCESS or FAILURE.
  // The Cancel request will be send automatically to the server.
  BT::NodeStatus onFeedback(const std::shared_ptr<const Feedback> feedback);
};
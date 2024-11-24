#include "tools_mm/get_path.hpp"
#include "tools_mm/get_target.hpp"
#include "tools_mm/execute_path.hpp"

int main(int argc, char** argv)
{
  rclcpp::init(argc, argv);
  auto nh = std::make_shared<rclcpp::Node>("main_BT");
  auto global_bb = BT::Blackboard::create();
  auto maintree_bb = BT::Blackboard::create(global_bb);

  BT::BehaviorTreeFactory factory;

  // add all the leafs
  factory.registerNodeType<GetTarget>("GetCone", BT::RosNodeParams(nh, "/get_cone_pos"));
  factory.registerNodeType<ExecutePath>("ExecutePath", BT::RosNodeParams(nh, "/set_path"));
  factory.registerNodeType<GetTarget>("GetTarget", BT::RosNodeParams(nh, "/get_trg_fnd_pos"));
  factory.registerNodeType<GetPath>("GetPath", BT::RosNodeParams(nh, "/get_path"));

  // generate the tree
  auto tree = factory.createTreeFromFile("/home/davide-work/humble_ws/wheele/src/tools_mm/BT.xml", maintree_bb); 

  // while tick loop
  while (rclcpp::ok())
  {
      tree.tickWhileRunning();
      std::this_thread::sleep_for(std::chrono::milliseconds(100));
  }

  rclcpp::shutdown();
  return 0;
}
#include "tools_mm/get_path.hpp"
#include "tools_mm/get_target.hpp"
#include "tools_mm/execute_path.hpp"

static const char* xml_text1 = R"(
 <root BTCPP_format="4">
     <BehaviorTree>
        <Sequence>
            <GetPath name="robotA" A="1" B="2" C="3"/>
        </Sequence>
     </BehaviorTree>
 </root>
 )";

 static const char* xml_text2 = R"(
 
 )";

 static const char* xml_text = R"(
 <root BTCPP_format="4">
     <BehaviorTree>
        <Sequence>

            <SetBoolA value="true"/>
            <SetBool  service_name="robotB/set_bool" value="true"/>
            <SetRobotBool robot="robotA" value="true"/>
            <SetRobotBool robot="robotB" value="true"/>
        </Sequence>
     </BehaviorTree>
 </root>
 )";

int main(int argc, char** argv)
{
  rclcpp::init(argc, argv);
  auto nh = std::make_shared<rclcpp::Node>("main_BT");
  auto global_bb = BT::Blackboard::create();
  auto maintree_bb = BT::Blackboard::create(global_bb);

  BT::BehaviorTreeFactory factory;

  // version with default port
  //factory.registerNodeType<GetPath>("GetPath", BT::RosNodeParams(nh, "/add_three_ints"));
  factory.registerNodeType<GetTarget>("GetCone", BT::RosNodeParams(nh, "/get_cone_pos"));
  factory.registerNodeType<ExecutePath>("ExecutePath", BT::RosNodeParams(nh, "/set_path"));
  factory.registerNodeType<GetTarget>("GetTarget", BT::RosNodeParams(nh, "/get_trg_fnd_pos"));
  factory.registerNodeType<GetPath>("GetPath", BT::RosNodeParams(nh, "/get_path"));
  // version without default port

  // namespace version
  //factory.registerNodeType<SetRobotBoolService>("SetRobotBool", nh, "set_bool");

  // version with default port
  //factory.registerNodeType<SetBoolService>("SetBoolA", BT::RosNodeParams(nh, "robotA/" "set_bool"));

  // version without default port
  //factory.registerNodeType<SetBoolService>("SetBool", BT::RosNodeParams(nh));

  // namespace version
  //factory.registerNodeType<SetRobotBoolService>("SetRobotBool", nh, "set_bool");

  //auto tree = factory.createTreeFromText(xml_text2);
  auto tree = factory.createTreeFromFile("/home/davide-work/humble_ws/wheele/src/tools_mm/BT.xml", maintree_bb); 

  while (rclcpp::ok())
  {
      tree.tickWhileRunning();
      std::this_thread::sleep_for(std::chrono::milliseconds(10));
  }

  rclcpp::shutdown();
  return 0;
}
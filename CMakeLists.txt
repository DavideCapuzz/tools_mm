cmake_minimum_required(VERSION 3.8)
project(tools_mm)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(actuator_msgs REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(vision_msgs REQUIRED)
find_package(cv_bridge REQUIRED)
find_package(image_transport REQUIRED)
find_package(OpenCV REQUIRED)
find_package(behaviortree_cpp_v3 REQUIRED)
find_package(behaviortree_ros2 REQUIRED)
find_package(tools_nav REQUIRED)

add_executable(main_BT src/main_BT.cpp)
add_executable(test_path src/get_path.cpp)
ament_target_dependencies(test_path
rclcpp
std_msgs 
geometry_msgs 
actuator_msgs 
sensor_msgs
sensor_msgs
vision_msgs
rclcpp
std_msgs
behaviortree_cpp_v3
behaviortree_ros2
tools_nav
cv_bridge image_transport OpenCV)

ament_target_dependencies(main_BT
rclcpp
std_msgs 
geometry_msgs 
actuator_msgs 
sensor_msgs
sensor_msgs
vision_msgs
rclcpp
std_msgs
behaviortree_cpp_v3
behaviortree_ros2
cv_bridge image_transport OpenCV)

target_include_directories(main_BT PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>)
target_compile_features(main_BT PUBLIC c_std_99 cxx_std_17)  # Require C99 and C++17

target_include_directories(test_path PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>)
target_compile_features(test_path PUBLIC c_std_99 cxx_std_17)  # Require C99 and C++17

install(TARGETS test_path
  DESTINATION lib/${PROJECT_NAME})

install(TARGETS test_path
  DESTINATION lib/${PROJECT_NAME})

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # comment the line when a copyright and license is added to all source files
  set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # comment the line when this package is in a git repo and when
  # a copyright and license is added to all source files
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()

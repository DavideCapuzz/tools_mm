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
find_package(behaviortree_ros2 REQUIRED)
find_package(btcpp_ros2_interfaces REQUIRED)
find_package(tools_nav REQUIRED)
find_package(std_srvs REQUIRED)

set(THIS_PACKAGE_DEPS
rclcpp
std_msgs 
geometry_msgs 
actuator_msgs 
sensor_msgs
sensor_msgs
vision_msgs
rclcpp
std_msgs
behaviortree_ros2
tools_nav
std_srvs
btcpp_ros2_interfaces
cv_bridge image_transport OpenCV)

add_executable(main_BT
  src/main_BT.cpp
  src/get_path.cpp
  src/get_target.cpp
  )
ament_target_dependencies(main_BT ${THIS_PACKAGE_DEPS})

target_include_directories(main_BT PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>)
target_compile_features(main_BT PUBLIC c_std_99 cxx_std_17)  # Require C99 and C++17

install(TARGETS main_BT
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

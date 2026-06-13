cmake_minimum_required(VERSION 3.8)
project(canopen_bridge)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(std_msgs REQUIRED)

add_executable(canopen_bridge_node
  src/canopen_bridge_node.cpp
  src/canopen_interface.cpp
)

target_include_directories(canopen_bridge_node PRIVATE
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
)

ament_target_dependencies(canopen_bridge_node
  rclcpp
  geometry_msgs
  std_msgs
)

install(TARGETS canopen_bridge_node
  DESTINATION lib/${PROJECT_NAME}
)

ament_package()

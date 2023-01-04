cmake_minimum_required(VERSION 3.8)
project(cam_reader)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED) # c++ library for ROS2 
find_package(OpenCV REQUIRED) # We add all what we need for this node to work. Here! 
find_package(sensor_msgs REQUIRED)
find_package(cv_bridge REQUIRED)

include_directories(include) # to add include. We use headers :)

set(DEPENDENCIES # define dependencies. # We add all what we need for this node to work. And here!
  rclcpp
  OpenCV
  sensor_msgs
  cv_bridge
)

add_executable(cam_reader_node # executable name
  src/cam_reader_node.cpp # location of node file
) 

ament_target_dependencies(cam_reader_node # executable name
  ${DEPENDENCIES} # specify dependencies
)

install(TARGETS
  cam_reader_node # executable name
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

ament_export_include_directories(include) # to add include. We use headers :)
ament_package()

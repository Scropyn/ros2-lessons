cmake_minimum_required(VERSION 3.8)
project(lesson_w2)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(interface_pkg REQUIRED)
find_package(rclcpp_action REQUIRED)

add_executable(template_walltimer src/template_walltimer.cpp)
add_executable(template_general src/template_general.cpp)
add_executable(template_serviceserver src/template_serviceserver.cpp)
add_executable(template_serviceclient src/template_serviceclient.cpp)
add_executable(template_serviceclientA src/template_serviceclientA.cpp)
add_executable(template_serviceclientB src/template_serviceclientB.cpp)
add_executable(template_serviceclientC src/template_serviceclientC.cpp)
add_executable(template_actionserver src/template_actionserver.cpp)
add_executable(my_serviceserver src/my_serviceserver.cpp)
add_executable(my_serviceclientC src/my_serviceclientC.cpp)

add_executable(my_debug src/my_debug.cpp)

ament_target_dependencies(template_walltimer rclcpp)
ament_target_dependencies(template_general rclcpp interface_pkg)
ament_target_dependencies(template_serviceserver rclcpp interface_pkg)
ament_target_dependencies(template_serviceclient rclcpp interface_pkg)
ament_target_dependencies(template_serviceclientA rclcpp interface_pkg)
ament_target_dependencies(template_serviceclientB rclcpp interface_pkg)
ament_target_dependencies(template_serviceclientC rclcpp interface_pkg)
ament_target_dependencies(my_serviceserver rclcpp interface_pkg)
ament_target_dependencies(my_serviceclientC rclcpp interface_pkg)
ament_target_dependencies(template_actionserver rclcpp interface_pkg rclcpp_action)

ament_target_dependencies(my_debug rclcpp)

install(
  TARGETS
  template_walltimer
  template_general
  template_serviceserver
  template_serviceclient
  template_serviceclientA
  template_serviceclientB
  template_serviceclientC
  template_actionserver
  my_serviceserver
  my_serviceclientC
  my_debug
  DESTINATION lib/${PROJECT_NAME}

)

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

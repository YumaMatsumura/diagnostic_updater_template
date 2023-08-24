cmake_minimum_required(VERSION 3.8)
project(diagnostic_updater_template)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(rclcpp_components REQUIRED)
find_package(diagnostic_updater REQUIRED)

set(diagnostic_updater_template_executable diagnostic_updater_template)
set(diagnostic_updater_template_library ${diagnostic_updater_template_executable}_core)
set(dependencies
  rclcpp
  rclcpp_components
  diagnostic_updater)

include_directories(include)

add_executable(${diagnostic_updater_template_executable}
  src/diagnostic_updater_template_node.cpp
  src/diagnostic_updater_template_component.cpp)
add_library(${diagnostic_updater_template_library} SHARED
  src/diagnostic_updater_template_component.cpp)
ament_target_dependencies(${diagnostic_updater_template_executable}
  ${dependencies})
ament_target_dependencies(${diagnostic_updater_template_library}
  ${dependencies})
rclcpp_components_register_nodes(${diagnostic_updater_template_library}
  "diagnostic_updater_template::DiagnosticUpdaterTemplate")

install(TARGETS ${diagnostic_updater_template_executable}
  DESTINATION lib/${PROJECT_NAME})
install(TARGETS ${diagnostic_updater_template_library}
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin)
install(DIRECTORY include/
  DESTINATION include/)

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

ament_export_include_directories(include)
ament_export_libraries(${diagnostic_updater_template_library})
ament_export_dependencies(${dependencies})
ament_package()

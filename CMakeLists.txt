cmake_minimum_required(VERSION 3.8)
project(eeg_publisher_cpp)

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(eeg_msgs REQUIRED)

add_executable(mock_eeg_publisher src/mock_eeg_publisher.cpp)
ament_target_dependencies(mock_eeg_publisher rclcpp std_msgs eeg_msgs)

install(TARGETS mock_eeg_publisher
  DESTINATION lib/${PROJECT_NAME})

install(DIRECTORY launch
  DESTINATION share/${PROJECT_NAME}
)

ament_package()

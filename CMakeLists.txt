cmake_minimum_required(VERSION 3.8)
project(sense_eeg_cpp)

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(eeg_msgs REQUIRED)

# Build executable
add_executable(mock_eeg_publisher src/mock_eeg_publisher.cpp)
ament_target_dependencies(mock_eeg_publisher rclcpp std_msgs eeg_msgs)

# Install
install(TARGETS mock_eeg_publisher
  DESTINATION lib/${PROJECT_NAME})

# Install launch files (optional but recommended)
install(DIRECTORY launch
  DESTINATION share/${PROJECT_NAME}
)

ament_package()

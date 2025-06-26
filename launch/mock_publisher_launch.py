from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    return LaunchDescription([
        Node(
            package='eeg_publisher_cpp',
            executable='mock_eeg_publisher',
            name='mock_eeg_publisher',
            output='screen'
        ),
    ])

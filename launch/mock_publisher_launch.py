from launch import LaunchDescription
from launch_ros.actions import Node
from ament_index_python.packages import get_package_share_directory
import os


def generate_launch_description():
    config = os.path.join(
        get_package_share_directory('eeg_publisher_cpp'),
        'config',
        'mock_publisher.yaml'
    )

    return LaunchDescription([
        Node(
            package='eeg_publisher_cpp',
            executable='mock_eeg_publisher',
            name='mock_eeg_publisher',
            parameters=[config],
            output='screen'
        ),
    ])

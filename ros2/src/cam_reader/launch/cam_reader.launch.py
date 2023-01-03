from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    return LaunchDescription([
        Node(
            package='cam_reader',
            executable='cam_reader_node',
            name='cam_reader',
            output='screen'
        )
    ])
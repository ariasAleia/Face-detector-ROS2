from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    return LaunchDescription([
        Node(
            package='bounding_box',
            executable='bounding_box_node',
            name='bounding_box',
            output='screen'
        )
    ])
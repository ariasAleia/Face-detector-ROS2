from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    return LaunchDescription([
        Node(
            package='face_detector',
            executable='face_detector_node',
            name='face_detector',
            output='screen'
        )
    ])
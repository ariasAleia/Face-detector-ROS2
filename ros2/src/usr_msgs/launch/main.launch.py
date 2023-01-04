from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    return LaunchDescription([
        Node(
            package='cam_reader',
            executable='cam_reader_node',
            name='cam_reader',
            output='screen'
        ),
        Node(
            package='bounding_box',
            executable='bounding_box_node',
            name='bounding_box',
            output='screen'
        ),
        Node(
            package='face_detector',
            executable='face_detector_node',
            name='face_detector',
            output='screen'
        )
    ])
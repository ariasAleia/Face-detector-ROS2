import os

from ament_index_python.packages import get_package_share_directory

from launch import LaunchDescription
from launch.actions import IncludeLaunchDescription
from launch.launch_description_sources import PythonLaunchDescriptionSource


def generate_launch_description():
   cam_reader = IncludeLaunchDescription(
      PythonLaunchDescriptionSource([os.path.join(
         get_package_share_directory('cam_reader'), 'launch'),
         '/cam_reader.launch.py'])
      )
   bounding_box = IncludeLaunchDescription(
      PythonLaunchDescriptionSource([os.path.join(
         get_package_share_directory('bounding_box'), 'launch'),
         '/bounding_box.launch.py'])
      )
   face_detector = IncludeLaunchDescription(
      PythonLaunchDescriptionSource([os.path.join(
         get_package_share_directory('face_detector'), 'launch'),
         '/face_detector.launch.py'])
      )

   return LaunchDescription([
      cam_reader,
      bounding_box,
      face_detector
   ])
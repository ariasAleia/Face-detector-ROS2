cd ros2/
source /opt/ros/humble/setup.bash
colcon build --symlink-install
source install/setup.bash

ros2 launch face_detector main.launch.py
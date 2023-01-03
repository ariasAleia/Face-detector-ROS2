#include "rclcpp/rclcpp.hpp"
#include "opencv2/opencv.hpp"
#include "sensor_msgs/msg/image.hpp"
#include "cv_bridge/cv_bridge.h"
#include "usr_msgs/msg/boxes.hpp"
#include <unistd.h>
#include <stdio.h>


class BoundingBox : public rclcpp::Node
{
public:
    BoundingBox();

private:

    // Subscribers
    rclcpp::Subscription<sensor_msgs::msg::Image>::SharedPtr image_sub_;
    
    // Publishers
    rclcpp::Publisher<usr_msgs::msg::Boxes>::SharedPtr boxes_pub_;
    // Timers

    // Callbacks
    void process_image_callback_(sensor_msgs::msg::Image msg);

};
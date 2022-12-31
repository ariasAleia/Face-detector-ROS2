#include "rclcpp/rclcpp.hpp"
#include "opencv2/opencv.hpp"
#include "sensor_msgs/msg/image.hpp"
#include "cv_bridge/cv_bridge.h"


class BoundingBox : public rclcpp::Node
{
public:
    BoundingBox();

private:

    // Subscribers
    rclcpp::Subscription<sensor_msgs::msg::Image>::SharedPtr image_sub_;
    
    // Publishers
   
    // Timers

    // Callbacks
    void process_image_callback_(sensor_msgs::msg::Image msg);

};
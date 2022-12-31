#include "rclcpp/rclcpp.hpp"
#include "opencv2/opencv.hpp"
#include "sensor_msgs/msg/image.hpp"
#include "cv_bridge/cv_bridge.h"


class CamReader : public rclcpp::Node
{
public:
    CamReader();

private:

    // Subscribers
    
    // Publishers
    rclcpp::Publisher<sensor_msgs::msg::Image>::SharedPtr image_publisher_;
   
    // Timers
    rclcpp::TimerBase::SharedPtr get_image_timer_;

    // Callbacks
    void get_image_callback_();

};
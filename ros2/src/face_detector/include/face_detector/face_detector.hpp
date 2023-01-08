#include "rclcpp/rclcpp.hpp"
#include "opencv2/opencv.hpp"
#include "sensor_msgs/msg/image.hpp"
#include "cv_bridge/cv_bridge.h"
#include "usr_msgs/msg/boxes.hpp"


class FaceDetector : public rclcpp::Node
{
public:
    FaceDetector();

private:

    // Subscribers
    rclcpp::Subscription<sensor_msgs::msg::Image>::SharedPtr image_sub_;
    rclcpp::Subscription<usr_msgs::msg::Boxes>::SharedPtr boxes_sub_;

    // Publishers
    rclcpp::Publisher<sensor_msgs::msg::Image>::SharedPtr final_image_pub_;

    // Callbacks
    void save_image_callback_(sensor_msgs::msg::Image msg);
    void draw_boxes_callback_(usr_msgs::msg::Boxes msg);

    // Class variables
    cv::Mat original_image;
};
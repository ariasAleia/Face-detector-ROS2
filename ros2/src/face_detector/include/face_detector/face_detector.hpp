#include "rclcpp/rclcpp.hpp"
#include "opencv2/opencv.hpp"
#include "sensor_msgs/msg/image.hpp"
#include "cv_bridge/cv_bridge.h"
#include "usr_msgs/msg/face_detection.hpp"


class FaceDetector : public rclcpp::Node
{
public:
    FaceDetector();

private:

    // Subscribers
    rclcpp::Subscription<usr_msgs::msg::FaceDetection>::SharedPtr face_image_sub_;

    // Publishers
    rclcpp::Publisher<sensor_msgs::msg::Image>::SharedPtr final_image_pub_;

    // Callbacks
    void draw_boxes_callback_(usr_msgs::msg::FaceDetection msg);
};
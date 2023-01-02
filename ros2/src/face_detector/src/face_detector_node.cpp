#include <face_detector/face_detector.hpp>


FaceDetector::FaceDetector()
: Node("face_detector")
{      
    image_sub_ = this->create_subscription<sensor_msgs::msg::Image>("/image", 
        10, std::bind(&FaceDetector::save_image_callback_, this, std::placeholders::_1));
    
    boxes_sub_ = this->create_subscription<usr_msgs::msg::Boxes>("/bounding_boxes", 
        10, std::bind(&FaceDetector::draw_boxes_callback_, this, std::placeholders::_1));
}

void FaceDetector::save_image_callback_(sensor_msgs::msg::Image msg)
{
    RCLCPP_INFO(this->get_logger(), "Received original image in face detector");
    cv_bridge::CvImagePtr cv_ptr;
    cv_ptr = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::RGB8);
    original_image = cv_ptr->image;
    RCLCPP_INFO(this->get_logger(), "Saved original image in face detector");
}

void FaceDetector::draw_boxes_callback_(usr_msgs::msg::Boxes msg)
{
    RCLCPP_INFO(this->get_logger(), "Drawing boxes in face detector");
}

int main(int argc, char * argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<FaceDetector>());
    rclcpp::shutdown();
    return 0;
}
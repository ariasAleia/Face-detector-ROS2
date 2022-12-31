#include <bounding_box/bounding_box.hpp>


BoundingBox::BoundingBox()
: Node("bounding_box")
{      
    image_sub_ = this->create_subscription<sensor_msgs::msg::Image>("/image", 
    10, std::bind(&BoundingBox::process_image_callback_, this, std::placeholders::_1));
}

void BoundingBox::process_image_callback_(sensor_msgs::msg::Image msg)
{
    RCLCPP_INFO(this->get_logger(), "Received image");
    cv_bridge::CvImagePtr cv_ptr;
    cv_ptr = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::RGB8);
    cv::imwrite("imageSubs.png", cv_ptr->image);   
}

int main(int argc, char * argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<BoundingBox>());
    rclcpp::shutdown();
    return 0;
}
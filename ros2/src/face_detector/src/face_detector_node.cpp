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
    cv_bridge::CvImagePtr cv_ptr;
    cv_ptr = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::RGB8);
    original_image = cv_ptr->image;
}

void FaceDetector::draw_boxes_callback_(usr_msgs::msg::Boxes msg)
{
    RCLCPP_INFO(this->get_logger(), "Drawing boxes in face detector");
    for ( size_t i = 0; i < msg.boxes.size(); i++ )
    {
        cv::Point p1(msg.boxes[i].x, msg.boxes[i].y);
        cv::Point p2(msg.boxes[i].x + msg.boxes[i].width, 
            msg.boxes[i].y + msg.boxes[i].height);
  
        cv::rectangle(original_image,p1,p2,cv::Scalar(0,255,0),3);
    }
    cv::imwrite("final_image.png", original_image);
}

int main(int argc, char * argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<FaceDetector>());
    rclcpp::shutdown();
    return 0;
}
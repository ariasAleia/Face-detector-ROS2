#include <face_detector/face_detector.hpp>


FaceDetector::FaceDetector()
: Node("face_detector")
{      
    auto default_qos = rclcpp::QoS(rclcpp::SystemDefaultsQoS());

    // Force to be reliable, some DDS have set defaultQoS to best effort
    default_qos.reliable();

    image_sub_ = this->create_subscription<sensor_msgs::msg::Image>("/image", 
        default_qos, std::bind(&FaceDetector::save_image_callback_, this, std::placeholders::_1));
    
    boxes_sub_ = this->create_subscription<usr_msgs::msg::Boxes>("/bounding_boxes", 
        default_qos, std::bind(&FaceDetector::draw_boxes_callback_, this, std::placeholders::_1));

    final_image_pub_ = this->create_publisher<sensor_msgs::msg::Image>("/final_image", default_qos);  
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
        cv::Point p1(msg.boxes[i].center.position.x - msg.boxes[i].size_x / 2,
                    msg.boxes[i].center.position.y - msg.boxes[i].size_y / 2);
        cv::Point p2(msg.boxes[i].center.position.x + msg.boxes[i].size_x / 2,
                    msg.boxes[i].center.position.y + msg.boxes[i].size_y / 2);

        cv::rectangle(original_image,p1,p2,cv::Scalar(0,255,0),3);
    }
    cv::imwrite("final_image.png", original_image);
    // From cv image to sensor msg Image
    cv_bridge::CvImage img_bridge;
    sensor_msgs::msg::Image final_image; 
    
    std_msgs::msg::Header header; // empty header

    img_bridge = cv_bridge::CvImage(header, sensor_msgs::image_encodings::RGB8, original_image);
    img_bridge.toImageMsg(final_image); // from cv_bridge to sensor_msgs::Image

    final_image_pub_->publish(final_image);
}

int main(int argc, char * argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<FaceDetector>());
    rclcpp::shutdown();
    return 0;
}
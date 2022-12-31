#include <cam_reader/cam_reader.hpp>


CamReader::CamReader ()
: Node("cam_reader")
{  
    get_image_timer_ = this->create_wall_timer(
        std::chrono::milliseconds(2000),
        std::bind(&CamReader::get_image_callback_, this));
    
    image_publisher_ = this->create_publisher<sensor_msgs::msg::Image>("/image", 10);
}

void CamReader::get_image_callback_()
{
    RCLCPP_INFO(this->get_logger(), "Cam Node present. Smile!");
    cv::VideoCapture cap(0); // open the default camera
    if(!cap.isOpened())  
        std::cout << "Error opening camera" << std::endl;
    cv::Mat frame;
    cap >> frame; // get a new frame from camera
    cv::imwrite("image.png", frame);   

    cv_bridge::CvImage img_bridge;
    sensor_msgs::msg::Image cam_msg; 
    
    std_msgs::msg::Header header; // empty header

    img_bridge = cv_bridge::CvImage(header, sensor_msgs::image_encodings::RGB8, frame);
    img_bridge.toImageMsg(cam_msg); // from cv_bridge to sensor_msgs::Image

    image_publisher_->publish(cam_msg);
}

int main(int argc, char * argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<CamReader>());
    rclcpp::shutdown();
    return 0;
}
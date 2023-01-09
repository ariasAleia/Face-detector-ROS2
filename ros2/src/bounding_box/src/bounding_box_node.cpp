#include <bounding_box/bounding_box.hpp>


BoundingBox::BoundingBox()
: Node("bounding_box")
{      
    image_sub_ = this->create_subscription<sensor_msgs::msg::Image>("/image", 
        10, std::bind(&BoundingBox::process_image_callback_, this, std::placeholders::_1));
    
    boxes_pub_ = this->create_publisher<usr_msgs::msg::Boxes>("/bounding_boxes", 10);  
}

void BoundingBox::process_image_callback_(sensor_msgs::msg::Image msg)
{
    RCLCPP_INFO(this->get_logger(), "Received image in bounding box node...");
    cv_bridge::CvImagePtr cv_ptr;
    cv_ptr = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::RGB8);
    cv::Mat frame_gray;
    cvtColor( cv_ptr->image, frame_gray, cv::COLOR_BGR2GRAY );
    cv::equalizeHist(frame_gray, frame_gray);

    cv::CascadeClassifier face_cascade; 
    std::string current_dir = get_current_dir_name(); 

    face_cascade.load(current_dir + "/src/bounding_box/cascade.xml");
    std::vector<cv::Rect> faces;
    face_cascade.detectMultiScale(frame_gray, faces);
    RCLCPP_INFO_STREAM(this->get_logger(), "Detected faces: " << faces.size());

    usr_msgs::msg::Boxes boxes_msg;
    vision_msgs::msg::BoundingBox2D bounding_box;

    for ( size_t i = 0; i < faces.size(); i++ )
    {
        bounding_box.center.position.x = faces[i].x + faces[i].width / 2;
        bounding_box.center.position.y = faces[i].y + faces[i].height / 2;
        bounding_box.size_x = faces[i].width;
        bounding_box.size_y = faces[i].height;
        boxes_msg.boxes.push_back(bounding_box);
    }
    boxes_pub_->publish(boxes_msg);
}

int main(int argc, char * argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<BoundingBox>());
    rclcpp::shutdown();
    return 0;
}
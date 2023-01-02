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
    RCLCPP_INFO(this->get_logger(), "Received image. Getting bounding box...");
    cv_bridge::CvImagePtr cv_ptr;
    cv_ptr = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::RGB8);
    cv::Mat frame_gray;
    cvtColor( cv_ptr->image, frame_gray, cv::COLOR_BGR2GRAY );
    cv::equalizeHist( frame_gray, frame_gray );
    cv::imwrite("imageSubs.png", frame_gray);

    cv::CascadeClassifier face_cascade; 
    face_cascade.load("/home/aleja/Documents/Face-detector-ROS2/ros2/src/bounding_box/cascade.xml");
    std::vector<cv::Rect> faces;
    face_cascade.detectMultiScale(frame_gray, faces);
    std::cout << "Size: " << faces.size() << std::endl;

    usr_msgs::msg::Boxes image_boxes;
    usr_msgs::msg::Box bounding_box;
    for ( size_t i = 0; i < faces.size(); i++ )
    {
        bounding_box.x = faces[i].x;
        bounding_box.y = faces[i].y;
        bounding_box.width = faces[i].width;
        bounding_box.height = faces[i].height;
        image_boxes.boxes.push_back(bounding_box);
        std::cout<<faces[i].x << std::endl;
        std::cout<<faces[i].y << std::endl;
        std::cout<<faces[i].width << std::endl;
        std::cout<<faces[i].height << std::endl;
    }
    boxes_pub_->publish(image_boxes);
    cv::Point p1(faces[0].x, faces[0].y);
  
    // Bottom Right Coordinates
    cv::Point p2(faces[0].x + faces[0].width, faces[0].y + faces[0].height);
        // Drawing the Rectangle
    // rectangle(image, p1, p2,
    //           Scalar(255, 0, 0),
    //           thickness, LINE_8);
    cv::rectangle(frame_gray,p1,p2,cv::Scalar(0,255,0),3);
    cv::imwrite("imageSubsRect.png", frame_gray);
}

int main(int argc, char * argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<BoundingBox>());
    rclcpp::shutdown();
    return 0;
}
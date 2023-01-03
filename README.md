# Face detection with ROS2

Hi there! Welcome to my very first ROS2 Project (in C++): Face Detection :)


**Status:** Mission completed (Waiting for feedback)

## What is this project about and how does it work?

This project allows you to take images from your webcam and detect faces.

All this magic is done using three different nodes that communicate with each other using topics by means of publishers and subscribers. 

![rqt_graph](https://user-images.githubusercontent.com/102924128/210364605-f31ab9c3-1c5a-4f0f-8985-4f7270b6c480.png)

### Nodes:
* **cam_reader_node:** Takes images from the webcam every 2 secs and publishes them in the topic */image*
* **bounding_box_node:** Subscribes to the topic */image*, receives the image as message and processes the image to detect faces using the super-hiper-mega Viola Jones algorithm (OpenCV helps us with that. Long life to OpenCV!). Bounding boxes where the faces are detected are then published in the topic */bounding_boxes*
* **face_detector_node:** Subscribes to the topic */image* and saves it in a class variable called *original_image*. Subscribes to the topic */bounding_boxes* and after receiving the box, it draws green rectangles in the *original_image* and saves the result in *final_image.png*

Check this video to see how it works!


## How can I use this project?

I really like when READMEs are totally clear and explain all, so, I will try to do it that way. However, in case sth does not work or you don't understand sth just contact me, I will be really happy to help!

### Steps to begin to play with this project:

* **Step 1:** Clone this repo
* **Step 2:** Make sure you are in the *FACE-DETECTOR-ROS2* folder
* **Step 3:** Run the following command in the terminal:
  ```bash
  bash start.sh
  ```
* **Step 4:** Open the just created *final_image.png* image in the *ros2* folder
* **Step 5:** Enjoy the magic! If everything works properly you should be seeing now how your webcam is taking photos every 2 secs and draws a green rectangle where a face is detected.


## Acknowledgments:

Thanks to [Nico](https://github.com/NicolasRochaPacheco) for this challenge. I really enjoyed it! 

Mission completed.

Waiting for feedback.

Ready for the next challenge.

Over and out!


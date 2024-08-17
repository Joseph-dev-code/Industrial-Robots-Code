//Integration with Vision System (OpenCV, ROS) by Jo
//By using intel realsense d435i camera or d435 camera
//modify the code to use intel realsense d435i aftter installing realsense SDK and ROS packages.

#include <ros/ros.h>
#include <opencv2/opencv.hpp>
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>

void imageCallback(const sensor_msgs::ImageConstPtr& msg) {
    try {
        cv::Mat frame = cv_bridge::toCvShare(msg, "bgr8")->image;
        cv::Mat gray, edges;

        // Convert to grayscale
        cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY);

        // Edge detection
        cv::Canny(gray, edges, 50, 150);

        // Display the result
        cv::imshow("Edges", edges);
        cv::waitKey(1);
    } catch (cv_bridge::Exception& e) {
        ROS_ERROR("Could not convert from '%s' to 'bgr8'.", msg->encoding.c_str());
    }
}

int main(int argc, char** argv) {
    ros::init(argc, argv, "vision_integration");
    ros::NodeHandle nh;
    image_transport::ImageTransport it(nh);
    image_transport::Subscriber sub = it.subscribe("/camera/image", 1, imageCallback);

    ros::spin();
    return 0;
}

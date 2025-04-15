#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/image.hpp"
#include "std_srvs/srv/set_bool.hpp"
#include "cv_bridge/cv_bridge.h"
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

class ImageConversionNode : public rclcpp::Node
{
public:
    ImageConversionNode() : Node("image_conversion_node"), convert_to_grayscale_(false)
    {
        using std::placeholders::_1;
        using std::placeholders::_2;

        image_sub_ = this->create_subscription<sensor_msgs::msg::Image>(
            "/image_raw", 10,
            std::bind(&ImageConversionNode::image_callback, this, _1));

        image_pub_ = this->create_publisher<sensor_msgs::msg::Image>(
            "/image_converted", 10);

        service_ = this->create_service<std_srvs::srv::SetBool>(
            "/set_conversion_mode",
            std::bind(&ImageConversionNode::mode_callback, this, _1, _2));

        RCLCPP_INFO(this->get_logger(), "ImageConversionNode has started.");
    }

private:
    void image_callback(const sensor_msgs::msg::Image::SharedPtr msg)
    {
        cv_bridge::CvImagePtr cv_ptr;
        try {
            cv_ptr = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::BGR8);
        } catch (cv_bridge::Exception &e) {
            RCLCPP_ERROR(this->get_logger(), "cv_bridge error: %s", e.what());
            return;
        }

        if (convert_to_grayscale_) {
            cv::Mat gray_img;
            cv::cvtColor(cv_ptr->image, gray_img, cv::COLOR_BGR2GRAY);
            cv_ptr->image = gray_img;
            cv_ptr->encoding = sensor_msgs::image_encodings::MONO8;
        }

        image_pub_->publish(*cv_ptr->toImageMsg());
    }

    void mode_callback(const std_srvs::srv::SetBool::Request::SharedPtr request,
                       std_srvs::srv::SetBool::Response::SharedPtr response)
    {
        convert_to_grayscale_ = request->data;
        response->success = true;
        response->message = convert_to_grayscale_ ? "Switched to grayscale mode." : "Switched to color mode.";
        RCLCPP_INFO(this->get_logger(), "%s", response->message.c_str());
    }

    bool convert_to_grayscale_;
    rclcpp::Subscription<sensor_msgs::msg::Image>::SharedPtr image_sub_;
    rclcpp::Publisher<sensor_msgs::msg::Image>::SharedPtr image_pub_;
    rclcpp::Service<std_srvs::srv::SetBool>::SharedPtr service_;
};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<ImageConversionNode>());
    rclcpp::shutdown();
    return 0;
}

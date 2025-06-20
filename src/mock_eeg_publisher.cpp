#include <chrono>
#include <memory>
#include <random>
#include <vector>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/header.hpp"
#include "eeg_msgs/msg/eeg_block.hpp"

using namespace std::chrono_literals;

class MockEEGPublisher : public rclcpp::Node {
public:
    MockEEGPublisher()
    : Node("mock_eeg_publisher"),
      num_channels_(8),
      num_samples_(32),
      sampling_rate_(256.0),
      rng_(std::random_device{}())
    {
        publisher_ = this->create_publisher<eeg_msgs::msg::EEGBlock>("/eeg/raw", 10);

        timer_ = this->create_wall_timer(
            std::chrono::duration<double>(1.0 / (sampling_rate_ / num_samples_)),
            std::bind(&MockEEGPublisher::publish_data, this)
        );

        RCLCPP_INFO(this->get_logger(), "Mock EEG Publisher started");
    }

private:
    void publish_data() {
        auto msg = eeg_msgs::msg::EEGBlock();
        msg.header.stamp = this->now();
        msg.num_channels = num_channels_;
        msg.num_samples = num_samples_;
        msg.sampling_rate = sampling_rate_;

        std::normal_distribution<float> dist(0.0, 1.0);
        msg.data.reserve(num_channels_ * num_samples_);
        for (int i = 0; i < num_channels_ * num_samples_; ++i) {
            msg.data.push_back(dist(rng_));
        }

        publisher_->publish(msg);
        RCLCPP_INFO(this->get_logger(), "Published EEGBlock with %ld samples", msg.data.size());
    }

    rclcpp::Publisher<eeg_msgs::msg::EEGBlock>::SharedPtr publisher_;
    rclcpp::TimerBase::SharedPtr timer_;
    std::mt19937 rng_;
    int num_channels_;
    int num_samples_;
    float sampling_rate_;
};

int main(int argc, char * argv[]) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<MockEEGPublisher>());
    rclcpp::shutdown();
    return 0;
}

#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/string.hpp>
#include <chrono>
#include <thread>

class CounterSubscriber : public rclcpp::Node {
public:
  CounterSubscriber() : Node("counter_subscriber_cpp") {
    std::this_thread::sleep_for(std::chrono::milliseconds(3000));

    // Use default QoS (reliable, volatile, queue size 10)
    subscription_ = create_subscription<std_msgs::msg::String>(
        "/counter", 10, 
        [this](const std_msgs::msg::String::SharedPtr msg) {
          RCLCPP_INFO(this->get_logger(), "Recibido: %s", msg->data.c_str());
        });

    auto topic_info = get_publishers_info_by_topic("/counter");
    RCLCPP_INFO(this->get_logger(), "Subscriber iniciado, escuchando /counter. Found %zu publishers.", topic_info.size());
  }

private:
  rclcpp::Subscription<std_msgs::msg::String>::SharedPtr subscription_;
};

int main(int argc, char *argv[]) {
  rclcpp::init(argc, argv);
  auto node = std::make_shared<CounterSubscriber>();
  rclcpp::spin(node);
  rclcpp::shutdown();
  return 0;
}
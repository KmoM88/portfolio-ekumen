#include <chrono>
#include <memory>
#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/string.hpp>
#include <sstream>

using namespace std::chrono_literals;

class CounterPublisher : public rclcpp::Node {
public:
  CounterPublisher() : Node("counter_publisher_cpp"), count_(0) {
    publisher_ = create_publisher<std_msgs::msg::String>("/counter", 10);
    timer_ = create_wall_timer(
        1s, std::bind(&CounterPublisher::publish_count, this));
    RCLCPP_INFO(this->get_logger(), "Publisher iniciado, publicando en /counter");
  }

private:
  void publish_count() {
    auto message = std_msgs::msg::String();
    std::stringstream ss;
    ss << "c++: " << count_++;
    message.data = ss.str();

    RCLCPP_INFO(this->get_logger(), "Publicando: %s", message.data.c_str());
    publisher_->publish(message);
  }

  rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_;
  rclcpp::TimerBase::SharedPtr timer_;
  int count_;
};

int main(int argc, char *argv[]) {
  rclcpp::init(argc, argv);
  auto node = std::make_shared<CounterPublisher>();
  rclcpp::spin(node);
  rclcpp::shutdown();
  return 0;
}

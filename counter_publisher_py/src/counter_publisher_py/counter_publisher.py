#!/usr/bin/env python3

import rclpy
from rclpy.node import Node
from std_msgs.msg import String

class CounterPublisher(Node):
    def __init__(self):
        super().__init__('counter_publisher_py')
        self.publisher_ = self.create_publisher(String, '/counter', 10)
        self.timer = self.create_timer(1.0, self.publish_count)
        self.count_ = 0
        self.get_logger().info('Publisher Python iniciado, publicando en /counter')

    def publish_count(self):
        msg = String()
        msg.data = f'py: {self.count_}'
        self.publisher_.publish(msg)
        self.get_logger().info(f'Publicando: {msg.data}')
        self.count_ += 1

def main(args=None):
    rclpy.init(args=args)
    node = CounterPublisher()
    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        pass
    finally:
        node.destroy_node()
        rclpy.shutdown()

if __name__ == '__main__':
    main()

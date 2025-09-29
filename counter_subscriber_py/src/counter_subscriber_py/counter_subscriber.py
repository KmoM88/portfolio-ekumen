#!/usr/bin/env python3
import rclpy
from rclpy.node import Node
from std_msgs.msg import String
import time

class CounterSubscriber(Node):
    def __init__(self):
        super().__init__('counter_subscriber_py')

        time.sleep(3)
        self.sub = self.create_subscription(
            String,
            '/counter',
            self.callback,
            10
        )
        publishers = self.get_publishers_info_by_topic('/counter')
        self.get_logger().info(f"Subscriber Python iniciado en /counter. Found {len(publishers)} publishers.")

    def callback(self, msg):
        self.get_logger().info(f"Recibido: {msg.data}")

def main(args=None):
    rclpy.init(args=args)
    node = CounterSubscriber()
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()

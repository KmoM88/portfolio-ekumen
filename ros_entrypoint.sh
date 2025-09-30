#!/bin/bash
set -e

source /opt/ros/jazzy/setup.bash
source /ws/install/setup.bash

NODE_NAME_CLEAN=$(echo "$NODE_NAME" | tr '-' '_')

exec ros2 run counter_publisher_cpp counter_publisher \
  --ros-args -r __ns:="/$NAMESPACE" -r __node:="$NODE_NAME_CLEAN"

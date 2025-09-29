FROM ubuntu:24.04

SHELL ["/bin/bash", "-c"]

# Instalar herramientas básicas, colcon, rosdep y dependencias de ROS 2 en una sola capa
RUN apt-get update && \
    apt-get install -y --no-install-recommends \
        curl \
        gnupg \
        lsb-release \
        build-essential \
        python3-colcon-common-extensions \
        python3-rosdep \
        ros-jazzy-ros-core \
        ros-jazzy-rclcpp \
        ros-jazzy-std-msgs \
        ros-jazzy-rmw-cyclonedds-cpp \
    && rm -rf /var/lib/apt/lists/*

# Agregar repositorio ROS 2 y llave (si no venía ya con los paquetes anteriores)
RUN curl -sSL https://raw.githubusercontent.com/ros/rosdistro/master/ros.key \
        -o /usr/share/keyrings/ros-archive-keyring.gpg && \
    echo "deb [arch=$(dpkg --print-architecture) signed-by=/usr/share/keyrings/ros-archive-keyring.gpg] \
        http://packages.ros.org/ros2/ubuntu $(lsb_release -cs) main" \
        | tee /etc/apt/sources.list.d/ros2.list > /dev/null

# Inicializar rosdep
RUN rosdep init && rosdep update

# Configurar workspace
WORKDIR /ws
COPY counter_publisher_cpp /ws/src/counter_publisher_cpp

# Construir el workspace con colcon
RUN source /opt/ros/jazzy/setup.bash && \
    rosdep install --from-paths src --ignore-src -r -y && \
    colcon build --symlink-install

# Configurar entorno y entrypoint
ENV ROS_SETUP="/opt/ros/jazzy/setup.bash"
ENV WS_SETUP="/ws/install/setup.bash"

ENTRYPOINT source $ROS_SETUP && source $WS_SETUP && \
    ros2 run counter_publisher_cpp counter_publisher \
    $( [ -n "$NAMESPACE" ] && echo "--ros-args -r __ns:=$NAMESPACE" ) \
    $( [ -n "$NODE_NAME" ] && echo "-r __node:=$NODE_NAME" )

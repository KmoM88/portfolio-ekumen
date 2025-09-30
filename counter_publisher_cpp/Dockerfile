FROM ubuntu:24.04

RUN apt-get update && \
    apt-get install -y \
        curl \
        gnupg \
        lsb-release \
        build-essential \
        && rm -rf /var/lib/apt/lists/*

# Agregar el repositorio de ROS 2
RUN curl -sSL https://raw.githubusercontent.com/ros/rosdistro/master/ros.key -o /usr/share/keyrings/ros-archive-keyring.gpg && \
    echo "deb [arch=$(dpkg --print-architecture) signed-by=/usr/share/keyrings/ros-archive-keyring.gpg] http://packages.ros.org/ros2/ubuntu $(lsb_release -cs) main" | tee /etc/apt/sources.list.d/ros2.list > /dev/null

# Instalar dependencias de ROS 2 y herramientas de compilación
RUN apt-get update && \
    apt-get install -y \
        python3-colcon-common-extensions \
        python3-rosdep \
        ros-jazzy-ros-core \
        ros-jazzy-rclcpp \
        ros-jazzy-std-msgs \
        ros-jazzy-rmw-cyclonedds-cpp \
        && rm -rf /var/lib/apt/lists/*

# Inicializar rosdep
RUN rosdep init && rosdep update

# Configurar el workspace
WORKDIR /ws
COPY counter_publisher_cpp /ws/src/counter_publisher_cpp

# Construir el workspace con colcon
RUN /bin/bash -c "source /opt/ros/jazzy/setup.bash && \
    cd /ws && \
    rosdep install --from-paths src --ignore-src -r -y && \
    colcon build --symlink-install"

# Configurar el entorno para ejecución
COPY ros_entrypoint.sh /ros_entrypoint.sh
RUN chmod +x /ros_entrypoint.sh
ENTRYPOINT ["/ros_entrypoint.sh"]

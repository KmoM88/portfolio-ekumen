# ROS2 DevOps Demo

## Project Overview

This project demonstrates a simple ROS2 workflow using C++ and Python nodes, integrated with Docker, Bazel, Jenkins, Docker Compose, and Kubernetes. It is designed to showcase DevOps practices for robotics software.

### Project Structure

```
ros2_devops_demo/
 ├── build/
 │    ├── Dockerfile.jenkins
 │    └── docker-compose.yml
 ├── deploy/
 │    └── docker-compose.yml
 ├── counter_publisher_cpp/
 │    ├── CMakeList.txt
 │    ├── Dockerfile
 │    ├── package.xml
 │    └── src/
 │         └── counter_publisher.cpp
 ├── counter_publisher_py/
 │    ├── Dockerfile
 │    ├── package.xml
 │    ├── setup.cfg
 │    ├── setup.py
 │    └── src/counter_publisher_py/
 │              └── counter_publisher.py
 ├── counter_subscriber_cpp/
 │    ├── CMakeList.txt
 │    ├── Dockerfile
 │    ├── package.xml
 │    └── src/
 │         └── counter_subscriber.cpp
 ├── counter_subscriber_py/
 │    ├── Dockerfile
 │    ├── package.xml
 │    ├── setup.cfg
 │    ├── setup.py
 │    └── src/counter_subscriber_py/
 │              └── counter_subscriber.py
 ├── jenkins/
 │    ├── jenkinsfile.build_pub_cpp
 │    ├── jenkinsfile.build_pub_py
 │    ├── jenkinsfile.build_sub_cpp
 │    └── jenkinsfile.build_sub_py
 ├── k8s/
 │    ├── 1_replica/
 │    │       ├── publisher-cpp-deploy.yaml
 │    │       ├── publisher-py-deploy.yaml
 │    │       ├── subscriber-cpp-deploy.yaml
 │    │       └── subscriber-py-deploy.yaml
 │    └── 5_replica/
 │            ├── publisher-cpp-deploy.yaml
 │            ├── publisher-py-deploy.yaml
 │            ├── subscriber-cpp-deploy.yaml
 │            └── subscriber-py-deploy.yaml
 ├── WORKSPACE
 └── README.md
```

---

## Jenkins

### Local Testing (Jenkins + Local Registry)
- A `docker-compose.yml` is included to spin up:
  - A local Jenkins instance
  - A private Docker Registry
- Allows testing pipelines end-to-end before using DigitalOcean.
- Access:
  - Jenkins: http://localhost:8081
  - Registry: http://localhost:5000
- Commands:

```sh
# Create credentials for the registry (only the first time) (sudo apt-get install apache2-utils if you don't have htpasswd):
mkdir -p auth
htpasswd -Bbn testuser testpassword > auth/htpasswd
# Start the services
docker compose up -d
```

## Publisher and Subscriber

* **Publisher (C++)**: publishes an incrementing counter on `/counter` topic.
```bash
docker build -t counter_publisher_cpp_image -f counter_publisher_cpp/Dockerfile . 

docker run --rm -it --name ros2_publisher --network host -e ROS_DOMAIN_ID=0 counter_publisher_cpp_image
```
* **Publisher (C++)**: publishes an incrementing counter on `/counter` topic.
```bash
docker build -t counter_publisher_py_image -f counter_publisher_py/Dockerfile .

docker run --rm -it --name ros2_publisher_py --network host -e ROS_DOMAIN_ID=0 counter_publisher_py_image
```

* **Subscriber (C++)**: subscribes to `/counter` and prints the received values.
```bash
docker build -t counter_subscriber_cpp_image -f counter_subscriber_cpp/Dockerfile .

docker run --rm -it --name ros2_subscriber_cpp --network host -e ROS_DOMAIN_ID=0 counter_subscriber_cpp_image
```

* **Subscriber (Python)**: subscribes to `/counter` and prints the received values.
```bash
docker build -t counter_subscriber_py_image -f counter_subscriber_py/Dockerfile .

docker run --rm -it --name ros2_subscriber_py --network host -e ROS_DOMAIN_ID=0 counter_subscriber_py_image
```

* **Dockr Compose**: runs both publishers
In deploy path run:
```bash
docker compose build
docker compose up
```

## Pipelines

In a local instance of Jenkins and registry, you can test the pipelines:
- `jenkinsfile.build_pub_cpp`: builds and pushes the C++ publisher image to the local registry.
- `jenkinsfile.build_pub_py`: builds and pushes the Python publisher image to the local registry.
- `jenkinsfile.build_sub_cpp`: builds and pushes the C++ publisher and subscriber images to the local registry.
- `jenkinsfile.build_sub_py`: builds and pushes the Python publisher and subscriber images to the local registry.

---


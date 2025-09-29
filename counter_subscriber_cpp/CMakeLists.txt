cmake_minimum_required(VERSION 3.8)
project(counter_subscriber_cpp)

# Encontrar dependencias
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)

# Compilar el ejecutable
add_executable(counter_subscriber src/counter_subscriber.cpp)
ament_target_dependencies(counter_subscriber rclcpp std_msgs)

# Instalar el ejecutable
install(TARGETS
  counter_subscriber
  DESTINATION lib/${PROJECT_NAME}
)

# Configuración de ament para testing
if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  ament_lint_auto_find_test_dependencies()
endif()

# Exportar el paquete
ament_package()
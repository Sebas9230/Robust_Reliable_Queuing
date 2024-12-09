cmake_minimum_required(VERSION 3.10)

# Nombre del proyecto
project(RobustReliableQueuing)

# Versión de C++ requerida
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Directorios de cabeceras y fuentes
include_directories(${CMAKE_SOURCE_DIR}/include)
file(GLOB SOURCES ${CMAKE_SOURCE_DIR}/src/*.cpp)

# Buscar la librería ZeroMQ
find_package(ZeroMQ REQUIRED)

# Crear el ejecutable
add_executable(${PROJECT_NAME} ${SOURCES})

# Vincular las bibliotecas necesarias
target_link_libraries(${PROJECT_NAME} zmq)

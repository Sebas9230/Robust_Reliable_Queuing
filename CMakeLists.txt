cmake_minimum_required(VERSION 3.10)

# Nombre del proyecto
project(RobustReliableQueuing)

# Versión de C++ requerida
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Archivos fuente y cabeceras
set(SOURCES
    src/client.cpp
    src/worker.cpp
    src/broker.cpp
    src/main.cpp
)

set(HEADERS
    include/client.hpp
    include/worker.hpp
    include/broker.hpp
)

# Incluir directorios
include_directories(${CMAKE_SOURCE_DIR})

# Buscar la librería ZeroMQ
find_package(ZeroMQ REQUIRED)

# Crear el ejecutable
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

# Vincular las bibliotecas necesarias
target_link_libraries(${PROJECT_NAME} zmq)

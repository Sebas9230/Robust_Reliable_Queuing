cmake_minimum_required(VERSION 3.10)
project(RobustReliableQueuing)

set(CMAKE_CXX_STANDARD 17)

find_package(ZeroMQ REQUIRED)

include_directories(include)

add_executable(RobustReliableQueuing
    src/main.cpp
    src/broker.cpp
    src/worker.cpp
    src/client.cpp
)

target_link_libraries(RobustReliableQueuing zmq)

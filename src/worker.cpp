#include "worker.hpp"
#include <iostream>
#include <thread>
#include <chrono>

Worker::Worker(const std::string& brokerAddress)
    : context(1), socket(context, ZMQ_DEALER) {
    socket.connect(brokerAddress);
}

void Worker::processTasks() {
    while (true) {
        zmq::message_t task;
        socket.recv(task, zmq::recv_flags::none);

        std::string imageName = task.to_string();
        std::cout << "Processing image: " << imageName << std::endl;

        std::this_thread::sleep_for(std::chrono::seconds(2)); // Simulate processing

        std::string result = processImage(imageName);

        zmq::message_t resultMsg(result.size());
        memcpy(resultMsg.data(), result.c_str(), result.size());
        socket.send(resultMsg, zmq::send_flags::none);
    }
}

std::string Worker::processImage(const std::string& imageName) {
    return "Processed_" + imageName;
}

#include "worker.hpp"
#include <iostream>
#include <thread>
#include <chrono>

Worker::Worker(const std::string& id)
    : context(1), socket(context, ZMQ_DEALER), id(id) {
    socket.set(zmq::sockopt::routing_id, id);
    socket.set(zmq::sockopt::linger, 0); // Evita bloqueos al cerrar
    socket.set(zmq::sockopt::rcvtimeo, 5000); // Timeout de 5 segundos para recv
    socket.connect("tcp://localhost:5556");
}

void Worker::start() {
    while (true) {
        zmq::message_t client_id, request;
        socket.recv(client_id);
        socket.recv(request);

        std::string data(static_cast<char*>(request.data()), request.size());
        std::cout << "Worker " << id << " processing request: " << data << std::endl;

        std::this_thread::sleep_for(std::chrono::seconds(1)); // Simulate processing

        std::string result = "Processed: " + data;
        socket.send(client_id, zmq::send_flags::sndmore);
        socket.send(zmq::buffer(result), zmq::send_flags::none);
    }
}

#ifndef WORKER_HPP
#define WORKER_HPP

#include <zmq.hpp>
#include <string>

class Worker {
public:
    Worker(const std::string& brokerAddress);
    void processTasks();

private:
    zmq::context_t context;
    zmq::socket_t socket;

    std::string processImage(const std::string& imageName);
};

#endif // WORKER_HPP

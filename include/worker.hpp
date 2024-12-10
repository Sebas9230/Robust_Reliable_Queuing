#ifndef WORKER_HPP
#define WORKER_HPP

#include <zmq.hpp>
#include <string>

class Worker {
public:
    Worker(const std::string& id);
    void start();

private:
    zmq::context_t context;
    zmq::socket_t socket;
    std::string id;
};

#endif // WORKER_HPP

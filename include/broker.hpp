#ifndef BROKER_HPP
#define BROKER_HPP

#include <zmq.hpp>
#include <string>
#include <unordered_map>

class Broker {
public:
    Broker();
    void start();

private:
    zmq::context_t context;
    zmq::socket_t frontend; // Client requests
    zmq::socket_t backend;  // Worker requests
    std::unordered_map<std::string, int> workers; // Track workers' activity
};

#endif // BROKER_HPP

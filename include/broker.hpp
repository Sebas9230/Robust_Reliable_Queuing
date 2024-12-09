#ifndef BROKER_HPP
#define BROKER_HPP

#include <zmq.hpp>
#include <string>
#include <map>

class Broker {
public:
    Broker();
    void run();

private:
    zmq::context_t context;
    zmq::socket_t clients;
    zmq::socket_t workers;
};

#endif // BROKER_HPP

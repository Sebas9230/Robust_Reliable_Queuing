#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <zmq.hpp>
#include <string>

class Client {
public:
    Client(const std::string& brokerAddress);
    void sendRequest(const std::string& imageName);

private:
    zmq::context_t context;
    zmq::socket_t socket;
};

#endif // CLIENT_HPP

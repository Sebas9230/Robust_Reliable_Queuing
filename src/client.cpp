#include "client.hpp"
#include <iostream>

Client::Client(const std::string& brokerAddress)
    : context(1), socket(context, ZMQ_REQ) {
    socket.connect(brokerAddress);
}

void Client::sendRequest(const std::string& imageName) {
    zmq::message_t request(imageName.size());
    memcpy(request.data(), imageName.c_str(), imageName.size());
    socket.send(request, zmq::send_flags::none);

    zmq::message_t reply;
    socket.recv(reply, zmq::recv_flags::none);
    std::cout << "Client received reply: " << reply.to_string() << std::endl;
}

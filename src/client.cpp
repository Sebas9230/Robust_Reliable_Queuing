#include "client.hpp"
#include <iostream>

Client::Client()
    : context(1), socket(context, ZMQ_REQ) {
    socket.set(zmq::sockopt::linger, 0); // Evita bloqueos al cerrar
    socket.set(zmq::sockopt::rcvtimeo, 5000); // Timeout de 5 segundos para recv
    socket.connect("tcp://localhost:5555");
}

void Client::sendRequest(const std::string& data) {
    zmq::message_t message(data.begin(), data.end());
    socket.send(message, zmq::send_flags::none);
}

void Client::receiveResponse() {
    zmq::message_t response;
    socket.recv(response);
    std::string reply(static_cast<char*>(response.data()), response.size());
    std::cout << "Client received: " << reply << std::endl;
}

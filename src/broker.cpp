#include "broker.hpp"
#include <iostream>
#include <queue>

Broker::Broker()
    : context(1), clients(context, ZMQ_ROUTER), workers(context, ZMQ_ROUTER) {
    clients.bind("tcp://*:5555");
    workers.bind("tcp://*:5556");
}

void Broker::run() {
    zmq::pollitem_t items[] = {
        { clients, 0, ZMQ_POLLIN, 0 },
        { workers, 0, ZMQ_POLLIN, 0 }
    };

    std::queue<std::string> workerQueue;

    while (true) {
        zmq::poll(items, 2, -1);

        // Handle worker messages
        if (items[1].revents & ZMQ_POLLIN) {
            zmq::message_t workerIdentity;
            workers.recv(workerIdentity, zmq::recv_flags::none);

            zmq::message_t readySignal;
            workers.recv(readySignal, zmq::recv_flags::none);

            std::string workerId(static_cast<char*>(workerIdentity.data()), workerIdentity.size());
            workerQueue.push(workerId);
        }

        // Handle client messages
        if (items[0].revents & ZMQ_POLLIN && !workerQueue.empty()) {
            zmq::message_t clientIdentity;
            clients.recv(clientIdentity, zmq::recv_flags::none);

            zmq::message_t clientRequest;
            clients.recv(clientRequest, zmq::recv_flags::none);

            std::string workerId = workerQueue.front();
            workerQueue.pop();

            workers.send(zmq::buffer(workerId), zmq::send_flags::sndmore);
            workers.send(clientRequest, zmq::send_flags::none);

            zmq::message_t result;
            workers.recv(result, zmq::recv_flags::none);

            clients.send(clientIdentity, zmq::send_flags::sndmore);
            clients.send(result, zmq::send_flags::none);
        }
    }
}

#include "Broker.hpp"
#include <iostream>
#include <zmq.hpp>

Broker::Broker()
    : context(1), frontend(context, ZMQ_ROUTER), backend(context, ZMQ_ROUTER) {
    frontend.bind("tcp://*:5555");
    backend.bind("tcp://*:5556");
}

void Broker::start() {
    zmq::pollitem_t items[] = {
        { static_cast<void*>(frontend), 0, ZMQ_POLLIN, 0 },
        { static_cast<void*>(backend), 0, ZMQ_POLLIN, 0 }
    };

    while (true) {
        zmq::poll(items, 2, -1);

        // Handle client requests
        if (items[0].revents & ZMQ_POLLIN) {
            zmq::message_t client_id, request;
            frontend.recv(client_id);
            frontend.recv(request);
            if (!workers.empty()) {
                auto it = workers.begin();
                backend.send(it->first, zmq::send_flags::sndmore);
                backend.send(client_id, zmq::send_flags::sndmore);
                backend.send(request, zmq::send_flags::none);
                workers.erase(it);
            }
        }

        // Handle worker responses
        if (items[1].revents & ZMQ_POLLIN) {
            zmq::message_t worker_id, client_id, response;
            backend.recv(worker_id);
            backend.recv(client_id);
            backend.recv(response);
            frontend.send(client_id, zmq::send_flags::sndmore);
            frontend.send(response, zmq::send_flags::none);
            workers.emplace(worker_id.to_string(), 0);
        }
    }
}

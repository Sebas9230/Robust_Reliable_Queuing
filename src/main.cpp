#include "client.hpp"
#include "worker.hpp"
#include "broker.hpp"
#include <thread>

int main() {
    std::thread brokerThread([]() {
        Broker broker;
        broker.run();
    });

    std::thread workerThread([]() {
        Worker worker("tcp://localhost:5556");
        worker.processTasks();
    });

    std::thread clientThread([]() {
        Client client("tcp://localhost:5555");
        client.sendRequest("image1.jpg");
        client.sendRequest("image2.jpg");
    });

    brokerThread.join();
    workerThread.join();
    clientThread.join();

    return 0;
}

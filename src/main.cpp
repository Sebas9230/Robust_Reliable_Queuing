#include "Broker.hpp"
#include "Worker.hpp"
#include "Client.hpp"
#include <thread>

int main() {
    std::thread brokerThread([]() {
        Broker broker;
        broker.start();
    });

    std::thread workerThread1([]() {
        Worker worker("Worker-1");
        worker.start();
    });

    std::thread workerThread2([]() {
        Worker worker("Worker-2");
        worker.start();
    });

    std::this_thread::sleep_for(std::chrono::seconds(1)); // Allow broker and workers to initialize

    Client client;
    client.sendRequest("Task A");
    client.receiveResponse();

    client.sendRequest("Task B");
    client.receiveResponse();

    brokerThread.join();
    workerThread1.join();
    workerThread2.join();

    return 0;
}

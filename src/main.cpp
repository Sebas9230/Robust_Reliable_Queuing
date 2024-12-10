#include "broker.hpp"
#include "worker.hpp"
#include "client.hpp"
#include <thread>
#include <iostream>

int main() {
    std::cout << "Inicio del programa RobustReliableQueuing" << std::endl;
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

    std::cout << "Enviando Request Task A" << std::endl;
    Client client;
    client.sendRequest("Task A");
    client.receiveResponse();

    std::cout << "Enviando Request Task B" << std::endl;
    client.sendRequest("Task B");
    client.receiveResponse();

    brokerThread.join();
    workerThread1.join();
    workerThread2.join();

    return 0;
}

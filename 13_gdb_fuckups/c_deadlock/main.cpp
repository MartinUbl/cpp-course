#include <iostream>
#include <thread>
#include <mutex>
#include <queue>
#include <random>
#include <chrono>
#include <list>
#include <memory>

using namespace std::chrono_literals;

constexpr size_t ItemsPerProducer = 10000;
constexpr size_t ProducerConsumerCount = 10;

std::mutex mProdMtx, mConsMtx;

bool producerFlag;
bool running;
std::queue<int> itemQueue;

std::random_device rd;
std::default_random_engine eng(rd());
std::uniform_int_distribution<int> unif_dist(1, 10);

size_t generateProducerThing()
{
    std::unique_lock<std::mutex> lck(mProdMtx);

    std::this_thread::sleep_for(10ms);

    return unif_dist(eng);
}

void sendFeedback()
{
    std::unique_lock<std::mutex> lck(mProdMtx);

    std::this_thread::sleep_for(10ms);

    // TODO: store feedback
}

void producer()
{
    for (size_t i = 0; i < ItemsPerProducer; i++)
    {
        size_t element = generateProducerThing();

        std::unique_lock<std::mutex> lck(mConsMtx);

        itemQueue.push(element);
    }
}

void consumer()
{
    while (running)
    {
        std::unique_lock<std::mutex> lck(mConsMtx);

        if (!itemQueue.empty())
        {
            size_t elem = itemQueue.front();
            itemQueue.pop();

            std::this_thread::sleep_for(10ms);

            sendFeedback();
        }
        else if (!producerFlag)
            running = false;

        std::this_thread::yield();
    }
}


int main(int argc, char** argv)
{
    std::list<std::unique_ptr<std::thread>> prodList;
    std::list<std::unique_ptr<std::thread>> consList;

    running = true;
    producerFlag = true;

    for (size_t i = 0; i < ProducerConsumerCount; i++)
    {
        prodList.push_back(std::make_unique<std::thread>(producer));
        consList.push_back(std::make_unique<std::thread>(consumer));
    }

    for (auto& prod : prodList)
        prod->join();

    producerFlag = false;

    for (auto& con : consList)
        con->join();

    std::cout << "DONE" << std::endl;

    return 0;
}

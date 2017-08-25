#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
#include <vector>
#include <memory>
#include <string>

using namespace std::chrono_literals;

// pocet vlaken
const size_t countOfThreads = 50;
// pocet iteraci
const size_t iterationCount = 10000;

// mutex pro zamykani v ramci funkce vlakna
std::mutex mtx;

// globalni promenna - existuje jen v hlavnim zasobniku
size_t counter = 0;

// thread_local promenna - pro kazdy kontext vlakna se vytvori v jeho zasobniku znovu
thread_local size_t threadCounter = 0;

void thread_func(size_t idVlakna)
{
    for (size_t i = 0; i < iterationCount; i++)
    {
        // yield - predani rizeni jinemu vlaknu ve fronte
        std::this_thread::yield();

        // lock scope; technicky vzato by nemusela byt explicitne, ale pro prehlednost je lepsi
        {
            std::unique_lock<std::mutex> lck(mtx);

            counter = counter + 1;
            threadCounter = threadCounter + 1;
        }
    }

    std::cout << "Vlakno " << idVlakna << ": " << threadCounter << std::endl;
}



std::recursive_mutex rmtx;

void thread_func_2(int recurDepth)
{
    if (recurDepth <= 0)
    {
        std::cout << "!";
        return;
    }

    // je mozne (zde jiste), ze ten samy mutex ze stejneho kontextu muzeme zkusit zamknout vickrat
    // pro tento pripad recursive_mutex drzi per-thread ownership zaznamy, tedy nenuti nas zamykat znovu,
    // pokud jiz vlastnime zdroj; obycejny std::mutex toto neumi

    //std::unique_lock<std::mutex> lck(mtx);
    std::unique_lock<std::recursive_mutex> lck(rmtx);

    thread_func_2(recurDepth - 1);
}




int main(int argc, char** argv)
{
    std::cout << "----------- standardni pouziti mutexu" << std::endl;

    std::vector<std::unique_ptr<std::thread>> thrVector;
    thrVector.resize(countOfThreads);

    for (size_t i = 0; i < countOfThreads; i++)
        thrVector[i] = std::make_unique<std::thread>(thread_func, i);

    for (size_t i = 0; i < countOfThreads; i++)
        thrVector[i]->join();

    thrVector.clear();

    std::cout << "Pocitadlo: " << counter << std::endl;





    std::cout << "----------- rekurzivni mutex" << std::endl;

    thrVector.resize(countOfThreads);

    for (size_t i = 0; i < countOfThreads; i++)
        thrVector[i] = std::make_unique<std::thread>(thread_func_2, 5);

    for (size_t i = 0; i < countOfThreads; i++)
        thrVector[i]->join();

    std::cout << std::endl;

    thrVector.clear();





    std::cout << "----------- potreba zamknout vice mutexu" << std::endl;

    std::mutex mtx_1, mtx_2;

    {
        std::unique_lock<std::mutex> lck_1(mtx_1, std::defer_lock);
        std::unique_lock<std::mutex> lck_2(mtx_2, std::defer_lock);

        // zamky zatim nejsou zamceny!

        std::lock(lck_1, lck_2);

        // zamceny oba mutexy bez rizika deadlocku
    }


    return 0;
}

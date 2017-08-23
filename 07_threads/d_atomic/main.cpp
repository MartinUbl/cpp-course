#include <iostream>
#include <thread>
#include <atomic>
#include <string>
#include <vector>
#include <chrono>

using namespace std::chrono_literals;

const size_t countOfThreads = 50;
const size_t iterationCount = 10000;

// uzitim std::atomic odbourame potrebu zamykat mutex apod.; jsou vyuzity dostupne strojove instrukce pro atomickou inkrementaci, apod.
std::atomic<size_t> counter = 0;
//size_t counter = 0;

// zjednodusena funkce z prikladu na mutex, jen bez mutexu, s vyuzitim strojovych prostredku pro atomicke operace
void thread_func()
{
    for (size_t i = 0; i < iterationCount; i++)
    {
        // yield - predani rizeni jinemu vlaknu ve fronte
        std::this_thread::yield();

        // je nutne, aby slo o atomicky proveditelnou operaci - pricteni jednotky (+=), inkrementace (++), a dalsi
        counter++;
    }
}



int main(int argc, char** argv)
{
    std::cout << "----------- jednoduchy priklad std::atomic" << std::endl;

    // nasledujici kod je identicky jako v predchozich programech; lisi se jen kod vlaknove funkce

    std::vector<std::unique_ptr<std::thread>> thrVector;
    thrVector.resize(countOfThreads);

    for (size_t i = 0; i < countOfThreads; i++)
        thrVector[i] = std::make_unique<std::thread>(thread_func);

    for (size_t i = 0; i < countOfThreads; i++)
        thrVector[i]->join();

    thrVector.clear();

    std::cout << "Pocitadlo:         " << counter << std::endl;
    std::cout << "Ocekavana hodnota: " << (iterationCount*countOfThreads) << std::endl;


    return 0;
}

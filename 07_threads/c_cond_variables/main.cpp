#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>
#include <vector>

using namespace std::chrono_literals;

// pocet spawnenych vlaken
const size_t countOfThreads = 5;


// mutex pro pouziti nad podminkovou promennou
std::mutex cvMtx;
// barierova promenna (citac)
size_t thrCounter;
// podminkova promenna
std::condition_variable cv;

void thread_func_worker()
{
    // "simulace prace"
    for (size_t i = 0; i < 100; i++)
        std::this_thread::sleep_for(10ms);

    // zamkneme - nutne pro podminkovou promennou, a zde i pro praci se sdilenou promennou
    std::unique_lock<std::mutex> lck(cvMtx);

    thrCounter--;

    // pokud jsme posledni zijici vlakno, notify_all -> probudime vsechny cekajici
    if (thrCounter == 0)
    {
        std::cout << "N" << std::endl;;
        cv.notify_all();
    }
    else // jinak se uspime
    {
        std::cout << "W";
        cv.wait(lck, []() { return (thrCounter == 0); });

        // wait zahrnuje i ochranu proti vzbuzeni "omylem" (napr. spurious wakeup, popr. klidne i chyba v kodu)
        // a to pomoci "probouzeciho predikatu", zde zastoupeneho lambda funkci vracejici bool (true = muzeme vzbudit, false = jeste spi)
        // tento predikat je nepovinny; je vsak vhodne ho vyuzit
    }

    std::cout << "!" << std::endl;
}




void thread_func_pipeliner(size_t idThread)
{
    // nejdrive se zablokujeme a pockame na probuzeni
    std::unique_lock<std::mutex> lck(cvMtx);
    cv.wait(lck);

    std::cout << "Worker " << idThread << " START" << std::endl;

    // "prace"
    std::this_thread::sleep_for(500ms);

    std::cout << "Worker " << idThread << " END" << std::endl;

    // odblokujeme dalsi vlakno v poradi (pokud je; pokud ne, tak se nic nestane)
    cv.notify_one();
}




int main(int argc, char** argv)
{
    std::cout << "----------- bezne pouziti podminkove promenne, bariera" << std::endl;

    // nasledujici kod je identicky jako v predchozich programech; lisi se jen kod vlaknove funkce

    std::vector<std::unique_ptr<std::thread>> thrVector;
    thrVector.resize(countOfThreads);

    thrCounter = countOfThreads;
    for (size_t i = 0; i < countOfThreads; i++)
    {
        std::this_thread::sleep_for(500ms);

        thrVector[i] = std::make_unique<std::thread>(thread_func_worker);
    }

    for (size_t i = 0; i < countOfThreads; i++)
        thrVector[i]->join();

    thrVector.clear();





    std::cout << "----------- jiny pripad - 'seriova linka'" << std::endl;

    thrVector.resize(countOfThreads);

    for (size_t i = 0; i < countOfThreads; i++)
        thrVector[i] = std::make_unique<std::thread>(thread_func_pipeliner, i);

    // lock scope - abychom se zvladli synchronizovat s ostatnimi vlakny nad podminkou, musime zamknout stejny mutex
    {
        std::unique_lock<std::mutex> lck(cvMtx);
        // odblokujeme prvni vlakno; kazde dalsi je odblokovano predchozim pri dokonceni prace
        cv.notify_one();
    }

    for (size_t i = 0; i < countOfThreads; i++)
        thrVector[i]->join();

    thrVector.clear();


    return 0;
}

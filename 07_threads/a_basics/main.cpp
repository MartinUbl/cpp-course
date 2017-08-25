#include <iostream>
#include <thread>
#include <string>
#include <vector>

using namespace std::chrono_literals;


void thread_func(std::string jmenoVlakna)
{
    std::cout << "Vlakno " << jmenoVlakna << " bylo vytvoreno" << std::endl;

    // uspani vlakna na 1000ms
    //std::this_thread::sleep_for(std::chrono::milliseconds(1000));

    // za pouziti std::chrono_literals je mozne pouzit i zkraceny zapis
    std::this_thread::sleep_for(1000ms);

    std::cout << "Vlakno " << jmenoVlakna << " konci" << std::endl;
}




int main(int argc, char** argv)
{
    std::cout << "----------- standardni pouziti, bez dynamicke alokace s detach a pevnym cekanim" << std::endl;

    for (size_t i = 0; i < 5; i++)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
        std::thread thr(thread_func, std::to_string(i));
        thr.detach(); // pozor, i std::thread je v podstate RAII struktura; pouzijeme detach, aby se neuvolnily prostredky
    }

    // nemame jak cekat na vlakna - nemame na ne odkaz; musime proto pockat "nejakou dobu"
    // toto lze pouzit jen pokud zname tuto dobu, a ani tak to zdaleka neni korektni reseni
    std::this_thread::sleep_for(std::chrono::milliseconds(5000));




    std::cout << "----------- standardni pouziti, s dynamickou alokaci a join" << std::endl;

    std::vector<std::unique_ptr<std::thread>> thrVector;
    thrVector.resize(5);

    for (size_t i = 0; i < 5; i++)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(200));

        thrVector[i] = std::make_unique<std::thread>(thread_func, std::to_string(i));
        // uz neni nutny detach - alokujeme dynamicky
    }

    // volame join nad vsemi instancemi
    for (size_t i = 0; i < 5; i++)
        thrVector[i]->join();

    // nyni uz je bezpecne vlakna smazat - to se deje s vyprazdnenim vektoru, jelikoz v nem mame unique_ptr
    thrVector.clear();




    std::cout << "----------- s lambda funkci" << std::endl;

    thrVector.resize(5);

    for (size_t i = 0; i < 5; i++)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(200));

        thrVector[i] = std::make_unique<std::thread>([=]() {
            std::cout << "Start: " << i << std::endl;
            std::this_thread::sleep_for(1000ms);
            std::cout << "Stop: " << i << std::endl;
        });
    }

    for (size_t i = 0; i < 5; i++)
        thrVector[i]->join();

    thrVector.clear();


    return 0;
}

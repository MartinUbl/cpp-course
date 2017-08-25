#include <iostream>
#include <functional>
#include <thread>
#include <cmath>
#include <random>


int nejakafunkce(int a, int b, double c, double d)
{
    return (int)(c / d + a / b);
}



int main(int argc, char** argv)
{
    int someInt = 10;
    int anotherInt = 20;

    std::cout << "-------- Lambda funkce 1" << std::endl;

    // jednoducha lambda, jen pro pochopeni zakladu
    std::function<void()> f = []() {
        std::cout << "test" << std::endl;
    };

    f();
    f();
    f();





    std::cout << "-------- Lambda funkce 2 - capture by value" << std::endl;

    // lambda s predanim kontextu hodnotou ( [=] )
    // "vse" co je doted zde viditelne je predano jako const hodnota dovnitr funkce
    // someInt nelze modifikovat, pouze cist
    std::function<void()> f2 = [=]() {
        std::cout << "Lambda scope value: " << someInt << std::endl;
    };

    std::cout << "Outer scope value: " << someInt << std::endl;
    f2();

    // zde hodnotu zmenime, v lambda funkci byla ale zachycena hodnota drive, pred modifikaci
    someInt += 66;

    std::cout << "Outer scope value: " << someInt << std::endl;
    f2();




    someInt = 10; // vratime hodnotu na 10

    std::cout << "-------- Lambda funkce 3 - capture by reference" << std::endl;

    // lambda s predanim kontextu referenci ( [&] )
    // vse se dovnitr predava referenci na promenne/atributy doposud deklarovane
    std::function<void()> f3 = [&]() {
        std::cout << "Lambda scope value: " << someInt << std::endl;
    };

    std::cout << "Outer scope value: " << someInt << std::endl;
    f3();

    // zde hodnotu zmenime, v lambda funkci se tentokrat zmena projevi - ma referenci na promennou
    someInt += 66;

    std::cout << "Outer scope value: " << someInt << std::endl;
    f3();





    std::cout << "-------- Lambda funkce 4 - capture specifickych promennych" << std::endl;

    // referenci predame treba someInt, hodnotou anotherInt
    std::function<void()> f4 = [&someInt, anotherInt]() {
        std::cout << "Lambda someInt: " << someInt << std::endl;
        std::cout << "Lambda anotherInt: " << anotherInt << std::endl;

        someInt++; // predano referenci, muzeme modifikovat
    };

    std::cout << "someInt before: " << someInt << std::endl;
    f4();
    std::cout << "someInt after: " << someInt << std::endl;






    std::cout << "-------- Lambda funkce 5 - navratova hodnota a parametry" << std::endl;

    // referenci predame treba someInt, hodnotou anotherInt
    std::function<int(int, int)> f5 = [=](int a, int b) {
        return a*a + b*b;
    };

    std::cout << "f5(2,5) = " << f5(2,5) << std::endl;





    std::cout << "-------- Lambda funkce 6 - pouziti pro vlakna" << std::endl;

    std::thread testThread1([=]() {
        for (size_t i = 0; i < 100; i++)
            std::cout << "1";
    });
    std::thread testThread2([=]() {
        for (size_t i = 0; i < 100; i++)
            std::cout << "2";
    });

    testThread1.join();
    testThread2.join();

    std::cout << "...KONEC" << std::endl;





    std::cout << "-------- std::bind" << std::endl;

    // pokud vime, ze budeme potrebovat jen druhou mocninu, tzn. ze druhy parametr bude vzdy 2, lze si vyvorit zkratku
    // placeholders::_1 zastupuje parametr, ktery doplnime az ho budeme potrebovat doplnit
    // "auto" viz dalsi kapitoly - automaticka dedukce typu, u std::bind se vazne hodi
    auto druha_mocnina = std::bind(powf, std::placeholders::_1, 2.0f);

    std::cout << "druha_mocnina(5.0) = " << druha_mocnina(5.0f) << std::endl;




    std::cout << "-------- std::bind 2" << std::endl;

    // pokud vime, ze budeme potrebovat jen druhou mocninu, tzn. ze druhy parametr bude vzdy 2, lze si vyvorit zkratku
    // placeholders::_1 zastupuje parametr, ktery doplnime az ho budeme potrebovat doplnit
    // "auto" viz dalsi kapitoly - automaticka dedukce typu, u std::bind se vazne hodi
    auto pocitani = std::bind(nejakafunkce, std::placeholders::_1, 2, std::placeholders::_2, 5.0);

    std::cout << "pocitani(4, 10.0) = nejakafunkce(4, 2, 10.0, 5.0) = " << pocitani(4, 10.0) << std::endl;




    std::cout << "-------- std::bind 3" << std::endl;

    // znama deklarace z kapitoly 8
    std::random_device r;
    std::default_random_engine re(r());
    std::uniform_int_distribution<int> uidist(1, 10);

    // normalne bychom museli volat vzdy uidist(re), tedy dodavat argument; jelikoz se to ale muze stat nepohodlnym
    // a my vime, ze nebudeme pouzivat jiny random engine (velmi casto tomu tak je), tak muzeme provest binding,
    // abychom se otravneho redundantního argumentu zbavili
    auto rnd = std::bind(uidist, re);

    // lze vytvorit i zastupnou lambdu, ovsem to je zbytecne velky overhead - musi se vytvorit funkcni kontext, lambda
    // se musi nekam vytvorit jako normalni funkce, musi se predat parametry... a to je v praxi mnohem drazsi nez bind
    // podobny overhead by byl i s beznou funkci, std::bind ho vyrazne redukuje, setri praci a misto a nervy
    auto rndFunc = [&]() { return uidist(re); };

    std::cout << rnd() << ", " << rnd() << ", " << rnd() << ", " << rnd() << ", " << rnd() << ", " << rnd() << std::endl;

    std::cout << rndFunc() << ", " << rndFunc() << ", " << rndFunc() << ", " << rndFunc() << ", " << rndFunc() << ", " << rndFunc() << std::endl;

    return 0;
}

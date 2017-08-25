#include <iostream>
#include <queue>
#include <stack>
#include <array>
#include <tuple>
#include <string>

std::tuple<std::string, double, double> getBodyProportions(size_t index)
{
    switch (index)
    {
        case 0: return { "Bonifac", 190.0, 95.0 };
        case 1: return { "Zvonimir", 175.0, 72.0 };
        case 2: return { "Herbert", 145.0, 102.0 };
        default:
            return { "Unknown", 0.0, 0.0 };
    }
}



int main(int argc, char** argv)
{
    std::cout << "----------- Fronta" << std::endl;

    std::queue<int> ique;

    // push - vlozit prvek do fronty
    ique.push(1);
    ique.push(2);
    ique.push(3);
    ique.push(4);
    ique.push(5);

    while (!ique.empty())
    {
        // front - vybere nejstarsi prvek z fronty (front - predni prvek)
        int el = ique.front();
        // pop - vezme predni prvek fronty a z fronty ho vybere
        ique.pop();

        std::cout << "Prvek: " << el << std::endl;
    }



    std::cout << "----------- Zasobnik" << std::endl;

    std::stack<int> istck;

    // push - vlozit prvek do zasobniku
    istck.push(1);
    istck.push(2);
    istck.push(3);
    istck.push(4);
    istck.push(5);

    while (!istck.empty())
    {
        int el = istck.top(); // jediny rozdil oproti fronte: top misto front
        istck.pop();

        std::cout << "Prvek: " << el << std::endl;
    }


    std::cout << "----------- Konstantni pole" << std::endl;

    // pole musi mit narozdil od vektoru nebo jinych struktur pevne stanovenou velikost jiz v dobe kompilace
    // - to zaruci inicializace skrze sablonu (sablony viz dalsi kapitoly)
    std::array<int, 5> ipole;

    ipole.fill(10); // vyplni pole samymi 10

    // 1) range-based for
    for (int& i : ipole)
        std::cout << "Prvek: " << i << std::endl;

    std::cout << "---" << std::endl;

    // 2) iteratory (fuj)
    for (std::array<int, 5>::iterator itr = ipole.begin(); itr != ipole.end(); ++itr)
        std::cout << "Prvek: " << *itr << std::endl;

    std::cout << "---" << std::endl;

    // 3) klasicky pres indexy (asi nejlepsi)
    for (size_t i = 0; i < ipole.size(); i++)
        std::cout << "Prvek: " << ipole[i] << std::endl;



    std::cout << "----------- Pair" << std::endl;

    // vice moznych variant inicializace
    std::pair<int, double> pr(1, 5.0);
    //std::pair<int, double> pr = std::make_pair(1, 5.0);
    //std::pair<int, double> pr = std::make_pair<>(1, 5.0);
    //std::pair<int, double> pr = std::make_pair<int, double>(1, 5.0);

    std::cout << "First: " << pr.first << ", second: " << pr.second << std::endl;





    std::cout << "----------- Tuple" << std::endl;

    //std::tuple<int, int, int> tup(1, 2, 3);
    //std::tuple<int, int, int> tup = std::make_tuple(1, 2, 3);
    //std::tuple<int, int, int> tup = std::make_tuple<>(1, 2, 3);
    std::tuple<int, int, int> tup = std::make_tuple<int, int, int>(15, 30, 45);

    std::cout << "0: " << std::get<0>(tup) << ", 1: " << std::get<1>(tup) << ", 2: " << std::get<2>(tup) << std::endl;

    // tuple jde "rozbit" pomoci std::tie
    int a, b, c;
    std::tie(a, b, c) = tup;

    std::cout << "a: " << a << ", b: " << b << ", c: " << c << std::endl;

    // tuple se hodi napr. pokud potrebujeme vratit z funkce vetsi mnozstvi hodnot najednou v pevne forme
    std::string jmeno;
    double vyska, hmotnost;

    // std::tie - roztrzeni tuple na jednotlive hodnoty
    std::tie(jmeno, vyska, hmotnost) = getBodyProportions(0);

    std::cout << "index 0: Jmeno: " << jmeno << ", vyska: " << vyska << ", hmotnost: " << hmotnost << std::endl;

    return 0;
}

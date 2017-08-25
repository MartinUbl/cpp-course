#include <iostream>
#include <vector>
#include <list>
#include <map>
#include <set>

int main(int argc, char** argv)
{
    // tato cast je spise opakovani

    // abychom meli s cim pracovat...
    std::vector<int> ivec = { 5, 10, 8, 6, 3, 4, 9 };
    std::list<int> ilist = { 10, 8, 7, 6, 2, 3, 5 };
    std::map<int, int> imap = {
        { 1, 5 }, { 3, 8 }, { 5, 9 }, { 7, 12 }, { 9, 88 }
    };
    std::set<int> iset = { 1, 8, 9, 15, 25, 36 };



    std::cout << "--------- std::vector" << std::endl;

    // vector pruchod - prvky lze modifikovat
    for (int& cislo : ivec)
    {
        std::cout << "Modifikuji " << cislo << std::endl;
        cislo++;
    }

    for (int& cislo : ivec)
        std::cout << "Modifikovane " << cislo << std::endl;




    std::cout << "--------- std::list" << std::endl;

    // stejne tak v listu lze modifikovat
    for (int& cislo : ilist)
    {
        std::cout << "Modifikuji " << cislo << std::endl;
        cislo++;
    }

    for (int& cislo : ilist)
        std::cout << "Modifikovane " << cislo << std::endl;





    std::cout << "--------- std::map" << std::endl;

    // v mape lze modifikovat pouze hodnota, nikoliv klic!
    for (auto& cislo : imap)
    {
        std::cout << "Modifikuji " << cislo.first << " : " << cislo.second << std::endl;
        //cislo.first++; // chyba!
        cislo.second++;
    }

    for (auto& cislo : imap)
        std::cout << "Modifikovane " << cislo.first << " : " << cislo.second << std::endl;




    std::cout << "--------- std::set" << std::endl;

    // v setu nelze modifikovat nic!
    for (auto& cislo : iset)
    {
        std::cout << "Nemodifikuji " << cislo << std::endl;
        //cislo++; // chyba!
    }


    return 0;
}

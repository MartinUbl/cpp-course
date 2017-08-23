#include <iostream>
#include <list>

int main(int argc, char** argv)
{
    std::list<int> a;

    // pridani prvku - zde bez reserve, jelikoz v podstate neni co rezervovat - nedochazi k realokaci, jde o spojovy seznam
    a.push_back(5);
    a.push_back(10);
    a.push_back(15);

    // pruchod listu - 1) iteratory
    for (std::list<int>::iterator itr = a.begin(); itr != a.end(); ++itr)
        std::cout << *itr << std::endl;

    // pruchod listu - 2) range-based for
    for (int& p : a)
        std::cout << p << std::endl;

    // pruchod listu pozpatku - jedine iteratory, ale specialni, reverse iteratory
    for (std::list<int>::reverse_iterator itr = a.rbegin(); itr != a.rend(); ++itr)
        std::cout << *itr << std::endl;

    // list nelze prochazet pres indexy - takovy pristup by vyzadoval pokazde doiterovat pres prvky az na dany prvek






    // mazani - obdobne jako u vektoru, tedy uzitim iteratoru
    // POZOR: iterator listu nema pretizeny operator +, musime zvolit jiny pristup posunuti iteratoru
    std::list<int>::iterator eitr;

    // 1) std::advance - funkce stavena na posouvani iteratoru
    eitr = a.begin();
    std::advance(eitr, 2);

    // 2) vlastni pristup - v poradku, ale proc, kdyz uz na nas mysleli s std::advance
    eitr = a.begin();
    for (size_t i = 0; i < 2; i++)
        eitr++;

    a.erase(eitr);



    std::cout << "--------------------" << std::endl;

    // selektivni promazani seznamu

    std::list<int> someNumbers = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 };

    // casta chyba: mazani iteratoru a jeho nasledna inkrementace --> problem
    /*
    for (std::list<int>::iterator itr = someNumbers.begin(); itr != someNumbers.end(); ++itr)
    {
        int hodnota = *itr;

        if (hodnota % 3 == 0)
            someNumbers.erase(itr);
    }
    */

    // spravne uziti iteratoru pro mazani
    for (std::list<int>::iterator itr = someNumbers.begin(); itr != someNumbers.end(); /* tady prazdno! */)
    {
        int hodnota = *itr;

        if (hodnota % 3 == 0)
            itr = someNumbers.erase(itr); // erase vzdy vraci novy iterator, ktery ukazuje na dalsi prvek
        else
            ++itr;
    }


    for (int& p : someNumbers)
        std::cout << p << std::endl;




    return 0;
}

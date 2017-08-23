#include <iostream>
#include <vector>

// testovaci trida, abychom videli, kdy se vola konstruktor
class Test
{
    public:
        Test() { std::cout << "Test()" << std::endl; };
};


int main(int argc, char** argv)
{
    // resize + klasicky pristup jako k poli
    std::vector<int> a;
    a.resize(3);

    a[0] = 1;
    a[1] = 5;
    a[2] = 10;



    // push_back prisup - muze byt neprijemny k pameti (realokace) --> tzn. pomalejsi
    std::vector<int> b;
    b.push_back(2);
    b.push_back(6);
    b.push_back(11);





    // reserve + push_back pristup - zamezi realokaci (alokuje potrebnou pamet), ale neinicializuje prvky
    // - pravdepodobne optimalni pristup, v praxi ale nemusi byt uplne dosazitelny
    std::vector<int> c;
    c.reserve(3);

    c.push_back(3);
    c.push_back(7);
    c.push_back(12);




    // inicializace konstantnim polem; optimalni vzhledem k moznostem (interne provede reserve a naplni pamet primo kopii)
    std::vector<int> d = { 10, 20, 30, 40 };





    size_t i;

    // pruchod vektoru - 1) indexy
    for (i = 0; i < a.size(); i++)
        std::cout << "a[" << i << "] = " << a[i] << std::endl;


    // pruchod vektoru - 2) iteratory - muze byt pomalejsi!
    i = 0;
    for (std::vector<int>::iterator itr = b.begin(); itr != b.end(); itr++, i++)
        std::cout << "b[" << i << "] = " << *itr << std::endl;


    // pruchod vektoru - 3) range-based for
    i = 0;
    for (int p : c)
        std::cout << "c[" << (i++) << "] = " << p << std::endl;

    // pro pruchod doporucuji pouzivat zpusob 1 nebo 3; u vektoru mi ale prijde logictejsi 1





    // mazani z vektoru - nelze indexem, musime pouzit iterator
    // - neni efektivni, musi preusporadat vsechny nasledujici prvky o index zpet; jina moznost vsak neexistuje
    c.erase(c.begin() + 2);




    // vyzaduje nejaka funkce int*, a my mame pouze std::vector<int>? Nevadi
    // - pamet alokovana std::vector metodami je souvisla, ale adresa se muze
    // modifikaci menit!

    int* a_ptr = &a[0];

    a.resize(20); // puvodni velikost = 3, zvetseni na 20 takrka urcite vyvola realokaci

    int* a_ptr_2 = &a[0];

    // adresy budou velmi pravdepodobne jine
    std::cout << "a_1: " << (long long)a_ptr << ", a_2: " << (long long)a_ptr_2 << std::endl;






    std::vector<Test> t_a;
    std::vector<Test> t_b;

    std::cout << "Reserve BEFORE" << std::endl;
    t_a.reserve(10);
    std::cout << "Reserve AFTER" << std::endl;
    std::cout << "Resize BEFORE" << std::endl;
    t_b.resize(10);
    std::cout << "Resize AFTER" << std::endl;

    // metoda at() kontroluje za behu, zdali se snazime pristoupit na existujici prvek; pokud ne, vyhodi vyjimku
    // tento pristup je pomalejsi, ale bezpecnejsi; nicmene v praxi se mnohem vice vyplati pristup pres indexy
    // nebo range-based pruchod
    try
    {
        t_a.at(1);
    }
    catch (std::out_of_range const& )
    {
        std::cout << "t_a.at(1) - out of range" << std::endl;
    }

    try
    {
        t_b.at(1);
    }
    catch (std::out_of_range const& )
    {
        std::cout << "t_b.at(1) - out of range" << std::endl;
    }

    return 0;
}

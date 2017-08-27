#include <iostream>
#include <map>
#include <cstring>

class Tlacitko
{
    private:
        int cislo;

    public:
        Tlacitko() : cislo(666)
        {
        }

        Tlacitko(int _cislo) : cislo(_cislo)
        {
        }

        int getCislo() const
        {
            return cislo;
        }
};

// komparacni funktor pro mapu a const char* typ
struct constchar_comparator
{
    bool operator()(const char *a, const char *b) const
    {
        return strcmp(a, b) < 0;
    }
};



int main(int argc, char** argv)
{
    std::map<int, double> m1;

    // vkladani - 1) insert std::pair - fuj
    m1.insert(std::pair<int, double>(1, 12.2));

    // vkladani - 2) indexem
    m1[2] = 20.4;
    m1[3] = 14.5;
    m1[99] = 1.2;


    std::cout << "----------- Pruchody" << std::endl;

    // pruchod - iteratory (pravdepodobne lepsi)
    for (std::map<int, double>::iterator itr = m1.begin(); itr != m1.end(); ++itr)
        std::cout << "Key: " << itr->first << ", Value: " << itr->second << std::endl;

    // pruchod - range-based for (pozor, zde jen hodnotou nebo const referenci; mapa si zajistuje, ze pri pruchodu nebude modifikovan klic)
    for (std::pair<int, double> item : m1)
        std::cout << "Key: " << item.first << ", Value: " << item.second << std::endl;

    // v praxi ale pruchod mapou neni zas tak casto potreba - vyuziva se vlastnosti pro lookup v O(1)

    std::cout << "----------- Vyzvedavani pod indexy" << std::endl;

    // vyzvedavani prvku dle indexu
    std::cout << m1[2] << std::endl;
    // neexistujici prvek - vytvori se!
    std::cout << m1[55] << std::endl;


    // pruchod s const referenci, popr. staci konstantni klic
    //for (std::pair<int, double> const& item : m1)
    for (std::pair<const int, double>& item : m1)
        std::cout << "Key: " << item.first << ", Value: " << item.second << std::endl;




    std::cout << "----------- Prohledavani klicu" << std::endl;

    for (int i = 0; i < 5; i++)
    {
        if (m1.find(i) == m1.end())
            std::cout << "Key " << i << " not found" << std::endl;
        else
            std::cout << "Key " << i << ": " << m1[i] << std::endl;
    }



    std::cout << "----------- Mazani" << std::endl;

    // mazani - lze podle klice, nemusime mit iterator
    m1.erase(3);
    m1.erase(99);
    // ... ale muzeme
    m1.erase(m1.find(55));

    for (std::pair<int, double> item : m1)
        std::cout << "Key: " << item.first << ", Value: " << item.second << std::endl;


    std::cout << "----------- Objekt jako klic" << std::endl;



    // objekty objevujici se v mape musi mit vychozi (bezparametricky) konstruktor!
    std::map<int, Tlacitko> tlacMap;

    std::cout << "Cislo: " << tlacMap[5].getCislo() << std::endl;




    std::cout << "----------- Mapa s const char* klicem" << std::endl;

    // mapa s const char* klicem - problem, mapa porovnava na rovnost, popr. nerovnost, v tomto pripade jde o porovnavani adres!
    std::map<const char*, int> cmap;

    cmap["ahoj"] = 5;
    cmap["zdar"] = 10;

    std::cout << "ahoj: " << cmap["ahoj"] << std::endl;




    std::cout << "----------- Mapa s std::string klicem" << std::endl;

    // kod je identicky s predchozim pripadem, jen misto const char* pouzivame std::string
    // nyni jiz vse funguje, std::string ma pretizene operatory ==, !=, < i >, zakladni komparator proto funguje
    std::map<std::string, int> smap;

    smap["ahoj"] = 5;
    smap["zdar"] = 10;

    std::cout << "ahoj: " << smap["ahoj"] << std::endl;



    std::cout << "----------- Mapa s const char* klicem a komparatorem" << std::endl;

    // mapa s const char* klicem, ale vlastnim komparatorem (funktor nebo lambda funkce) - problem je take vyresen
    std::map<const char*, int, constchar_comparator> ccmap;

    ccmap["ahoj"] = 5;
    ccmap["zdar"] = 10;

    std::cout << "ahoj: " << ccmap["ahoj"] << std::endl;

    return 0;
}

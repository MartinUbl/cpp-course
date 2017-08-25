#include <iostream>
#include <set>

struct constchar_comparator
{
    bool operator()(const char *a, const char *b) const
    {
        return strcmp(a, b) < 0;
    }
};



int main(int argc, char** argv)
{
    std::set<int> iset;

    // vkladani jednoduse
    iset.insert(5);
    // uziti "initializer list", v podstate pole hodnot ke vlozeni; muze se vymstit pokud jde o nejaky objekt a ne primitivni dat. typ
    iset.insert({1,2,8});
    // vlozeni duplikatu - nevlozi se podruhe
    iset.insert(5);
    // vlozeni duplikatu
    iset.insert(2);



    std::cout << "----------- Pruchod" << std::endl;

    // opet lze projit jako kazdy jiny container - 1) iteratory
    for (std::set<int>::iterator itr = iset.begin(); itr != iset.end(); ++itr)
        std::cout << "Element: " << *itr << std::endl;

    std::cout << "----" << std::endl;

    // 2) range-based for - opet bud jako kopie prvku (zde) nebo konstantni reference; u primitivnich dat. typu je to vcelku jedno
    for (int i : iset)
        std::cout << "Element: " << i << std::endl;




    std::cout << "----------- Prohledani podle prvku" << std::endl;

    // takove prohledani je stejne jako u mapy
    for (int i = 0; i < 10; i++)
    {
        if (iset.find(i) == iset.end())
            std::cout << "Key " << i << " not found" << std::endl;
        else
            std::cout << "Key " << i << " found!" << std::endl;
    }



    size_t res;

    // erase vraci vzdy pocet smazanych prvku
    res = iset.erase(5);
    std::cout << "erase(5): " << res << std::endl;
    res = iset.erase(69);
    std::cout << "erase(69): " << res << std::endl;





    std::cout << "----------- std::set s const char* prvky" << std::endl;

    // const char* prvky, stejny problem jako u mapy
    std::set<const char*> cset;

    cset.insert("ahoj");
    cset.insert("ahoj");
    cset.insert("ahoj");

    for (const char* cc : cset)
        std::cout << "Element: " << cc << std::endl;



    std::cout << "----------- std::set s std::string prvky" << std::endl;

    // std::string resi pretizenim operatoru pro porovnani
    std::set<std::string> sset;

    sset.insert("ahoj");
    sset.insert("ahoj");
    sset.insert("ahoj");

    for (std::string cc : sset)
        std::cout << "Element: " << cc.c_str() << std::endl;



    std::cout << "----------- std::set s const char* prvky a komparatorem" << std::endl;

    // const char* prvky, problem komparace vyresen pridanym funktorem pro porovnani
    std::set<const char*, constchar_comparator> ccset;

    ccset.insert("ahoj");
    ccset.insert("ahoj");
    ccset.insert("ahoj");

    for (const char* cc : ccset)
        std::cout << "Element: " << cc << std::endl;

    return 0;
}

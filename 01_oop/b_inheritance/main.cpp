#include <iostream>
#include <string>

#include "rodic.h"
#include "timmy.h"
#include "jimmy.h"

const char* valid(void* mem)
{
    return (mem ? "valid" : "null");
}

int main(int argc, char** argv)
{
    // !!! Nepovede se, Rodic je abstraktni trida (diky plne virtualni metode "motto")
    //Rodic r("Kenny");

    Timmy timmy;
    Jimmy jimmy;

    Rodic &timmyR = timmy;

    // lastName vrati rozdilne hodnoty - nejde o virtualni metodu - jednou se chova jako clen tridy Timmy, jednou jako clen tridy Rodic, podle na kterou je prave pretypovana
    // specialAbility ale vrati hodnoty stejne - je to virtualni metoda - vzdy se chova jako clen tridy Timmy, jelikoz je uvedena v tabulce virtualnich metod

    std::cout << "timmy:   " << timmy.firstName() << " " << timmy.lastName() << ", special ability: " << timmy.specialAbility() << std::endl;
    std::cout << "timmyR:  " << timmyR.firstName() << " " << timmyR.lastName() << ", special ability: " << timmyR.specialAbility() << std::endl;

    // s ukazatelem je efekt stejny, reference je jen "bezpecna varianta ukazatele rizena kompilatorem"

    Rodic* timmyRP = &timmy;

    std::cout << "timmyRP: " << timmyRP->firstName() << " " << timmyRP->lastName() << ", special ability: " << timmyRP->specialAbility() << std::endl;

    std::cout << std::endl;

    /////////// stejny pokus s Jimmym

    Rodic &jimmyR = jimmy;

    std::cout << "jimmy:   " << jimmy.firstName() << " " << jimmy.lastName() << ", special ability: " << jimmy.specialAbility() << std::endl;
    std::cout << "jimmyR:  " << jimmyR.firstName() << " " << jimmyR.lastName() << ", special ability: " << jimmyR.specialAbility() << std::endl;

    std::cout << std::endl;

    // jen hratky s virtualnimi metodami - je videt, ze ackoliv metoda "motto" neni v rodici definovana, je vyvolana spravne, jelikoz ji (povinne) potomek prepisuje
    // a je uvedena v tabulce virtualnich metod

    std::cout << "timmy motto:   " << timmy.motto() << std::endl;
    std::cout << "timmyR motto:  " << timmyR.motto() << std::endl;

    std::cout << "jimmy motto:   " << jimmy.motto() << std::endl;
    std::cout << "jimmyR motto:  " << jimmyR.motto() << std::endl;

    std::cout << std::endl;


    /////////// hratky s pretypovanim

    // timmyRP ukazuje na objekt typu Timmy (to vime)

    // static_cast se povede v podstate vzdy
    // dynamic_cast se povest nemusi - nepovede se tehdy, pokud se snazime pretypovat na takovy typ, ktery nepasuje

    // zde neni problem nikde, jelikoz vime, ze predek byl Timmy
    Timmy* timmySC = static_cast<Timmy*>(timmyRP);
    Timmy* timmyDC = dynamic_cast<Timmy*>(timmyRP);

    // static_cast projde vzdy - neprovadi kontrolu typu
    // dynamic_cast ale vrati nulu, jelikoz zkontroloval typy a zjistil, ze nesouhlasi
    Jimmy* jimmySC = static_cast<Jimmy*>(timmyRP);
    Jimmy* jimmyDC = dynamic_cast<Jimmy*>(timmyRP);

    std::cout << "timmySC: " << valid(timmySC) << std::endl;
    std::cout << "timmyDC: " << valid(timmyDC) << std::endl;
    std::cout << "jimmySC: " << valid(jimmySC) << std::endl;
    std::cout << "jimmyDC: " << valid(jimmyDC) << std::endl;

    return 0;
}

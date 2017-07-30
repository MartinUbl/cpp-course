#include <iostream>
#include <string>

#include "elephant.h"
#include "pig.h"
#include "elepig.h"

int main(int argc, char** argv)
{
    Elephant mother;
    Pig father;

    ElePig son = mother.MakeLove(father);

    std::cout << "Mother: species: " << mother.whoAmI() << std::endl
              << "        ears: " << mother.ears() << std::endl
              << "        nose: " << mother.nose() << std::endl;

    std::cout << "---------------------------------------" << std::endl;

    std::cout << "Father: species: " << father.whoAmI() << std::endl
              << "        ears: " << father.ears() << std::endl
              << "        nose: " << father.nose() << std::endl;

    std::cout << "---------------------------------------" << std::endl;

    std::cout << "Son:    species: " << son.whoAmI() << std::endl
              << "        ears: " << son.ears() << std::endl
              << "        nose: " << son.nose() << std::endl;

    Pig& pigSon = son;
    Elephant& elephantSon = son;

    std::cout << "---------------------------------------" << std::endl;

    std::cout << "Son:    species: " << pigSon.whoAmI() << std::endl
        << "        ears: " << pigSon.ears() << std::endl
        << "        nose: " << pigSon.nose() << std::endl;

    std::cout << "---------------------------------------" << std::endl;

    std::cout << "Son:    species: " << elephantSon.whoAmI() << std::endl
        << "        ears: " << elephantSon.ears() << std::endl
        << "        nose: " << elephantSon.nose() << std::endl;


    std::cout << "---------------------------------------" << std::endl;
    std::cout << "---------------------------------------" << std::endl;

    // !!! kompilator hazi chybu: nelze dedukovat v case kompilace, zdali lze pretypovat z Pig na Elephant (kompilator nevi, zdali pigSon je ve skutecnosti ElePig)
    //Elephant& pigElephantSon = static_cast<Elephant&>(pigSon);
    // !!! to same chovani prichazi i s pointerem
    //Elephant* pigElephantSonP = static_cast<Elephant*>(&pigSon);

    // kompilator nehazi chybu - kontrola typu se odlozi do runtime
    // ale co kdyz u reference (nemuze byt null) selze pretypovani? --> vyjimka, musime odchytit; vyjimky viz dalsi kapitoly, ted jen pro nazornost

    try
    {
        Elephant& pigElephantSon = dynamic_cast<Elephant&>(pigSon);

        std::cout << "Pretypovani se povedlo!" << std::endl;
    }
    catch (std::bad_cast &e)
    {
        std::cout << "Nepovedlo se: " << e.what() << std::endl;
    }

    try
    {
        Elephant& elephantFather = dynamic_cast<Elephant&>(father);

        std::cout << "Pretypovani se povedlo!" << std::endl;
    }
    catch (std::bad_cast &e)
    {
        std::cout << "Nepovedlo se: " << e.what() << std::endl;
    }

    // u pointeru neni vyhazovana vyjimka - muzeme totiz dat vedet pomoci "null", ze se pretypovani nepovedlo

    Elephant* elephantFatherP = dynamic_cast<Elephant*>(&father);
    if (elephantFatherP)
        std::cout << "Pretypovani se povedlo!" << std::endl;
    else
        std::cout << "Nepovedlo se!" << std::endl;

    return 0;
}

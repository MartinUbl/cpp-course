#include <iostream>
#include <memory>

struct Coordinates
{
    Coordinates() : x(0), y(0)
    {
    }

    Coordinates(double _x, double _y) : x(_x), y(_y)
    {
    }

    double x;
    double y;
};



int main(int argc, char** argv)
{
    std::cout << "----------- klasicke pouziti" << std::endl;

    std::shared_ptr<Coordinates> coords;
    Coordinates* bxx;

    // scope kolem shared_ptr
    {
        std::shared_ptr<Coordinates> a = std::make_shared<Coordinates>(5.5, 12.5);

        // zde uz kopie funguje - zvysi se citac referenci s konstruktorem
        std::shared_ptr<Coordinates> b = a;

        // ve vnejsi scope mame promennou "coords" - to zaruci, ze referencni citac neklesne na nulu po opusteni teto scope
        coords = b;

        bxx = b.get();

        std::cout << "bxx->x uvnitr: " << bxx->x << std::endl;
    }

    std::cout << "bxx->x vne: " << bxx->x << std::endl;






    std::cout << "----------- klasicke pouziti 2" << std::endl;

    // scope kolem shared_ptr
    {
        std::shared_ptr<Coordinates> a = std::make_shared<Coordinates>(5.5, 12.5);

        // zde uz kopie funguje - zvysi se citac referenci s konstruktorem
        std::shared_ptr<Coordinates> b = a;

        // nyni nepriradime do vnejsi promenne "coords"
        // --> po opusteni scope je pamet smazana

        bxx = b.get();

        std::cout << "bxx->x uvnitr: " << bxx->x << std::endl;
    }

    std::cout << "bxx->x vne: " << bxx->x << std::endl;

    return 0;
}

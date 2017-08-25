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
    // vnejsi weak_ptr - nepodili se na reference countingu, takze na nej nema scope moc vliv
    std::weak_ptr<Coordinates> p;

    // scope shared_ptr
    {
        std::shared_ptr<Coordinates> a = std::make_shared<Coordinates>(2.5, 5.5);

        p = a;

        // standardni prace s weak_ptr - nejdrive je treba ho "docasne prevest na shared_ptr"
        // zde se podari - reference stale existuje
        if (std::shared_ptr<Coordinates> sptr = p.lock())
            std::cout << "Uvnitr: p->x: " << sptr->x << std::endl;
        else
            std::cout << "'p' je neplatne" << std::endl;
    }

    // zde se uz nepodari - odkazovany shared_ptr uz nema referenci a byl smazan
    if (std::shared_ptr<Coordinates> sptr = p.lock())
        std::cout << "Uvnitr: p->x: " << sptr->x << std::endl;
    else
        std::cout << "'p' je neplatne" << std::endl;

    return 0;
}

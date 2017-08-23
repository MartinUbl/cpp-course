#include <iostream>
#include <memory>
#include <functional>

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
    Coordinates* bxx = nullptr;

    std::cout << "----------- klasicke pouziti" << std::endl;

    // scope pro prvni pokus
    {
        std::unique_ptr<Coordinates> a = std::make_unique<Coordinates>(5.5, 2.5);

        std::cout << "a->x: " << a->x << std::endl;

        // Nelze! Tohle zavani kopii, unique_ptr nelze kopirovat
        //std::unique_ptr<Coordinates> b = a;

        // Lze ale presouvat vlastnictvi mezi instancemi
        std::unique_ptr<Coordinates> b = std::move(a); // "a" je zruseno, obsah a vlastnictvi pameti je predano "b"

        std::cout << "b->x: " << b->x << std::endl;

        bxx = b.get(); // lze extrahovat pointer na danou pamet, ovsem tohle uz je na vlastni nebezpeci - muze zustat viset dangling pointer, viz dale

        std::cout << "bxx->x uvnitr: " << bxx->x << std::endl;
    }
    // s koncem scope jsou volany destruktory "a" i "b" - s "a" se nic nestane, protoze ho vyprazdnil uz std::move
    // pamet vlastnena "b" se dealokuje; dukazem budiz 

    std::cout << "bxx->x vne: " << bxx->x << std::endl;




    std::cout << "----------- vlastni deletor" << std::endl;

    // scope pro pokus s vlastnim deleterem
    {
        std::unique_ptr<Coordinates, std::function<void(Coordinates*)>> up(
            new Coordinates(1.0, 2.0),
            [](Coordinates* c) {
                std::cout << "Mazu!!" << std::endl; delete c;
            }
        );

        std::cout << "x: " << up->x << ", y: " << up->y << std::endl;
    }

    return 0;
}

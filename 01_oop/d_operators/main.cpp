#include <iostream>
#include <string>


// v C++ struct = "class, kde je vsechno public"
// Struktura klasickeho 2D vektoru roviny, ktery zname z analyticke geometrie
struct Vektor
{
    Vektor()
    {
    };

    // muze ale nemusi byt, jelikoz mame inicializator { }, viz nize
    Vektor(float _x, float _y) : x(_x), y(_y)
    {
    }

    float x;    // souradnice X
    float y;    // souradnice Y

    void print()
    {
        std::cout << "X: " << x << ", Y: " << y << std::endl;
    }

    // vysledkem operace ("volanim operatoru") muze byt Vektor
    // vektor = vektor + vektor
    Vektor operator+(const Vektor& druhy)
    {
        return Vektor{ x + druhy.x, y + druhy.y };
    }

    // vysledkem operace muze byt i "nic", pouze napr. uprava stavajiciho objektu
    // vektor += vektor
    void operator+=(const Vektor& druhy)
    {
        x += druhy.x;
        y += druhy.y;
    }

    // vysledkem operace muze byt i uplne jiny typ (zde skalarni soucin s jinym vektorem --> float)
    // float = vektor*vektor
    float operator*(const Vektor& druhy)
    {
        return x*druhy.x + y*druhy.y;
    }

    // muzeme definovat stejne operatory vickrat, jen s jinou signaturou (jine parametry)
    // vektor = vektor*float
    Vektor operator*(const float& kolikrat)
    {
        return Vektor{ x*kolikrat, y*kolikrat };
    }

    // operandem muze byt i uplne jiny typ
    // zde nasobeni (s prirazenim) vektoru skalarem - pouze dojde k uprave slozek stavajiciho objektu
    // vektor *= float
    void operator*=(const float& kolikrat)
    {
        x *= kolikrat;
        y *= kolikrat;
    }
};





// pridani operace nad jinym objektem - treba nad output streamem (viz dalsi kapitoly), pokud chceme jednoduse formatovat vystup (std::cout je instanci std::ostream)
// umozni delat: stream = stream << vektor;
//      v praxi: stream << vektor << string << vektor << ...;
std::ostream& operator<<(std::ostream& os /* leva strana */, Vektor const& v /* prava strana */)
{
    // vepise do streamu (x, y)
    os << "(" << v.x << ", " << v.y << ")";
    return os;
}

// umozni delat: vektor = vektor / float;
Vektor& operator/(const Vektor& d /* leva strana */, const float& f /* prava strana */)
{
    return Vektor{ d.x/f, d.y/f };
}






int main(int argc, char** argv)
{
    // obycejny operator +

    Vektor a(1.0f, 2.0f);
    Vektor b(5.0f, 6.0f);

    Vektor c = a + b;

    c.print();



    // compound operator +=

    Vektor d(1.0f, 1.0f);
    d += a;

    d.print();



    // jiny typ jako operand ("argument operace")

    float skalar = a*b;

    std::cout << "Skalarni soucin: " << skalar << std::endl;





    // vyuziti pridani operace nad streamem
    std::cout << "Vektor a: " << a << std::endl;
    std::cout << "Vektor d: " << d << std::endl << std::endl;



    // vyuziti pridane operace nad Vektorem definovane mimo Vektor
    Vektor g = d / 2.0f;
    std::cout << "Vektor g: " << g << std::endl;



    return 0;
}

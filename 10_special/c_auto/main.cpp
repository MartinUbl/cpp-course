#include <iostream>
#include <chrono>
#include <functional>

using namespace std::chrono_literals;


// automaticky dedukovana navratova hodnota; muze byt osemetne
auto nejakafunkce(int a)
{
    // automaticka dedukce vyhodnoti typ "double"
    auto b = 5.0 * a;

    // opet typ "double"
    return b * 5;
}



int main(int argc, char** argv)
{
    // ciselny typ - dedukce na int (ac by slo pouzit short, long, char, ..)
    auto a = 10;
    // dedukce na double; float musi byt uvozen literalem
    auto b = 10.0;
    // dedukce na float
    auto c = 15.0f;
    // dedukce na cas, opet uvozeno literalem (tentokrat sice user-defined, ale stale literal)
    auto d = 1000ms;

    // dedukce navratove hodnoty funkce; taktez funkcni, pokud neexistuje nejaka mnohoznacnost
    auto e = pow(10.0f, 15.0f);

    // u lambda funkci a std::bind je "auto" velmi uzitecne
    auto lambd = []() {
        std::cout << "Autolambda" << std::endl;
    };

    // lze dedukovat i navratovou hodnotu, opet pouze pokud je jednoznacna; implicitni konverze tomu
    // moc nepomahaji
    auto lambd2 = [&](int a, double d) {

        // tohle uz muze byt problem, jednou vracime int, jednou double; musime konvertovat explicitne
        if (a == 0)
            return a;
        else
            return (int)d;
    };
    // tento problem se netyka jen lambda funkci

    return 0;
}

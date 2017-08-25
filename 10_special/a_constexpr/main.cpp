#include <iostream>

// tohle by se vyhodnotilo normalne i bez constexpr v case kompilace - dva konstantni literaly
constexpr float magic0 = 1000.0f / 52.1f;
// tohle uz ale normalne ne - musime postouchnout kompilator klicovym slovem constexpr, aby vyhodnotil v case kompilace
constexpr float magic1 = magic0 / 258.546f - 13546.4f + 1111/321.0f;

// ne-constexpr funkce pro rekurzivni vypocet faktorialu - vola se vzdy za behu
int factorial_nonconst(const int a)
{
    return (a == 1) ? 1 : factorial_nonconst(a - 1)*a;
}

// constexpr funkce pro rekurzivni vypocet faktorialu - pokud mozno, vyhodnoti se
// v case kompilace (pokud je prirazovana do constexpr konstanty)
constexpr int factorial(const int a)
{
    return (a == 1) ? 1 : factorial(a-1)*a;
}

int main(int argc, char** argv)
{
    // jen vypis magicke konstanty vypoctene v case kompilace
    std::cout << "Magic: " << magic1 << std::endl;


    // NOTE: constexpr vyhody neimplikuji, ze rekurzivni vypocet faktorialu je v poradku
    //       - je to stale stejna prasarna, jen je to dobry ucebnicovy priklad na demonstraci
    //       jednoduchych principu, zde rekurze v constexpr funkci

    // normalni volani funkce
    int fac5_nc = factorial_nonconst(5);

    std::cout << "Fact: " << fac5_nc << std::endl;

    // prirazeni do constexpr promenne - povede se, vyhodnoti se v case kompilace
    constexpr int fac5_c = factorial(5);

    std::cout << "Fact: " << fac5_c << std::endl;

    // argument ani funkce (operator <<) neni constexpr! nevyhodnoti se v case kompilace, zavola se za behu
    std::cout << "Fact: " << factorial(5) << std::endl;

    return 0;
}

#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>

int main(int argc, char** argv)
{
    // cista scope
    {
        std::ostringstream ss;
        ss << "0x" << std::hex << 192;
        std::cout << ss.str() << std::endl;

        ss.str(""); // reinicializace streamu prazdnym stringem

        // std::hex modifier zustane! meni stav streamu jako takoveho
        ss << "0x" << 192;
        std::cout << ss.str() << std::endl;
    }



    // cista scope
    {
        std::ostringstream ss;

        // hex = hexa vystup
        // setw = ciselne vystupy maji nejmene 8 cifer
        // setfill = znak, kterym se vyplni neobsazene cifry
        // uppercase = znaky pro base > 10 budou velke

        ss << "0x" << std::hex << std::setw(8) << std::setfill('0') << std::uppercase << 253;

        std::cout << ss.str() << std::endl;
    }



    // cista scope
    {
        std::ostringstream ss;

        double d = 12.52648;

        ss << std::setprecision(3) << std::scientific << d;

        std::cout << ss.str() << std::endl;
    }



    // cista scope
    {
        std::ostringstream ss;

        ss << std::boolalpha << true << " / " << false << " ///// ";
        ss << std::noboolalpha << true << " / " << false;

        std::cout << ss.str() << std::endl;
    }

    return 0;
}

#include <iostream>
#include <exception>
#include <string>

class YouScrewedException : public std::exception
{
    public:
        YouScrewedException(int input)
        {
            m_what = std::string("Rikam kladny! Zda se ti ") + std::to_string(input) + " kladny?";
        }

        // "prepiseme" metodu what(); signatura s "throw()" rika, ze tato metoda nebude hazet vyjimku - kompilator pak reaguje jinou optimalizaci kodu, pokud je treba
        const char* what() const throw()
        {
            return m_what.c_str();
        };

    private:
        std::string m_what;
};

int BeruJenKladnaCisla(int input)
{
    if (input < 0)
        throw YouScrewedException(input);

    return -input; // whatever
}

void ExceptionCustom()
{
    try
    {
        BeruJenKladnaCisla(-9);
    }
    catch (std::exception& ex) // obecna vyjimka
    {
        std::cerr << ex.what() << std::endl;
    }
}










void Exception1()
{
    try
    {
        long long a = std::stoll("aaaa");
    }
    catch (std::invalid_argument &ex) // specificka vyjimka - hodi se pravdepodobne asi pouze kdyz chceme odchytit presne tu onu vyjimku, a ne jinou
    {
        std::cerr << "stoll: " << ex.what() << std::endl;
    }
}

void Exception2()
{
    try
    {
        long long size = 1000000000000000;
        long long* hello = new long long[size];
    }
    catch (std::exception& ex) // obecna vyjimka - hodi se kdyz potrebujeme odchytit jakoukoliv vyjimku, ale je nam fuk, co za vyjimku to je
    {
        std::cerr << "new: " << ex.what() << std::endl;
    }
}

#include <vector>

void Exception3()
{
    try
    {
        // std::vector viz nasledujici kapitoly
        std::vector<int> v;
        v.resize(5);

        std::cout << v.at(10) << std::endl;
    }
    catch (...)
    {
        std::cerr << "vector.at: Doslo k vyjimce!" << std::endl;
    }
}




// nas vycet chyb
enum class ErrorType
{
    ERR_TOO_LARGE,
    ERR_TOO_SMALL,
    ERR_OVERFLOW,
    // ...
};

void Exception4(const int input)
{
    try
    {
        if (input > 10)
            throw ErrorType::ERR_TOO_LARGE;
        else if (input < 0)
            throw ErrorType::ERR_TOO_SMALL;
        std::cout << "OK" << std::endl;
    }
    catch (ErrorType &a) // odchytavame jeden konkretni typ - ErrorType
    {
        std::cout << "Chyba: ";
        // ovsem tohle neni prilis "C++ reseni", lepsi viz Exception5
        switch (a)
        {
            case ErrorType::ERR_TOO_LARGE:
                std::cout << "Vstup je prilis velky" << std::endl;
                break;
            case ErrorType::ERR_TOO_SMALL:
                std::cout << "Vstup je prilis maly" << std::endl;
                break;
            default:
                std::cout << "neznama chyba" << std::endl;
                break;
        }
    }
}


class Err_Base {};
class Err_TooLarge : public Err_Base {};
class Err_TooSmall : public Err_Base {};
class Err_Overflow : public Err_Base {};

void Exception5(const int input)
{
    try
    {
        if (input > 10)
            throw Err_TooLarge();
        else if (input < 0)
            throw Err_TooSmall();
        else if (input == 5)
            throw Err_Overflow();
        std::cout << "OK" << std::endl;
    }
    catch (Err_TooLarge &e) // prvni vyjimka, muzeme treba chtit referenci na instanci (zde ale trochu zbytecne)
    {
        std::cout << "Chyba: Vstup je prilis velky" << std::endl;
    }
    catch (Err_TooSmall&) // nebo nemusime chtit referenci, pouze nam jde o typ (zde nasnade)
    {
        std::cout << "Chyba: Vstup je prilis maly" << std::endl;
    }
    catch (Err_Base&) // kazda jina chyba ktera dedi od Err_Base
    {
        std::cout << "Chyba: neznama chyba" << std::endl;
    }
}



void tryMethod() try
{
    BeruJenKladnaCisla(-9);
}
catch (...)
{
    std::cout << "doslo k vyjimce!" << std::endl;
}



int main(int argc, char** argv)
{
    std::cout << "----- Exception 1 - prevod na integer" << std::endl;
    Exception1();
    std::cout << "----- Exception 2 - alokace velke pameti" << std::endl;
    Exception2();
    std::cout << "----- Exception 3 - vector.at()" << std::endl;
    Exception3();
    std::cout << "----- Exception 4 - throw enum" << std::endl;
    Exception4(12);
    std::cout << "----- Exception 5 - throw empty class" << std::endl;
    Exception5(12);
    Exception5(-90);

    std::cout << "----- Exception 5 - vlastni vyjimkova trida" << std::endl;
    ExceptionCustom();


    std::cout << "----- Exception 6 - try-catch metoda" << std::endl;
    tryMethod();

    return 0;
}

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
        // zajimavosti je, ze shodou signatur je vyvolana spravna metoda "what" (z nasi tridy, ne z obecne std::exception)
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






int main(int argc, char** argv)
{
    Exception1();
    Exception2();
    Exception3();

    ExceptionCustom();

    return 0;
}

#include <iostream>
#include <string>

// puvodni implementace - specializuje se pri prekladu
template<typename T>
void printSomething(T const& value)
{
    std::cout << value << std::endl;
}

// explicitni specializace - vime, ze budeme potrebovat odlisne fungovani pro argument
// typu double - specializujeme proto funkci s timto typem
template<>
void printSomething<double>(double const& value)
{
    std::cout << "DOUBLE: " << value << std::endl;
}




template<class T>
class TemplTrida
{
    private:
        T mValue;

    public:
        TemplTrida(T value) : mValue(value)
        {
        }

        void printValue()
        {
            printSomething(mValue);
        }
};



int main(int argc, char** argv)
{
    std::cout << "--------- Zakladni pouziti" << std::endl;

    printSomething("Hello");
    printSomething(10);
    printSomething(15.555);
    printSomething<double>(5);

    std::cout << "--------- Sablonova trida" << std::endl;

    std::cout << "-- std::string template" << std::endl;

    TemplTrida<std::string> tr("Moje template trida");
    tr.printValue();

    std::cout << "-- int template" << std::endl;

    TemplTrida<int> tr2(69);
    tr2.printValue();




    // po odkomentovani nasledujiciho radku vznikne chyba - nelze specializovat
    // funkci printSomething pro tridu TemplTrida - neexistuje implementace operatoru << pro ni a std::ostream
    //printSomething(tr);

    return 0;
}

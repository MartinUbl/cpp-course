#include <iostream>
#include <sstream>
#include <string>

// ukazkovy kontejner pro data
struct MujObjekt
{
    MujObjekt() : A(0), B(0)
    {
    }

    int A, B;


    // pro moznost udelat if (mojeinstance); ukazka toho, jak to dela std::istream/std::ostream
    operator bool() const
    {
        return A && B;
    }
};

// vystupni operator << pro nas kontejner (na formatovani vystupu)
std::ostream& operator <<(std::ostream& left, MujObjekt& r)
{
    return left << r.A << ";" << r.B;
}

// vstupni operator >> pro nas kontejner (na parsovani ze vstupu)
std::istream& operator >>(std::istream& left, MujObjekt &r)
{
    char ch;
    return left >> r.A >> ch >> r.B;
}



// vlastni obal nad std::ostream
class MyOStream
{
    private:
        std::ostream& mOutStream;

    public:
        MyOStream(std::ostream& out) : mOutStream(out) { };

        // tato sablonova metoda se zvladne pri prekladu sama specializovat; sablony viz dalsi kapitoly
        template<typename T>
        MyOStream& operator<<(T& rval)
        {
            mOutStream << "'" << rval << "'" << std::endl;
            return *this;
        }
};




int main(int argc, char** argv)
{
    std::string s;

    std::cout << "----------- input stringstream" << std::endl;

    std::istringstream is("hello world how are you");
    // zakladni delimiter je mezera; operator >> zde vraci ten samy istream, jen ma pretizen operator pro pretypovani na bool
    while (is >> s)
        std::cout << s << std::endl;



    std::cout << "----------- input stringstream 2 - delimiter" << std::endl;

    std::istringstream is2("hello;world;how;are;you");
    while (std::getline(is2, s, ';'))
        std::cout << s << std::endl;


    std::cout << "----------- input stringstream 3 - nas kontejner" << std::endl;

    std::istringstream is3("13;50\n15;20");
    MujObjekt obj1, obj2;
    is3 >> obj1 >> obj2;

    std::cout << "obj1: a: " << obj1.A << ", b: " << obj1.B << std::endl;
    std::cout << "obj2: a: " << obj2.A << ", b: " << obj2.B << std::endl;




    std::cout << "----------- output stringstream" << std::endl;

    std::ostringstream os;
    os << "hello world, here's my number: " << 123456789;
    std::cout << os.str() << std::endl;


    std::cout << "----------- output stringstream 2 - nas kontejner" << std::endl;

    std::ostringstream os2;
    os2 << obj1 << std::endl << obj2;
    std::cout << os2.str() << std::endl;

    std::cout << "----------- output stringstream 3 - vlastni nadstavba a retezeni" << std::endl;

    MyOStream os3(std::cout); // zretezime se std::cout, coz je instance std::ostream
    os3 << "hello" << "world";





    std::cout << "----------- obecny stringstream" << std::endl;

    // stringstream pomoci vicenasobne dedicnosti spojuje obe tridy istringstream a ostringstream
    std::stringstream ss;
    MujObjekt novy1, novy2;
    // zapiseme uz hotovy kontejner
    ss << obj1 << std::endl;
    // zapiseme novy
    ss << "88;99" << std::endl;

    // oba je precteme do dvou novych kontejneru - poradi zustava zachovano - novy1 <- obj1, novy2 <- 88;99
    ss >> novy1 >> novy2;

    std::cout << "novy1: a: " << novy1.A << ", b: " << novy1.B << std::endl;
    std::cout << "novy2: a: " << novy2.A << ", b: " << novy2.B << std::endl;
    
    return 0;
}

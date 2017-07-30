#include <iostream>
#include <string>

//using namespace std;

class MyClass
{
    // public sekce - verejne viditelna
    public:
        // bezparametricky konstruktor
        MyClass()
        {
            std::cout << "K: -" << std::endl;
            m_something = "";
            m_somethingElse = 0;
        }

        // konstruktor s jednim parametrem
        MyClass(std::string something) : m_something(something), m_somethingElse(0)
        {
            std::cout << "K: string (" << something << ")" << std::endl;
        }

        // konstruktor se dvema parametry
        MyClass(std::string something, int somethingElse)
        {
            std::cout << "K: string (" << something << "), int (" << somethingElse << ")" << std::endl;

            m_something = something;
            m_somethingElse = somethingElse;
        }

        // !!! konstruktor se tremi parametry, ale jeden ma vychozi hodnotu - mozna viceznacnost s predchozim
        //MyClass(std::string something, int somethingElse, float anything = 0.0f)
        //{
        //    cout << "K: string, int, float" << endl;
        //}

        // copy konstruktor, neni treba explicitne definovat, pokud nemame specialni pozadavky
        MyClass(const MyClass& second) // definici copy konstruktoru se zamezi i implicitnimu chovani - kopirovani
            : m_something(second.m_something), m_somethingElse(second.m_somethingElse)
        {
            std::cout << "K: kopie (" << second.m_something << ")" << std::endl;

            // "upresneni", mohli jsme to udelat uz vyse pri inicilizaci
            m_something = second.m_something + "-kopie";
        }

        ~MyClass()
        {
            std::cout << "D: something: " << m_something << ", somethingElse: " << m_somethingElse << std::endl;
        }

        void rename(std::string something)
        {
            std::cout << "R: " << m_something << " --> " << something << std::endl;

            m_something = something;
        }

    // protected sekce - viditelna jen pro tuto tridu a jeji potomky
    protected:
        int m_somethingElse;

    // private sekce - viditelna jen pro tuto tridu
    private:
        std::string m_something;
};







void MyClassTest()
{ // implicitni scope - funkce

    MyClass a;
    MyClass b("instance B");
    MyClass c("instance C", 5);

    // po odkomentovani zakomentovaneho konstruktoru s tremi parametry kompilator rve, ze se nemuze rozhodnout mezi dvemi moznostmi
    // - definovani takoveho viceznacneho konstruktoru chyba neni; chyba vznika az v momente, kdy se musime rozhodnout, ktery z nich volat
    // - nejlepsi je ale vyhnout se takove viceznacnosti uplne, tzn. i predchazet ji lepsi definici, pojmenovanim, ..

    //MyClass d("hello", 10, 5.5f);

    MyClass e(b);
} // konec implicitni funkcni scope - zde se volaji destruktory vsech instanci (a,b,c,(d),e)

int main(int argc, char** argv)
{
    MyClassTest();

    // explicitni scope
    {
        MyClass f("instance F");
        f.rename("instance FUJ");
    } // konec scope - taktez se volaji destruktory vsech trid ve scope (f)

    return 0;
}

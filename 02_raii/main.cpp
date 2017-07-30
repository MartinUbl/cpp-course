#include <iostream>
#include <string>

// warning C4996: 'fopen': This function or variable may be unsafe. Consider using fopen_s instead. To disable deprecation, use _CRT_SECURE_NO_WARNINGS.
#pragma warning(disable:4996)

// umyslne vyuzivame C pristup k souborum, jelikoz C++ I/O uz RAII pouziva

class Soubor_NoRAII
{
    public:
        // konstruktor - zatim nic neotevira
        Soubor_NoRAII(std::string filename)
        {
            m_filename = filename;
            m_file = nullptr;
        }

        // otevrit soubor, vratit info o uspechu
        bool Open()
        {
            m_file = fopen(m_filename.c_str(), "r");

            //return m_file;
            //return m_file ? true : false;
            return (m_file != nullptr);
            //return (m_file != nullptr) ? true : false;
        }

        // precist
        std::string ReadStuff()
        {
            char buf[128];
            fgets(buf, 128, m_file);

            return buf;
        }

        // zavrit
        void Close()
        {
            if (m_file)
                fclose(m_file);
        }

    private:
        std::string m_filename;
        FILE* m_file;
};

class Soubor_RAII
{
    public:
        // RAII konstruktor - otevira soubor, "zabira prostredek"
        Soubor_RAII(std::string filename)
        {
            m_filename = filename;
            m_file = fopen(m_filename.c_str(), "r");
        }

        // RAII destruktor - zavira soubor, "uvolnuje prostredek"
        ~Soubor_RAII()
        {
            if (m_file)
                fclose(m_file);
        }

        // je soubor otevreny?
        bool IsOpen()
        {
            //return m_file;
            //return m_file ? true : false;
            return (m_file != nullptr);
            //return (m_file != nullptr) ? true : false;
        }

        // precist
        std::string ReadStuff()
        {
            char buf[128];
            fgets(buf, 128, m_file);

            return buf;
        }

    private:
        std::string m_filename;
        FILE* m_file;
};






void Test_BezRAII()
{
    Soubor_NoRAII soubor("../../02_raii/test.txt");
    if (!soubor.Open())
    {
        std::cerr << "Nelze otevrit soubor" << std::endl;
        return;
    }

    std::cout << "Obsah: " << soubor.ReadStuff() << std::endl;
    soubor.Close(); // v pripade zapomenuteho volani Close by soubor zustal stale otevreny, dokud by aplikace neskoncila
    // zde je to velmi primitivni priklad, prakticky je ale RAII velmi uzitecne
}

void Test_RAII()
{
    Soubor_RAII soubor("../../02_raii/test.txt");
    if (!soubor.IsOpen())
    {
        std::cerr << "Nelze otevrit soubor" << std::endl;
        return;
    }

    std::cout << "Obsah: " << soubor.ReadStuff() << std::endl;
    // RAII odbourava nutnost volat "Close", protoze to implicitne udela za nas destruktor
}


int main(int argc, char** argv)
{
    // 1. bez RAII
    Test_BezRAII();

    // 2. s RAII
    Test_RAII();

    return 0;
}

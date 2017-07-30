#include <iostream>
#include <string>


int main(int argc, char** argv)
{
    // konkatenace

    std::string a = "hello";
    std::string b("world");
    int cislo = 10;

    std::string c = a + " " + b + " - " + std::to_string(cislo); // pro cislo nutna explicitni konverze na string

    std::cout << c << std::endl;




    // substring

    std::string d = a.substr(1, 2);
    std::cout << d << std::endl;




    // hledani vyskytu

    size_t pos = a.find("ll", 0);
    if (pos == std::string::npos)
        std::cout << "Nenalezeno" << std::endl;
    else
        std::cout << "Nalezeno na pozici " << pos << std::endl;




    // hledani vyskytu alespon jednoho ze znaku

    std::string msg = "Tom Cruise has seaman on his back";
    std::cout << "Before: " << msg << std::endl;

    // - napriklad vsechny samohlasky transformujeme na podtrzitka
    // pro dobrou nazornost vypujceno z: http://www.cplusplus.com/reference/string/string/find_first_of/
    pos = msg.find_first_of("aeiou", 0);
    while (pos != std::string::npos)
    {
        msg[pos] = '_';
        pos = msg.find_first_of("aeiou", 0);
    }

    std::cout << "After:  " << msg << std::endl;




    // porovnavani

    const char* zprava_a = "ahoj";
    const char* zprava_b = "ahoj";
    std::string str_a(zprava_a);
    std::string str_b(zprava_b);

    // porovnavat konstantni retezcove literaly na rovnost operatorem == se nevyplaci
    // porovnavaji se totiz ve skutecnosti jejich adresy, ktere se nerovnaji takrka jiste
    // proto se pouziva strcmp, strncmp, ..
    if (zprava_a == zprava_b)
        std::cout << "zprava_a == zprava_b" << std::endl;
    else
        std::cout << "zprava_a != zprava_b" << std::endl;

    // std::string instance ale jiz takto porovnavat lze - maji pretizeny operator ==
    // takto pretizeny operator dela to, co by jinak delalo strncmp
    if (str_a == str_b)
        std::cout << "str_a == str_b" << std::endl;
    else
        std::cout << "str_a != str_b" << std::endl;

    // komparacni operator == je pretizen i pro jednu stranu std::string a druhou const char*
    if (str_a == zprava_b)
        std::cout << "str_a == zprava_b" << std::endl;
    else
        std::cout << "str_a != zprava_b" << std::endl;

    return 0;
}

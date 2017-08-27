#include <iostream>
#include <list>
#include <sstream>
#include <random>
#include <cstring>
#include <cstdio>
#include <cstdlib>

/*

Build command:

        g++ -g main.cpp -o range_c

Valgrind command:

        valgrind --tool=exp-sgcheck ./range_c

NOTE: na debianu stretch zatim rozbity SGCheck

*/

// mockovany vstup
const char* vstup =
"Antonin Novak;195;95;M\nHenrieta Nova;180;65;Z\nBartolomej Novotny;175;99;M\nTomas Novy;185;92;M\nJosef Novak;145;72;H\nAntonin Novak;190;85;N\nJan Novotny;179;84;M\n"
"Gregory Newman;157;45;M\nBartolomej Novotny;193;88;H\nJan Novotny;174;71;M";

// maximalni delka pacientova jmena
constexpr size_t MaxPacientNameLen = 18;

// enum pohlavi
enum class Pohlavi
{
    MUZ,
    ZENA,
    HERMAFRODIT,
    NEZNAME,
};

// ziska retezec reprezentujici pohlavi
const char* getPohlaviString(Pohlavi poh)
{
    switch (poh)
    {
        case Pohlavi::MUZ: return "muz";
        case Pohlavi::ZENA: return "zena";
        case Pohlavi::HERMAFRODIT: return "hermafrodit";
        case Pohlavi::NEZNAME: return "nezname";
        default: return "<chyba>";
    }
}

// struktura pacienta
struct Pacient
{
    // jmeno pacienta
    char jmeno[MaxPacientNameLen];
    // vyska pacienta
    uint16_t vyska;
    // hmotnost pacienta
    uint16_t hmotnost;
    // pohlavi pacienta
    Pohlavi pohlavi;

    // naivni porovnavaci operator ==
    bool operator==(Pacient& other)
    {
        return (vyska == other.vyska
            && hmotnost == other.hmotnost
            && pohlavi == other.pohlavi
            && strncmp(jmeno, other.jmeno, MaxPacientNameLen) == 0);
    }
};

// parsuje vstup do seznamu
void parseList(const char* inputString, std::list<Pacient> &targetList)
{
    std::istringstream is(inputString);

    std::string target, ftarget;
    // dokud je co cist
    while (std::getline(is, target))
    {
        std::istringstream linestr(target);

        Pacient pac;

        // precist jmeno
        if (!std::getline(linestr, ftarget, ';'))
            break;

        memset(pac.jmeno, 0, MaxPacientNameLen);
        strncpy(pac.jmeno, ftarget.c_str(), MaxPacientNameLen);

        // precist vysku
        if (!std::getline(linestr, ftarget, ';'))
            break;

        try
        {
            pac.vyska = std::stol(ftarget);
        }
        catch (...)
        {
            break;
        }

        // precist hmotnost
        if (!std::getline(linestr, ftarget, ';'))
            break;

        try
        {
            pac.hmotnost = std::stol(ftarget);
        }
        catch (...)
        {
            break;
        }

        // precist pohlavi
        if (!std::getline(linestr, ftarget, ';'))
            break;

        if (ftarget == "M")
            pac.pohlavi = Pohlavi::MUZ;
        else if (ftarget == "Z")
            pac.pohlavi = Pohlavi::ZENA;
        else if (ftarget == "H")
            pac.pohlavi = Pohlavi::HERMAFRODIT;
        else if (ftarget == "N")
            pac.pohlavi = Pohlavi::NEZNAME;
        else
            break;

        // vlozit do seznamu
        targetList.push_back(pac);
    }
}

std::random_device rd;
std::default_random_engine eng(rd());
std::uniform_int_distribution<int> unif_dist(1, 10);

// prida na konec pacientova jmena cislo
void resolveDuplicateNameFor(Pacient& duplicate)
{
    std::string numAdd = "-" + std::to_string(unif_dist(eng));

    char* start = duplicate.jmeno + strlen(duplicate.jmeno);
    strcpy(start, numAdd.c_str());
}

// vyhleda vsechny duplikaty a oznaci je
void resolveDuplicateNames(std::list<Pacient> &targetList)
{
    for (Pacient& pac : targetList)
    {
        for (Pacient& otherpac : targetList)
        {
            // pretizili jsme operator==, funguje
            if (pac == otherpac)
                continue;

            // pokud se shoduji jmena pacientu, ale nejde o identicky zaznam, vyresime konflikt
            if (strncmp(pac.jmeno, otherpac.jmeno, MaxPacientNameLen) == 0)
                resolveDuplicateNameFor(otherpac);
        }
    }
}

// vytiskne list pacientu
void printList(std::list<Pacient> &targetList)
{
    for (Pacient const& pac : targetList)
    {
        std::cout << "----------------------" << std::endl;

        std::cout << "Jmeno:    " << std::string(pac.jmeno, MaxPacientNameLen) << std::endl
                  << "Vyska:    " << std::to_string(pac.vyska) << "cm" << std::endl
                  << "Hmotnost: " << std::to_string(pac.hmotnost) << "kg" << std::endl
                  << "Pohlavi:  " << getPohlaviString(pac.pohlavi) << std::endl;
    }
}

int main(int argc, char** argv)
{
    std::list<Pacient> pacList;

    parseList(vstup, pacList);

    resolveDuplicateNames(pacList);

    printList(pacList);

    return 0;
}

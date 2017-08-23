#include <iostream>
#include <random>
#include <cmath>
#include <algorithm>
#include <ctime>
#include <functional>

// pocet nahodnych losovani
const size_t randomPicks = 1000;
// spodni hranice
const size_t lowBound = 1;
// horni hranice
const size_t highBound = 20;

// vymaze vektor
void clearVector(std::vector<size_t>& vect)
{
    for (size_t i = 0; i < vect.size(); i++)
        vect[i] = 0;
}

// vytiskne vektor
void printVector(std::vector<size_t>& vect)
{
    for (size_t i = 0; i < vect.size(); i++)
        std::cout << (i + lowBound) << ": " << vect[i] << std::endl;
}




int main(int argc, char** argv)
{
    // random device, obaluje pristup ke generatoru nahodnych nebo pseudonahodnych cisel
    // pokud neni k dispozici generator nahodnych (/dev/urandom, ..) sahne po pseudonahodnem
    // -- muze byt jeden na celou aplikaci, vyuziva se pouze jako zdroj seedu pro random engine
    std::random_device r;

    // inicializace generatoru (pseudo)nahodnych cisel seedem z random_device
    // tento krok nahrazuje srand(time(NULL)) z klasickeho C-pristupu
    std::default_random_engine eng(r());

    // nic nam vsak nebrani pouzit tento pristup i ted; osidime se ale o "lepsi nahodu"
    //std::default_random_engine eng(time(NULL));



    std::cout << "--------- Uniformni rozlozeni" << std::endl;

    // definice nahodneho rozlozeni nad generatorem pseudonahodnych cisel
    // z rand() by nam padaly nejake hodnoty, ale rozlozeni si musime zajistit sami.
    // tento pristup ho vyresi za nas - pri generovani bude pouzit random engine jako zdroj cisel ("rand()")
    // a vnitrni implementace zajisti pozadovane rozlozeni
    std::uniform_int_distribution<int> uniform_dist(lowBound, highBound);

    std::vector<size_t> picks;
    picks.resize(highBound - lowBound + 1);

    clearVector(picks);
    for (size_t i = 0; i < randomPicks; i++)
        picks[uniform_dist(eng) - lowBound]++;
    printVector(picks);




    std::cout << "--------- Normalni rozlozeni" << std::endl;

    // pred kazdym nezavislym pokusem bychom spravne meli reinicializovat random engine
    eng.seed(r());

    // normalni rozlozeni - vstupem je stredni hodnota a rozptyl
    std::normal_distribution<double> norm_dist((double)(highBound - lowBound + 1)/2.0, 2.0);

    clearVector(picks);
    for (size_t i = 0; i < randomPicks; i++)
    {
        double val = round(norm_dist(eng) - lowBound);
        if (val < 0 || val > (highBound - lowBound))
            continue;

        picks[(size_t)val]++;
    }
    printVector(picks);




    std::cout << "--------- Rozmichani vektoru" << std::endl;

    std::vector<size_t> a;
    a.resize(10);
    for (size_t i = 0; i < 10; i++)
        a[i] = i;

    std::cout << "Original:" << std::endl;
    printVector(a);

    // <algorithm>, viz dalsi kapitoly
    // jako argument bere random engine, ne finalni generator rozlozeni!
    std::shuffle(a.begin(), a.end(), eng);

    std::cout << "Shuffled:" << std::endl;
    printVector(a);




    std::cout << "--------- Seed generatoru" << std::endl;

    std::cout << "seed(10)" << std::endl;

    eng.seed(10);
    std::cout << uniform_dist(eng) << " " << uniform_dist(eng) << " " << uniform_dist(eng) << " " << uniform_dist(eng) << std::endl;

    std::cout << "seed(10)" << std::endl;

    eng.seed(10);
    std::cout << uniform_dist(eng) << " " << uniform_dist(eng) << " " << uniform_dist(eng) << " " << uniform_dist(eng) << std::endl;





    std::cout << "--------- Mersenne twister" << std::endl;

    // inicializace obdobna, mersenne twister je jen jiny random engine - podle jineho klice generuje hodnoty
    std::mt19937 mtwister(r());
    // zbytek je stejny

    std::uniform_int_distribution<int> unif_mt(lowBound, highBound);

    clearVector(picks);
    for (size_t i = 0; i < randomPicks; i++)
        picks[unif_mt(mtwister) - lowBound]++;
    printVector(picks);

    return 0;
}

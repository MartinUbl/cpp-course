#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <random>


std::random_device rdev;
std::default_random_engine reng(rdev());



template<typename T>
void printVectorInline(std::vector<T>& vect)
{
    for (size_t i = 0; i < vect.size(); i++)
    {
        if (i != 0)
            std::cout << ", ";
        std::cout << vect[i];
    }
    std::cout << std::endl;
}

// neefektivni implementace ziskani poctu delitelu daneho cisla
int getPocetDelitelu(int a)
{
    int counter = 0;
    for (int i = 2; i < abs(a); i++)
    {
        if (a % i == 0)
            counter++;
    }
    return counter;
}

// predikat pro razeni podle poctu delitelu; neefektivni a k nicemu radit podle tohoto kritieria, ale pro nazornost...
struct SortPredicatePocetDelitelu
{
    bool operator()(int& a, int& b)
    {
        return getPocetDelitelu(a) < getPocetDelitelu(b);
    }
};

void tiskniSlovo(std::string& str)
{
    std::cout << "SLOVO: " << str << std::endl;
}


int main(int argc, char** argv)
{
    std::cout << "--------- std::generate, std::shuffle, std::sort" << std::endl;

    // nagenerujeme nejaky vektor hodnot
    std::vector<int> toBeSorted;
    toBeSorted.resize(20);

    // generate - vygeneruje obsah podle predikatu, asi se hodi spise na sofistikovanejsi veci
    int pos = 1;
    std::generate(toBeSorted.begin(), toBeSorted.end(), [&]() { return (pos++); });

    // rozmichame - potrebujeme k tomu nejaky zdroj nahody, pouzijeme co zname z kapitoly pro nahodna cisla
    std::shuffle(toBeSorted.begin(), toBeSorted.end(), reng);

    std::cout << "Shuffled: " << std::endl;
    printVectorInline(toBeSorted);

    // seradime - implicitne se radi od nejmensiho k nejvetsimu
    std::sort(toBeSorted.begin(), toBeSorted.end());

    std::cout << "Sorted 1: " << std::endl;
    printVectorInline(toBeSorted);

    // seradime, ovsem s vlastnim predikatem pro razeni;
    // zde predikat musi byt funkce nebo funktor (s pretizenym operatorem() ), ktery bere za parametry dva prvky daneho typu
    // a vraci boolean
    std::sort(toBeSorted.begin(), toBeSorted.end(), [](int &a, int &b) { return a > b; });

    std::cout << "Sorted 2: " << std::endl;
    printVectorInline(toBeSorted);

    // predikat zde neni normalni funkce ani lambda funkce, nybrz tzv. funktor - struktura s pretizenym operatorem()
    std::sort(toBeSorted.begin(), toBeSorted.end(), SortPredicatePocetDelitelu());

    std::cout << "Sorted 3: " << std::endl;
    printVectorInline(toBeSorted);







    std::cout << "--------- std::for_each" << std::endl;

    std::vector<std::string> strVector = { "hello", "world", "how", "are", "you" };

    // for_each je sice fajn, ale malokdy nalezne svoje vyuziti oproti range-based for nebo jinemu pruchodu
    // hodi se ale vsak pri pouziti stejne funkce pro pruchod na vice mistech - setri cas a kod
    std::for_each(strVector.begin(), strVector.end(), tiskniSlovo);





    std::cout << "--------- std::next_permutation" << std::endl;

    // permutacni algoritmus se umi vyrovnat i s duplikaty
    std::string toperm = "abcc";
    // prvni permutace je vzdy ta, co vychazi ze serazene posloupnosti; kazda dalsi pouziva STEJNY radici predikat
    std::sort(toperm.begin(), toperm.end());

    do
    {
        std::cout << "Permutace: " << toperm << std::endl;
    } while (std::next_permutation(toperm.begin(), toperm.end()));




    std::cout << "--------- std::min_element, std::max_element, std::minmax_element" << std::endl;

    std::vector<int> rvect = { 5, 10, 2, 8, 35, 6, 8, 14, 13};

    // funkce vraci iteratory
    auto minitr = std::min_element(rvect.begin(), rvect.end());
    auto maxitr = std::max_element(rvect.begin(), rvect.end());

    std::cout << "min: " << *minitr << ", max: " << *maxitr << std::endl;

    // oboje v jednom
    auto minmaxpair = std::minmax_element(rvect.begin(), rvect.end());

    std::cout << "min: " << *minmaxpair.first << ", max: " << *minmaxpair.second << std::endl;





    // a mnohem vice zde: http://en.cppreference.com/w/cpp/header/algorithm
    // pouziti byva vesmes stejne nebo velmi podobne

    return 0;
}

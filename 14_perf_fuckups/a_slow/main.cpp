#include <iostream>
#include <vector>
#include <random>
#include <limits>
#include <algorithm>

/*

Build command:

        g++ -g main.cpp -o slow_a

Perf record command:

        perf record -g ./slow_a
        perf report

*/

/* konstanty */

// velikost datoveho vektoru
constexpr size_t dataCount = 10000000;
// spodni limit
constexpr int rangeMin = std::numeric_limits<int>::min();
// horni limit
constexpr int rangeMax = std::numeric_limits<int>::max();

// data nagenerovana pomoci generateData
std::vector<int> data;

// random bordel

std::random_device rd;
std::default_random_engine eng(rd());
std::uniform_int_distribution<int> unif_rand(rangeMin, rangeMax);

// nageneruje data a ulozi je do vektoru
void generateData()
{
    data.resize(dataCount);

    for (size_t i = 0; i < dataCount; i++)
        data[i] = unif_rand(eng);
}

// ziska primer hodnot
int getAverage()
{
    long sum = 0;

    for (size_t i = 0; i < dataCount; i++)
        sum += data[i];

    return (int)((long)sum / (long)dataCount);
}

// ziska median hodnot
int getMedian()
{
    std::vector<int> datacopy;
    datacopy.resize(dataCount);

    // nasledujici operace budou velmi drahe - existuje lepsi zpusob, jak ziskat median

    std::copy(data.begin(), data.end(), datacopy.begin());
    std::sort(datacopy.begin(), datacopy.end());

    if (dataCount % 2 == 0)
        return (datacopy[dataCount / 2] + datacopy[dataCount / 2 + 1]) / 2;
    else
        return datacopy[dataCount / 2];
}

// ziska pocet sudych cisel za pouziti <algorithm> funkce count_if
int getEvenCount()
{
    return std::count_if(data.begin(), data.end(), [](int el) { return (el % 2) == 0; });
}

// ziska pocet sudych cisel za pouziti vlastni implementace
int getEvenCount_Custom()
{
    size_t count = 0;

    for (size_t i = 0; i < dataCount; i++)
    {
        if (data[i] % 2 == 0)
            count++;
    }

    return count;
}

int main(int argc, char** argv)
{
    generateData();

    std::cout << "Value count:      " << dataCount << std::endl;
    std::cout << "Range min:        " << rangeMin << std::endl;
    std::cout << "Range max:        " << rangeMax << std::endl;
    std::cout << "------------------------------------" << std::endl;
    std::cout << "Average:          " << getAverage() << std::endl;
    std::cout << "Median:           " << getMedian() << std::endl;
    std::cout << "Even count:       " << getEvenCount_Custom() << std::endl;
    std::cout << "Even count (std): " << getEvenCount() << std::endl;

    return 0;
}

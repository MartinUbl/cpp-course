#include <iostream>
#include <vector>
#include <algorithm>

int main(int argc, char** argv)
{
    // jednoduchy, lehce pitomy priklad, pouze pro demonstraci vygenerovani corefile a jeho prochazeni

    size_t sz = 10;

    std::vector<int*> iptrVec;
    iptrVec.resize(sz + 1);
    std::fill(iptrVec.begin(), iptrVec.end(), nullptr);

    for (size_t i = 0; i < sz; i++)
        iptrVec[i] = new int((int)i + 1);

    for (auto& iptr : iptrVec)
    {
        std::cout << "iptr: " << *iptr << std::endl;
    }

    return 0;
}

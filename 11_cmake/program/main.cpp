#include <iostream>
#include <cstdint>
#include "general.h"
#include "../library/libinclude.h"
#include "../dynamic/dyninclude.h"

int main(int argc, char** argv)
{
    std::string sb = "hello!";

    printLine(sb);
    printPrefixedLine(sb);

    calcAndPrintMD5(sb);

    return 0;
}


#include <iostream>

#include "elepig.h"

ElePig::ElePig(Elephant& mother, Pig& father)
{
    //
}

std::string ElePig::ears()
{
    return Elephant::ears() + ", but also " + Pig::ears();
}

std::string ElePig::nose()
{
    return Elephant::nose() + ", but also " + Pig::nose();
}

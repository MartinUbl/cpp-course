#include <iostream>

#include "elephant.h"
#include "elepig.h"

Elephant::Elephant()
{
    //
}

ElePig Elephant::MakeLove(Pig& p)
{
    return p.MakeLove(*this);
}

std::string Elephant::nose()
{
    return "long and flexible";
}

std::string Elephant::ears()
{
    return "big";
}

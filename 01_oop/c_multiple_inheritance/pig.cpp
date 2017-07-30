#include <iostream>

#include "pig.h"
#include "elepig.h"

Pig::Pig()
{
    //
}

ElePig Pig::MakeLove(Elephant& e)
{
    // !!!
    //return e.MakeLove(*this);

    return ElePig(e, *this);
}

std::string Pig::nose()
{
    return "tiny";
}

std::string Pig::ears()
{
    return "pink";
}


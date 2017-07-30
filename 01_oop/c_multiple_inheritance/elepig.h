
#pragma once

#include "elephant.h"
#include "pig.h"

class ElePig : public Elephant, public Pig
{
    public:
        ElePig(Elephant& mother, Pig& father);

        virtual std::string whoAmI() override
        {
            return "elepig";
        }

        virtual std::string ears() override;
        virtual std::string nose() override;

    protected:
        //

    private:
        //
};

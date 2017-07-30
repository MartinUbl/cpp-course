
#pragma once

#include "rodic.h"

class Timmy : public Rodic
{
    public:
        // Rodic nema implicitni bezparametricky konstruktor, musime proto definovat konstruktor kvuli spravnemu
        // volani konstruktoru nadrazeneho, i kdybychom ho sami v teto tride nijak neupotrebili
        Timmy() : Rodic("Timmy")
        {
            //
        }

        // klicove slovo "override" neni povinne; jen pridava dodatecnou kontrolu, ze skutecne metoda prepisuje co potrebujeme
        // zde neni tato potreba moc znat, v komplikovanejsich projektech vsak casto muze dojit k omylu

        virtual std::string specialAbility() override
        {
            return "fast travel";
        }

        virtual std::string motto() override
        {
            return "LIVIN' A LIE, TIMMAH'!";
        }

        std::string lastName() const
        {
            return "Burch";
        };

    protected:
        //

    private:
        //
};

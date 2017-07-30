
#pragma once

class Rodic;

class Jimmy : public Rodic
{
    public:
        // Rodic nema implicitni bezparametricky konstruktor, musime proto definovat konstruktor kvuli spravnemu
        // volani konstruktoru nadrazeneho, i kdybychom ho sami v teto tride nijak neupotrebili
        Jimmy() : Rodic("Jimmy")
        {
            //
        }

        // klicove slovo "override" neni povinne; jen pridava dodatecnou kontrolu, ze skutecne metoda prepisuje co potrebujeme
        // zde neni tato potreba moc znat, v komplikovanejsich projektech vsak casto muze dojit k omylu
        
        virtual std::string specialAbility() override
        {
            return "the power of standup comedy";
        }

        virtual std::string motto() override
        {
            return "My mom says God had a plan for everyone, I guess I was plan B.";
        }

        std::string lastName() const
        {
            return "Valmer";
        };

    protected:
        //

    private:
        //
};

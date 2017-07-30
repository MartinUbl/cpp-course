
// C++ vylepseni ifndef + define + endif obalu
#pragma once

class Rodic
{
    public:
        Rodic(std::string firstName) : m_firstName(firstName)
        {
            //
        }

        // virtualni destruktor - musi byt specifikovan pro spravnou funkci "delete" nad pointerem na rodice
        virtual ~Rodic() {};

        // virtualni metoda - lze ji prepsat, ale neni to povinne
        virtual std::string specialAbility()
        {
            return "none";
        };

        // ciste virtualni metoda (pure virtual, = 0) - musi byt prepsana
        virtual std::string motto() = 0;

        // obycejna metoda; neni uvedena v tabulce virtualnich metod, protoze neni virtualni - nepodleha tedy prepisovacimu schematu
        // klicove slovo "const" rika, ze provadeni metody nemeni stav objektu
        std::string lastName() const
        {
            return "none";
        }

        // ne-virtualni metoda, const = nemeni stav objektu, pouze napr. vraci neco co je objektu vlastni
        std::string firstName() const
        {
            return m_firstName;
        }

    protected:
        //

    private:
        std::string m_firstName;
};


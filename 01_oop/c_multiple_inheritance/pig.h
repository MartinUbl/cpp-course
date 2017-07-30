
#pragma once

class Elephant;
class ElePig;

class Pig
{
    public:
        Pig();

        // virtualni destruktor pro pripad volani delete nad pointerem na rodicovskou tridu
        virtual ~Pig() {};

        ElePig MakeLove(Elephant &p);

        virtual std::string whoAmI()
        {
            return "pig";
        }

        virtual std::string nose();
        virtual std::string ears();

    protected:
        //

    private:
        //
};

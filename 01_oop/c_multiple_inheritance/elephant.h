
#pragma once

class Pig;
class ElePig;

class Elephant
{
    public:
        Elephant();

        // virtualni destruktor pro pripad volani delete nad pointerem na rodicovskou tridu
        virtual ~Elephant() {};

        ElePig MakeLove(Pig &p);

        virtual std::string whoAmI()
        {
            return "elephant";
        }

        virtual std::string nose();
        virtual std::string ears();

    protected:
        //

    private:
        //
};


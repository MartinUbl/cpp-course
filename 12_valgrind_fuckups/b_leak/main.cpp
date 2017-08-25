#include <iostream>
#include <memory>
#include <cstring>
#include <cstdio>

/*

Build command:

        g++ -g main.cpp -o leak_b

Valgrind command:

        valgrind --tool=memcheck --leak-check=full ./leak_b

*/


class StringMod
{
    public:
        StringMod(const char* input)
        {
            mStr = new char[strlen(input) + 1];
            strcpy(mStr, input);
        }

        ~StringMod()
        {
            delete[] mStr;
        }

        virtual void Modify() = 0;

        friend std::ostream& operator<<(std::ostream& stream, StringMod& me)
        {
            return stream << me.mStr << me.suffixStr();
        }

    protected:
        char* mStr;

        virtual const char* suffixStr() { return ""; };
};



class Vypatlator : public StringMod
{
    public:
        Vypatlator(const char* input) : StringMod(input)
        {
            mDodatek = nullptr;
        }

        ~Vypatlator()
        {
            if (mDodatek)
                delete[] mDodatek;
        }

        virtual void Modify() override
        {
            size_t spaceCounter = 0;

            for (size_t i = 0; i < strlen(mStr); i++)
            {
                switch (mStr[i])
                {
                    case ' ':
                    {
                        if (spaceCounter % 2 == 1)
                            mStr[i] = '_';
                        spaceCounter++;
                        break;
                    }
                    case 'k':
                        mStr[i] = 'Q';
                        break;
                }
            }

            if (mDodatek)
                delete mDodatek;

            const char* dodatek;
            switch (strlen(mStr) % 3)
            {
                case 0:
                    dodatek = " *muck*";
                    break;
                case 1:
                    dodatek = " O_o";
                    break;
                case 2:
                    dodatek = " ^_^";
                    break;
            }

            mDodatek = new char[strlen(dodatek) + 1];
            strcpy(mDodatek, dodatek);
        }

    protected:
        char* mDodatek;

        virtual const char* suffixStr() override
        {
            return mDodatek ? mDodatek : "";
        }
};







int main(int argc, char** argv)
{
    StringMod* v = new Vypatlator("ahojky popismenkujes si se mnou?");

    std::cout << "Pred vypatlanim:  " << *v << std::endl;
    v->Modify();
    std::cout << "Po vypatlani:     " << *v << std::endl;

    return 0;
}

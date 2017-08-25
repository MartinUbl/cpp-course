#include <iostream>
#include <cstring>
#include <cstdlib>

/*

Build command:

        g++ -g main.cpp -o leak_a

Valgrind command:

        valgrind --tool=memcheck --leak-check=full ./leak_a

*/

/*
 * Trida ktera rozdeli vstupni retezec na jednotliva slova
 * Umyslne neefektivni a nemoderni implementace stylem "C s objekty"
 * Skolsky priklad
 */
class Splitter
{
    public:
        // konstruktor rozdeli retezec a ulozi slova do pole uvnitr
        Splitter(const char* input)
        {
            mWordCount = 1; // zaklad je vzdy 1 slovo, byt prazdne
            for (size_t i = 0; i < strlen(input); i++)
            {
                if (input[i] == ' ')
                    mWordCount++;
            }

            // alokujeme prostor pro slova
            mWords = new char*[mWordCount];

            // a parsujeme
            size_t wordIdx = 0;
            size_t lastSpace = (size_t)-1; // trochu zneuzijeme vlastnosti bezznaminkove aritmetiky, kdy unsigned -1 po pricteni 1 da 0 vzdy a vsude
            for (size_t i = 0; i <= strlen(input); i++) // rovnitko v podmince umyslne, abychom nemuseli vyrabet specialni kus kodu za cyklus
            {
                if (i == strlen(input) || input[i] == ' ')
                {
                    mWords[wordIdx] = new char[i - lastSpace + 1 + 1];
                    strncpy(mWords[wordIdx], input + lastSpace + 1, i - lastSpace);
                    mWords[wordIdx][i - lastSpace - 1] = '\0';

                    wordIdx++;
                    lastSpace = i;
                }
            }
        }

        ~Splitter()
        {
            // smazeme pole se slovy
            delete[] mWords;
        }

        void print()
        {
            // vytiskneme kazde slovo na novou radku
            for (size_t i = 0; i < mWordCount; i++)
                std::cout << "Slovo[" << i << "]: " << mWords[i] << std::endl;
        }

    private:
        // pocet slov vzniklych rozdelenim vstupniho retezce
        size_t mWordCount;
        // pole slov
        char** mWords;
};





int main(int argc, char** argv)
{
    Splitter spl("hello world how is it going");
    spl.print();

    return 0;
}

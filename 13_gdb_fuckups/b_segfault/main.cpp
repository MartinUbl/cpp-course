#include <iostream>
#include <memory>

class TestRunner
{
    public:
        TestRunner(int a = 100) : mParam(a) {};

        void printParam()
        {
            std::cout << "Parametr: ";
            _printParam();
        }

    private:
        int mParam;

        void _printParam()
        {
            std::cout << mParam << std::endl;;
        }
};

int main(int argc, char** argv)
{
    std::unique_ptr<TestRunner> ppp;

    ppp->printParam();

    return 0;
}

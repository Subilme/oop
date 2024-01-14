//Работа с контейнером vector(1)

#include "Utils.h"
#include <iomanip>

int main()
{
    std::vector<double> numbers;
    double value;
    while (std::cin >> value)
    {
        numbers.push_back(value);
    }
    
    DivideByHalfMax(numbers);

    Print(std::cout, numbers);

    return 0;
}
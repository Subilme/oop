#include "Utils.h"
#include <algorithm>
#include <iomanip>

void DivideByHalfMax(std::vector<double>& numbers)
{
    if (!numbers.size())
    {
        return;
    }

    double max = *std::max_element(numbers.begin(), numbers.end());

    std::transform(numbers.begin(), numbers.end(), numbers.begin(), [max](double value) { return value * 2 / max; });
    std::sort(numbers.begin(), numbers.end());
}

void Print(std::ostream& output, std::vector<double>& numbers)
{
    for (auto val : numbers)
    {
        std::cout << std::fixed << std::setprecision(3) << val << " ";
    }
    std::cout << std::endl;
}
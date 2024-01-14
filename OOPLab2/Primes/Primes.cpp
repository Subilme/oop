//Работа с контейнером set(4)

#include <iostream>
#include "PrimesUtils.h"

std::string ParseArgs(int argc, char* argv[])
{
    if (argc != 2)
    {
        return "";
    }
    return argv[1];
}

int main(int argc, char* argv[])
{
    std::string arg = ParseArgs(argc, argv);

    if (arg.empty())
    {
        throw std::invalid_argument("Invalid number.");
    }
    int n = std::stoi(arg);

    Print(std::cout, GeneratePrimeNumbersSet(n));

    return 0;
}

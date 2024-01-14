#include <vector>
#include <iostream>
#include "PrimesUtils.h"

std::set<int> GeneratePrimeNumbersSet(const int upperBound)
{
    if (upperBound < 2)
    {
        return {};
    }
    //sieving изменить +
    std::vector<bool> isPrime(upperBound + 1, true);

    for (int i = 2; i * i <= upperBound; i++)
    {
        if (isPrime[i])
        {
            for (int j = i * i; j <= upperBound; j += i)
            {
                isPrime[j] = false;
            }
        }
    }

    std::set<int> primes;
    for (int i = 2; i <= upperBound; i++)
    {
        if (isPrime[i])
        {
            primes.insert(i);
        }
    }

    return primes;
}
//Исправить функцию +
void Print(std::ostream& output, const std::set<int>& primes)
{
    for (auto value : primes)
    {
        output << value << " ";
    }
    output << std::endl;
}

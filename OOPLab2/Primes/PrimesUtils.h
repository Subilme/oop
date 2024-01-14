#pragma once
#include <string>
#include <set>

std::set<int> GeneratePrimeNumbersSet(int upperBound);
void Print(std::ostream& output, const std::set<int>& primes);

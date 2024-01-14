#define CATCH_CONFIG_MAIN
#include <iostream>
#include "..\..\catch2\catch.hpp"
#include "..\Primes\PrimesUtils.h"

SCENARIO("Testing limit values")
{
	REQUIRE(GeneratePrimeNumbersSet(-21).empty());
	REQUIRE(GeneratePrimeNumbersSet(0).empty());
	REQUIRE(GeneratePrimeNumbersSet(1).empty());
	REQUIRE(GeneratePrimeNumbersSet(2) == std::set<int>{2});
	REQUIRE(GeneratePrimeNumbersSet(100000000).size() == 5761455);
}

SCENARIO("Tesing random values")
{
	REQUIRE(GeneratePrimeNumbersSet(19) == std::set<int>{2, 3, 5, 7, 11, 13, 17, 19});
	REQUIRE(GeneratePrimeNumbersSet(36) == std::set<int>{2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31});
	REQUIRE(GeneratePrimeNumbersSet(100).size() == 25);
	REQUIRE(GeneratePrimeNumbersSet(1000).size() == 168);
}

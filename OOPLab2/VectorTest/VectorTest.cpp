#define CATCH_CONFIG_MAIN
#include <algorithm>
#include "..\..\catch2\catch.hpp"
#include "..\vector\Utils.h"

SCENARIO("Testing normal vector")
{
	std::vector<double> v = { 5, 54, 1, 2.3, 1, -45.68 };
	std::vector<double> expected = { -1.69185, 0.037037, 0.037037, 0.0851852, 0.185185, 2 };
	DivideByHalfMax(v);
	REQUIRE(equal(v.begin(), v.end(), expected.begin(), [](double a, double b) { return static_cast<int>(a - b) == 0; }));
}

SCENARIO("Testing sorted vector")
{
	std::vector<double> v = { 1, 2, 3, 4, 5, 6 };
	std::vector<double> expected = { 0.333333, 0.666667, 1, 1.33333, 1.66667, 2 };
	DivideByHalfMax(v);
	REQUIRE(equal(v.begin(), v.end(), expected.begin(), [](double a, double b) { return static_cast<int>(a - b) == 0; }));
}

SCENARIO("Testing reverse sorted vector")
{
	std::vector<double> v = { 6, 5, 4, 3, 2, 1 };
	std::vector<double> expected = { 0.333333, 0.666667, 1, 1.33333, 1.66667, 2 };
	DivideByHalfMax(v);
	REQUIRE(equal(v.begin(), v.end(), expected.begin(), [](double a, double b) { return static_cast<int>(a - b) == 0; }));
	//TODO: числа с плавающей точкой нужно сравнивать через диапазон остатка
}

SCENARIO("Testing empty vector")
{
	std::vector<double> v = {};
	std::vector<double> expected = {};
	DivideByHalfMax(v);
	REQUIRE(equal(v.begin(), v.end(), expected.begin(), [](double a, double b) { return static_cast<int>(a - b) == 0; }));
}
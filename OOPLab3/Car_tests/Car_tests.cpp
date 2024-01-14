#define CATCH_CONFIG_MAIN
#include "../../catch2/catch.hpp"
#include "../Car/CCar.h"

TEST_CASE("Checking Car's initial state and engine behavior")
{
	CCar car;

	SECTION("Check initial state of car: engine is off, speed 0, gear neutral, direction immobile")
	{
		REQUIRE(!car.IsTurnedOn());
		REQUIRE(car.GetGear() == 0);
		REQUIRE(car.GetSpeed() == 0);
		REQUIRE(car.GetDirection() == CCar::Direction::None);
	}

	SECTION("Turning off engine which already stopped")
	{
		REQUIRE(!car.IsTurnedOn());
		REQUIRE(car.TurnOffEngine());
	}

	SECTION("Turning on engine which already running")
	{
		REQUIRE(car.TurnOnEngine());
		REQUIRE(car.IsTurnedOn());
		REQUIRE(car.TurnOnEngine());
	}
}

TEST_CASE("Checking Car's gear manipulations")
{
	CCar car;

	SECTION("Trying set gear and speed while engine is off")
	{
		REQUIRE(!car.IsTurnedOn());
		REQUIRE(!car.SetGear(1));
		REQUIRE(car.GetGear() == 0);
		REQUIRE(!car.SetSpeed(10));
		REQUIRE(car.GetSpeed() == 0);
		REQUIRE(car.GetDirection() == CCar::Direction::None);
	}

	SECTION("Trying set gear with out of range values")
	{
		REQUIRE(car.TurnOnEngine());
		REQUIRE(car.IsTurnedOn());
		REQUIRE(!car.SetGear(-2));
		REQUIRE(car.GetGear() == 0);
		REQUIRE(!car.SetGear(6));
		REQUIRE(car.GetGear() == 0);
	}

	SECTION("Trying set gear while moving at wrong speed range")
	{
		REQUIRE(car.TurnOnEngine());
		REQUIRE(car.SetGear(1));
		REQUIRE(car.SetSpeed(10));

		REQUIRE(!car.SetGear(-1));
		REQUIRE(car.GetGear() == 1);
		REQUIRE(!car.SetGear(2));
		REQUIRE(car.GetGear() == 1);
		REQUIRE(!car.SetGear(3));
		REQUIRE(car.GetGear() == 1);
		REQUIRE(!car.SetGear(4));
		REQUIRE(car.GetGear() == 1);
		REQUIRE(!car.SetGear(5));
		REQUIRE(car.GetGear() == 1);

		REQUIRE(car.SetSpeed(30));
		REQUIRE(car.SetGear(2));

		REQUIRE(!car.SetGear(-1));
		REQUIRE(car.GetGear() == 2);
		REQUIRE(!car.SetGear(5));
		REQUIRE(car.GetGear() == 2);

		REQUIRE(car.SetGear(0));
		REQUIRE(car.SetSpeed(0));
		REQUIRE(car.SetGear(-1));
		REQUIRE(car.SetSpeed(15));

		REQUIRE(!car.SetGear(1));
		REQUIRE(car.GetGear() == -1);

		REQUIRE(car.SetGear(0));
		REQUIRE(!car.SetGear(-1));
		REQUIRE(car.GetGear() == 0);
	}
}

TEST_CASE("Checking Car's speed manipulations")
{
	CCar car;

	SECTION("Trying set speed out of range of current gear speed range")
	{
		REQUIRE(car.TurnOnEngine());
		REQUIRE(car.SetGear(1));

		// gear 1
		REQUIRE(!car.SetSpeed(47));
		REQUIRE(!car.SetSpeed(-45));

		REQUIRE(car.SetSpeed(20));
		REQUIRE(car.SetGear(2));

		// gear 2
		REQUIRE(!car.SetSpeed(19));
		REQUIRE(!car.SetSpeed(51));

		REQUIRE(car.SetSpeed(40));
		REQUIRE(car.SetGear(3));

		// gear 3
		REQUIRE(!car.SetSpeed(29));
		REQUIRE(!car.SetSpeed(61));

		REQUIRE(car.SetSpeed(55));
		REQUIRE(car.SetGear(4));

		// gear 4
		REQUIRE(!car.SetSpeed(39));
		REQUIRE(!car.SetSpeed(91));

		REQUIRE(car.SetSpeed(85));
		REQUIRE(car.SetGear(5));

		// gear 5
		REQUIRE(!car.SetSpeed(49));
		REQUIRE(!car.SetSpeed(151));
	}

	SECTION("Trying accelerate at neutral gear")
	{
		REQUIRE(car.TurnOnEngine());
		REQUIRE(car.SetGear(1));

		REQUIRE(car.SetSpeed(30));
		REQUIRE(car.SetGear(0));
		REQUIRE(car.SetSpeed(15));
		REQUIRE(!car.SetSpeed(25));

		REQUIRE(car.SetSpeed(0));
		REQUIRE(car.SetGear(-1));
	
		REQUIRE(car.SetSpeed(20));
		REQUIRE(car.SetGear(0));
		REQUIRE(car.SetSpeed(15));
		REQUIRE(!car.SetSpeed(18));
	}
}

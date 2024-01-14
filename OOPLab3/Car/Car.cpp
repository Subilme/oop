#include <iostream>
#include <string>
#include "CCar.h"

void Info(CCar& car, std::ostream& output)
{
    std::string direction;
    switch (car.GetDirection())
    {
        case (CCar::Direction::Forward):
            direction = "forward";
            break;
        case (CCar::Direction::Backward):
            direction = "backward";
            break;
        case (CCar::Direction::None):
            direction = "None";
            break;
    }
    output << "Engine: " << (car.IsTurnedOn() ? "on" : "off") << std::endl
        << "Direction: " << direction << std::endl
        << "Speed: " << std::to_string(car.GetSpeed()) << std::endl
        << "Gear: " << std::to_string(car.GetGear()) << std::endl;
}

void EngineOn(CCar& car, std::ostream& output)
{
    if (car.TurnOnEngine())
    {
        output << "Engine is turned on" << std::endl;
    }
    else
    {
        output << "Error on turning on the engine" << std::endl;
    }
}

void EngineOff(CCar& car, std::ostream& output)
{
    if (car.TurnOffEngine())
    {
        output << "Engine is turned off" << std::endl;
    }
    else
    {
        output << "Error on turning off the engine" << std::endl;
    }
}

void SetGear(CCar& car, std::istream& input, std::ostream& output)
{
    int gear = 0;
    input >> gear;
    if (car.SetGear(gear))
    {
        output << "Gear succesfully changed" << std::endl;
    }
    else
    {
        output << "Error on changing the gear" << std::endl;
    }
}

void SetSpeed(CCar& car, std::istream& input, std::ostream& output)
{
    int speed = 0;
    input >> speed;
    if (car.SetSpeed(speed))
    {
        output << "Speed succesfully changed" << std::endl;
    }
    else
    {
        output << "Error on changing the speed" << std::endl;
    }
}

void Help(std::ostream& output)
{
    output << "Info - get info about the car" << std::endl
        << "EngineOn - turn on the engine" << std::endl
        << "EngineOff - turn off the engine" << std::endl
        << "SetGear <gear> - set the gear" << std::endl
        << "SetSpeed <speed> - set the speed" << std::endl
        << "Exit - exit the app" << std::endl;
 }

void ProcessCommand(CCar& car, const std::string& command, std::istream& input, std::ostream& output)
{
    if (command == "Info")
    {
        Info(car, std::cout);
    }
    else if (command == "EngineOn")
    {
        EngineOn(car, std::cout);
    }
    else if (command == "EngineOff")
    {
        EngineOff(car, std::cout);
    }
    else if (command == "SetGear")
    {
        SetGear(car, std::cin, std::cout);
    }
    else if (command == "SetSpeed")
    {
        SetSpeed(car, std::cin, std::cout);
    }
    else if (command == "Help")
    {
        Help(std::cout);
    }
    else
    {
        output << "Unknown command" << std::endl;
    }
}

int main()
{
    CCar car;
    
    while (true)
    {
        std::string command;
        std::cin >> command;

        if (command == "Exit")
        {
            return 0;
        }
        ProcessCommand(car, command, std::cin, std::cout);
    }

    return 0;
}

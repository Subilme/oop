#include "DataProcessor.h"
#include <iostream>
#include <vector>

//class Animal
//{
//public:
//	virtual void Say() = 0;
//};
//
//class Dog : public Animal
//{
//public:
//	void Say() override
//	{
//		std::cout << "gav-gav " << name << std::endl;
//	}
//	std::string name;
//};
//
//class Cat : public Animal
//{
//public:
//	void Say() override
//	{
//		std::cout << "meow" << std::endl;
//	}
//};

int main()
{
	/*Dog dog;
	Cat cat;
	std::vector<Animal*> animals;
	animals.push_back(&dog);
	animals.push_back(&cat);

	dog.name = "sharik";
	for (Animal* animal : animals)
	{
		(*animal).Say();
	}*/

	DataProcessor dataProcessor;

	if (!dataProcessor.ReadShapeData(std::cin))
	{
		std::cout << "Failed to read data" << std::endl;
		return 1;
	}

	std::cout << "Max Area Shape" << std::endl;
	dataProcessor.PrintMaxAreaShapeInfo(std::cout);
	std::cout << "Min Perimeter Shape" << std::endl;
	dataProcessor.PrintMinPerimeterShapeInfo(std::cout);

	return 0;
}

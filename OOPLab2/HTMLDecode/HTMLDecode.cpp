#include <iostream>
#include "DecodeFunctions.h"

int main()
{
	std::string inputStr;

	while (std::getline(std::cin, inputStr))
	{
		std::cout << HtmlDecode(inputStr) << '\n';
	}

	return 0;
}

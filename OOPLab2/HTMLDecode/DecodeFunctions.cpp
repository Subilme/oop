#include "DecodeFunctions.h"
#include <map>

const std::map<std::string, char> decodeMap = {
	{ "&lt;", '<' },
	{ "&gt;", '>' },
	{ "&amp;", '&' },
	{ "&apos;", '\'' },
	{ "&quot;", '"' }
};

// TODO: ћожно использовать std::equal, либо compare у строки
bool CompareWithEntity(const std::string::const_iterator& first, const std::string::const_iterator& end, const std::string& entityCode)
{
	char i = 0;
	for (const char ch : entityCode)
	{
		if ((first + i) == end || ch != *(first + i))
		{
			return false;
		}
		++i;
	}

	return true;
}

// TODO: итераторы принимать по значению
char DecodeNextChar(std::string::const_iterator& first, const std::string::const_iterator& end)
{
	for (const auto& [entityCode, ch] : decodeMap)
	{
		if (CompareWithEntity(first, end, entityCode))
		{
			// TODO: –азобратьс€ с -1
			std::advance(first, entityCode.length() - 1);
			return ch;
		}
	}

	return *first;
}

std::string HtmlDecode(const std::string& html)
{
	std::string decodedStr;
	std::string::const_iterator iterator = html.begin();

	while (iterator != html.end())
	{
		decodedStr.push_back(DecodeNextChar(iterator, html.end()));
		++iterator;
	}

	return decodedStr;
}

#include <iostream>
#include <string>
#include <cmath>

using namespace std;

int GetDigitValue(char digit, bool& notFound)
{
	notFound = false;
	if (digit <= '9' && digit >= '0')
	{
		return digit - '0';
	}
	if (digit <= 'Z' && digit >= 'A')
	{
		return digit - 'A' + 10;
	}
	notFound = true;
	return 0;
}

char GetDigitChar(int value, bool& notFound)
{
	notFound = false;
	if (value < 10 && value > 0)
	{
		return value + '0';
	}
	if (value < 36 && value > 11)
	{
		return value + 'A' - 10;
	}
	notFound = true;
	return -1;
}

int StringToInt(const string& str, int radix, bool& wasError)
{
	int result = 0;
	int numeralSystemMultiplier = 1;
	bool digitNotFound = false;
	for (int i = 0; i < str.length(); i++)
	{
		
		int digitValue = GetDigitValue(str[str.length() - i - 1], digitNotFound);
		if (digitNotFound || digitValue >= radix)
		{
			wasError = true;
			return 0;
		}
		result += digitValue * numeralSystemMultiplier;
		numeralSystemMultiplier *= radix;
	}
	wasError = false;
	return result;
}

string IntToString(int n, int radix, bool& wasError)
{
	string expression;
	bool digitNotFound = false;
	while (n > 0)
	{
		int value = n % radix;
		n = n / radix;
		char digit = GetDigitChar(value, digitNotFound);
		if (digitNotFound)
		{
			wasError = true;
			return "";
		}
		expression += digit;
	}
	string result;
	for (int i = expression.length() - 1; i >= 0; i--)
	{
		result += expression[i];
	}
	wasError = false;
	return result;
}

int main(int argc, char* argv[])
{
	if (argc != 4)
	{
		cout << "Wrong number of arguments" << endl;
		cout << "Expected radix.exe [source notation] [destination notation] [expression]" << endl;
		return 1;
	}
	bool error = true;
	int sourceNotation = StringToInt(argv[1], 10, error);
	if (error)
	{
		cout << "Incorrect input" << endl;
		return 1;
	}
	int destinationNotation = StringToInt(argv[2], 10, error);
	if (error)
	{
		cout << "Incorrect input" << endl;
		return 1;
	}

	int decimalValue = StringToInt(argv[3], sourceNotation, error);
	if (error)
	{
		cout << "Incorrect input" << endl;
		return 1;
	}

	string destinationValue = IntToString(decimalValue, destinationNotation, error);
	if (error)
	{
		cout << "Calculation error" << endl;
		return 1;
	}

	cout << destinationValue << endl;
	return 0;
}
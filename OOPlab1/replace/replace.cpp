#include <fstream>
#include <iostream>
#include <string>

using namespace std;

bool IsStringStartsWith(const string& stringToCheck, const string& possibleStart)
{
	if (stringToCheck.length() < possibleStart.length())
	{
		return false;
	}
	for (size_t i = 0; i < possibleStart.length(); i++)
	{
		if (stringToCheck[i] != possibleStart[i])
		{
			return false;
		}
		if ((i + 1) == possibleStart.length())
		{
			return true;
		}
	}
	return false;
}

void Replace(fstream& input, fstream& output, const string& searchString, const string& replaceString)
{
	string buffer;
	string line;

	while (getline(input, line))
	{
		for (size_t pos = 0; pos < line.length(); pos++)
		{
			buffer += line[pos];
			if (IsStringStartsWith(searchString, buffer))
			{
				if (searchString.length() == buffer.length())
				{
					buffer = "";
					output << replaceString;
				}
			}
			else
			{
				while ((!IsStringStartsWith(searchString, buffer)) && (buffer.length() != 0))
				{
					output << buffer[0];
					buffer = buffer.substr(1, buffer.length() - 1);
				}
			}
		}
		output << buffer << endl;
		buffer = "";
	}
}

int main(int argc, char* argv[])
{
	if (argc != 5)
	{
		cerr << "Invalid argument count" << endl;
		cerr << "Expected replace.exe [input file] [output file] [search string] [replace string]" << endl;
		return 1;
	}
	//Выделить функции

	string inputFileName = argv[1];
	fstream inFile;
	inFile.open(inputFileName, ios_base::in);
	if (!inFile.is_open())
	{
		cerr << "Error on opening file" << endl;
		return 1;
	}

	string outputFileName = argv[2];
	fstream outFile;
	outFile.open(outputFileName, ios_base::out);

	string searchString = argv[3];
	string replaceString = argv[4];

	Replace(inFile, outFile, searchString, replaceString);

	inFile.close();
	outFile.close();
	return 0;
}
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

enum Mode
{
	Pack,
	Unpack
};

struct CommandLineArguments
{
	Mode mode;
	string inFileName;//Name
	string outFileName;//Name
};

struct RleChunk
{
	int counter;
	int symbol;
};

CommandLineArguments ParseArgs(int argc, char* argv[], bool& success)
{
	CommandLineArguments args;
	if (argc != 4)
	{
		success = false;
		return args;
	}
	string modeString = argv[1];
	if (modeString == "pack")
	{
		args.mode = Mode::Pack;
	}
	else if (modeString == "unpack")
	{
		args.mode = Mode::Unpack;
	}
	else
	{
		success = false;
		return args;
	}
	args.inFileName = argv[2];
	args.outFileName = argv[3];
	success = true;

	return args;
}

bool ReadChunk(RleChunk& chunk, fstream& input)
{
	chunk.counter = input.get();
	chunk.symbol = input.get();
	return (chunk.symbol != EOF && chunk.counter != EOF);
}

string UnpackChunk(const RleChunk& chunk)
{
	string unpackedChunk;
	for (int j = 0; j < chunk.counter; j++)
	{
		unpackedChunk += (char)chunk.symbol;
	}
	return unpackedChunk;
}

void PrintChunk(const RleChunk& chunk, fstream& output)
{
	output.put((char)chunk.counter);
	output.put((char)chunk.symbol);
}

bool PackFile(const string& inputFileName, const string& outputFileName)
{
	fstream input;
	input.open(inputFileName, ios_base::in | ios_base::binary);
	if (!input.is_open())
	{
		return false;
	}

	fstream output;
	output.open(outputFileName, ios_base::out | ios_base::binary);
	if(!output.is_open())
	{
		return false;
	}

	int inputSymbol = input.get();
	RleChunk chunk;
	chunk.counter = 0;
	while (inputSymbol != EOF)
	{
		if (chunk.counter == 0)
		{
			chunk.symbol = inputSymbol;
			chunk.counter = 1;
		}
		else
		{
			if (inputSymbol == chunk.symbol)
			{
				chunk.counter++;
				if (chunk.counter == 255)
				{
					PrintChunk(chunk, output);
					chunk.counter = 0;
				}
			}
			else
			{
				PrintChunk(chunk, output);
				chunk.symbol = inputSymbol;
				chunk.counter = 1;
			}
		}
		inputSymbol = input.get();
	}
	if (chunk.counter != 0)
	{
		PrintChunk(chunk, output);
	}
	return true;
}

bool UnpackFile(const string& inputFileName, const string& outputFileName)
{
	fstream input;
	input.open(inputFileName, ios_base::in | ios_base::binary);
	if (!input.is_open())
	{
		return false;
	}

	fstream output;
	output.open(outputFileName, ios_base::out | ios_base::binary);

	RleChunk chunk;
	bool chunkSuccessfullyRead = ReadChunk(chunk, input);
	while (chunkSuccessfullyRead)
	{
		string unpackedChunk = UnpackChunk(chunk);
		output << unpackedChunk;
		chunkSuccessfullyRead = ReadChunk(chunk, input);
	}

	return true;
}

int main(int argc, char* argv[])
{
	bool success = false;
	CommandLineArguments args = ParseArgs(argc, argv, success);

	if (!success)
	{
		cout << "Incorrect arguments" << endl;
		cout << "Expected rle.exe [pack || unpack] [input file] [output file]" << endl;
		return 1;
	}

	if (args.mode == Mode::Pack)
	{
		success = PackFile(args.inFileName, args.outFileName);
	}
	else
	{
		success = UnpackFile(args.inFileName, args.outFileName);
	}

	if (!success)
	{
		cout << "Error on processing file" << endl;
		return 1;
	}

	return 0;
}
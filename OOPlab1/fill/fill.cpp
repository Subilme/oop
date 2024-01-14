#include <fstream>
#include <iostream>
#include <string>
#include <queue>

using namespace std;

const int MAX_FIELD_SIZE = 100;
const char EMPTY_SYMBOL = ' ';
const char FILL_SYMBOL = '.';
const char BORDER_SYMBOL = '#';
const char START_SYMBOL = 'O';

// +2 для окантовки массива
using Field = char[MAX_FIELD_SIZE + 2][MAX_FIELD_SIZE + 2];

struct CommandLineArguments
{
	string inputFileName;
	string outputFileName;
};

//Изменить
struct StartCoords
{
	Field field;
	queue<pair<int, int>> startCoordsQueue;
};

CommandLineArguments ParseArguments(int argc, char* argv[], bool& success)
{
	CommandLineArguments args;
	if (argc != 3)
	{
		success = false;
	}
	else
	{
		args.inputFileName = argv[1];
		args.outputFileName = argv[2];
		success = true;
	}
	return args;
}

void InitField(Field& field)
{
	// Заполнение массива пустыми символами
	for (int i = 1; i <= MAX_FIELD_SIZE; i++)
	{
		for (int j = 1; j <= MAX_FIELD_SIZE; j++)
		{
			field[i][j] = EMPTY_SYMBOL;
		}
	}

	// Окантовка массива
	for (int i = 0; i < MAX_FIELD_SIZE + 2; i++)
	{
		field[i][0] = BORDER_SYMBOL;
		field[i][MAX_FIELD_SIZE + 1] = BORDER_SYMBOL;
	}
	for (int i = 0; i < MAX_FIELD_SIZE + 2; i++)
	{
		field[0][i] = BORDER_SYMBOL;
		field[MAX_FIELD_SIZE + 1][i] = BORDER_SYMBOL;
	}
}

//Разделить функцию
StartCoords FindStartCoordinates(
	const string& inputFileName, bool& success)
{
	success = true;
	StartCoords startCoords;
	fstream input;
	input.open(inputFileName, ios_base::in);
	if (!input.is_open())
	{
		success = false;
		return startCoords;
	}

	InitField(startCoords.field);

	string line;
	int lineCounter = 1;
	while (getline(input, line))
	{
		for (int columnCounter = 1; columnCounter <= line.length(); columnCounter++)
		{
			startCoords.field[lineCounter][columnCounter] = line[columnCounter];
			if (line[columnCounter] == START_SYMBOL)
			{
				startCoords.startCoordsQueue
					.push(make_pair(lineCounter, columnCounter));
			}
		}
		lineCounter++;
	}

	return startCoords;
}

void StartCoordsPair(Field& field, int x, int y)
{
	const int DIRECTIONS_COUNT = 4;
	const pair<int, int> DIRECTIONS[] = { { 1, 0 }, { -1, 0 }, { 0, 1 }, { 0, -1 } };

	queue<pair<int, int>> coordinatesQueue;
	coordinatesQueue.push(make_pair(x, y));

	while (!coordinatesQueue.empty())
	{
		pair<int, int> coordinates = coordinatesQueue.front();
		coordinatesQueue.pop();
		int x = coordinates.first;
		int y = coordinates.second;
		for (int i = 0; i < DIRECTIONS_COUNT; i++)
		{
			int deltaX = DIRECTIONS[i].first;
			int deltaY = DIRECTIONS[i].second;
			if (field[x + deltaX][y + deltaY] == EMPTY_SYMBOL)
			{
				coordinatesQueue.push(make_pair(x + deltaX, y + deltaY));
				field[x + deltaX][y + deltaY] = FILL_SYMBOL;
			}
		}
	}
}

void Fill(StartCoords& startCoords)
{
	while (!startCoords.startCoordsQueue.empty())
	{
		StartCoordsPair(startCoords.field,
			startCoords.startCoordsQueue.front().first,
			startCoords.startCoordsQueue.front().second);
		startCoords.startCoordsQueue.pop();
	}
}

void Print(const string& outputFileName, const Field& field)
{
	fstream output;
	output.open(outputFileName, ios_base::out);

	for (int x = 1; x <= MAX_FIELD_SIZE; x++)
	{
		for (int y = 1; y <= MAX_FIELD_SIZE; y++)
		{
			output << field[x][y];
		}
		output << endl;
	}
}

int main(int argc, char* argv[])
{
	bool success = false;
	CommandLineArguments arguments = ParseArguments(argc, argv, success);

	if (!success)
	{
		cerr << "Wrong command line arguments" << endl;
		cerr << "Expected fill.exe [input file] [output file]" << endl;
		return 1;
	}

	success = false;

	StartCoords startCoords = FindStartCoordinates(arguments.inputFileName, success);

	if (!success)
	{
		cerr << "Error on parsing input file" << endl;
		return 1;
	}

	Fill(startCoords);

	Print(arguments.outputFileName, startCoords.field);

	return 0;
}


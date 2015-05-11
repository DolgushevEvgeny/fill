// fill.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <string>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

void ReadMap(const string &fileName, vector<vector<char>> &map)
{
	ifstream inputFile;
	inputFile.open(fileName, ifstream::in);

	if (!(inputFile.good()))
	{
		exit(1);
	}

	for (int i = 0; i < 100; ++i)
	{
		vector<char> line;
		for (int j = 0; j < 100; ++j)
		{
			char symbol;
			if (!inputFile.eof())
			{
				inputFile.get(symbol);
				if (symbol != '\n')
				{
					line.push_back(symbol);
				}
				else
				{
					break;
				}
			}
		}
		map.push_back(line);
		if (inputFile.eof())
		{
			break;
		}
	}
}

void PaintMap(const int &k, const int &p, vector<vector<char>> &map)
{
	if ((0 < k && k < map.size()) && (0 < p && p < map[0].size()))
	{
		if (k + 1 <= map.size())
		{
			if (map[k + 1][p] == ' ')
			{
				map[k+1][p] = '.';
				PaintMap(k + 1, p, map);
			}
		}
		if (k - 1 >= 0)
		{
			if (map[k - 1][p] == ' ')
			{
				map[k-1][p] = '.';
				PaintMap(k - 1, p, map);
			}
		}
		if (p + 1 <= map[0].size())
		{
			if (map[k][p + 1] == ' ')
			{
				map[k][p+1] = '.';
				PaintMap(k, p + 1, map);
			}
		}
		if (p - 1 >= 0)
		{
			if (map[k][p - 1] == ' ')
			{
				map[k][p-1] = '.';
				PaintMap(k, p - 1, map);
			}
		}
	}
}

void SaveMap(const vector<vector<char>> &map, const string &fileName)
{
	ofstream outputFile;
	outputFile.open(fileName, ofstream::out);

	if (!(outputFile.good()))
	{
		exit(1);
	}

	for (int i = 0; i < map.size(); i++)
	{
		for (int j = 0; j < map[0].size(); j++)
		{
			if (i != map.size() && j != map[0].size())
			{
				outputFile << map[i][j];
			}
		}
		if (i < map.size() - 1)
		{
			outputFile << endl;
		}
	}
}

void WaveSearch(vector<vector<char>> &map)
{
	for (unsigned int i = 0; i < map.size(); ++i)
	{
		for (unsigned int j = 0; j < map[0].size(); ++j)
		{
			if (map[i][j] == 'O')
			{
				PaintMap(i, j, map);
			}
		}
	}
}

void PrintMap(const vector<vector<char>> &map)
{
	for (int i = 0; i < map.size(); i++)
	{
		for (int j = 0; j < map[0].size(); j++)
		{
			cout << map[i][j];
		}
		cout << endl;
	}
}
int main(int argc, char* argv[])
{
	string inputFileName = argv[1];
	string outputFileName = argv[2];

	vector<vector<char>> map;
	ReadMap(inputFileName, map);
	WaveSearch(map);
	if (outputFileName.size() == 0)
	{
		PrintMap(map);
	}
	SaveMap(map, outputFileName);
	return 0;
}


// fill.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <malloc.h>
#include <string>
#include <fstream>

using namespace std;

int n_size = 0, m_size = 0;

void Dispose_Memory(char **matrix)
{
	for (int i = 0; i < 3; i++)
	{
		delete[] matrix[i];
	}
	delete[] matrix;
}

char** Read_Map(char *file_name)
{
	FILE *file_input = fopen(file_name, "r");
	if (file_input == NULL)
	{
		printf("Error: cannot load input file\n");
		system("pause");
		exit(1);
	}
	
	char **map = new char*[100];
	for (int i = 0; i < 100; i++)
	{
		map[i] = new char[100];
		for (int j = 0; j < 100; j++)
		{
			char symbol;
			if (!feof(file_input))
			{
				symbol = fgetc(file_input);
				if (symbol != '\n')
				{
					map[i][j] = symbol;
					m_size++;
				}
				else
					break;
			}
		}
		n_size++;
		if (feof(file_input))
			break;
	}
	m_size = (m_size - 1) / n_size;
	return map;
	fclose(file_input);
}

void Paint_Map(int k, int p, char** map)
{
	if ((0 < k < n_size) && (0 < p < m_size))
	{
		if (k + 1 <= n_size)
		{
			if (map[k + 1][p] == ' ')
			{
				map[k+1][p] = '.';
				Paint_Map(k + 1, p, map);
			}
		}
		if (k - 1 >= 0)
		{
			if (map[k - 1][p] == ' ')
			{
				map[k-1][p] = '.';
				Paint_Map(k - 1, p, map);
			}
		}
		if (p + 1 <= m_size)
		{
			if (map[k][p + 1] == ' ')
			{
				map[k][p+1] = '.';
				Paint_Map(k, p + 1, map);
			}
		}
		if (p - 1 >= 0)
		{
			if (map[k][p - 1] == ' ')
			{
				map[k][p-1] = '.';
				Paint_Map(k, p - 1, map);
			}
		}
	}
}

void Save_Map(char** map, char *file_name)
{
	FILE *file_output = fopen(file_name, "w");
	if (file_output == NULL)
	{
		printf("Error: cannot create output file\n");
		system("pause");
		exit(1);
	}

	for (int i = 0; i < n_size; i++)
	{
		for (int j = 0; j < m_size; j++)
		{
			if (i != n_size && j != m_size)
				fprintf(file_output, "%c", map[i][j]);
		}
		if (i < n_size - 1)
			fprintf(file_output, "%s", "\n");
	}
	fclose(file_output);
	Dispose_Memory(map);
}

void Wave_search(char **map)
{
	for (int i = 0; i < n_size; i++)
	{
		for (int j = 0; j < m_size; j++)
		{
			if (map[i][j] == 'O')
				Paint_Map(i, j, map);
		}
	}
}

void Print_Map(char **map)
{
	for (int i = 0; i < n_size; i++)
	{
		for (int j = 0; j < m_size; j++)
			printf("%c", map[i][j]);

		printf("%s", "\n");
	}
}
int main(int argc, char* argv[])
{
	char *Name_input = argv[1];
	char *Name_output = argv[2];
	char **Map = Read_Map(Name_input);
	//Print_Map(Map);
	Wave_search(Map);
	Save_Map(Map,Name_output);
	return 0;
}


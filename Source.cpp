#include "golFunc.h"
#include <stdio.h>
#include <fstream>

const int MAX_X = 12;
const int MAX_Y = 20;

int game[MAX_X][MAX_Y] = {}; // game[rows][columns]
int next[MAX_X][MAX_Y] = {};

int countCells(int x, int y, int r) // Count neighbours
{
	int sum = 0;
	for (int i = x - r; i <= x + r; i++)
	{
		int i_wrapped = (i + MAX_X) % MAX_X; // Wrap the game board (rows)
		for (int j = y - r; j <= y + r; j++)
		{
			int j_wrapped = (j + MAX_Y) % MAX_Y; // Wrap the game board (columns)
			sum += game[i_wrapped][j_wrapped];   // Add state of a cell to sum (1/0)
		}
	}
	sum -= game[x][y];
	return sum;
}

void nextIteration() // Calculate next iteration
{
	for (int i = 0; i < MAX_X; i++)
	{
		for (int j = 0; j < MAX_Y; j++)
		{
			int neighbours = countCells(i, j, 1); // Variable with neighbours of a cell
			// Check rules
			if (game[i][j] == 0 && neighbours == 3)
			{
				next[i][j] = 1;
			}
			else if (game[i][j] == 1 && (neighbours == 3 || neighbours == 2))
			{
				next[i][j] = 1;
			}
			else
			{
				next[i][j] = 0;
			}
		}
	}
}

void writeToNew() // Write iteration to game[][]
{
	for (int i = 0; i < MAX_X; i++)
	{
		for (int j = 0; j < MAX_Y; j++)
		{
			game[i][j] = next[i][j];
		}
	}
}

void writeToConsole() // Write current iteration to console
{
	for (int i = 0; i < MAX_X; i++)
	{
		for (int j = 0; j < MAX_Y; j++)
		{
			printf("%d", game[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

void countAliveCells() // Count alive cells in iteration
{
	int suma = 0;
	for (int i = 0; i < MAX_X; i++)
	{
		for (int j = 0; j < MAX_Y; j++)
		{
			suma += game[i][j];
		}
	}
	printf("Count of alive cells in iteration: %d \n", suma);
}

bool equalIters() // Check equality of iterations
{
	for (int i = 0; i < MAX_X; i++)
	{
		for (int j = 0; j < MAX_Y; j++)
		{
			if (game[i][j] != next[i][j])
				return false;
		}
	}
	return true;
}

void part1() // Output number of alive neighbours in 37th iteration for cell in 2nd row and 19th collumn
{
	for (int i = 1; i < 37; i++)
	{
		nextIteration();
		writeToNew();
	}
	printf("%d", countCells(1, 18, 1));
}

void part2() // Output number of alive cells in 2nd iteration
{
	for (int i = 1; i < 2; i++)
	{
		nextIteration();
		writeToNew();
	}
	countAliveCells();
}

void part3() // In which iteration (max 100) current and previous one will be identical
{
	for (int i = 1; i < 100; i++)
	{
		nextIteration();
		if (equalIters())
		{
			printf("\nEqual in iteration: %d \n", i + 1);
			break;
		}
		writeToNew();
	}
	countAliveCells();
}

void writeBegFromFile()
{
	std::ifstream input;
	input.open("gra.txt");
	char a;
	for (int x = 0; x < MAX_X; x++) // Import and coversion to dead (0) or alive (1)
	{
		for (int y = 0; y < MAX_Y; y++)
		{
			input >> a;
			if (a == '.')
				game[x][y] = 0;
			else
				game[x][y] = 1;
		}
	}
}
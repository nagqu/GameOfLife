#include "golFunc.h"
#include <Windows.h>
#include <stdio.h>

/*	A code designed to solve problem from 
	exercise 5 2016 matura exam (old) */

void gamePreview()
{
	while (true)
	{
		nextIteration();
		writeToNew();
		writeToConsole();
		Sleep(750);
		system("cls");
	}
}

int main()
{
	writeBegFromFile();
	//Uncomment to run. Only one at a time.
	//part1();
	//part2();
	//part3();
	return 0;
}
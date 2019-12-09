// Day07.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "IntcodeComputer.h"

#include <iostream>
#include <fstream>

int main()
{
	std::vector<int> input;
	std::vector<int> program;

	int value;
	char split;

	std::ifstream fileIn("input.txt");

	while (fileIn >> value >> split)
	{
		input.push_back(value);
	}
	fileIn >> value;
	input.push_back(value);

	program.assign(input.begin(), input.end());

}

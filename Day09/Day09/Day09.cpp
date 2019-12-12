// Day09.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "IntcodeComputer.h"

#include <iostream>
#include <fstream>

int main()
{
	std::vector<std::int64_t> input;
	std::vector<std::int64_t> program;

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

	IntcodeComputer part1(program);

	part1.RunProgram();
}

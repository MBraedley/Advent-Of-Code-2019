// Day5.cpp : This file contains the 'main' function. Program execution begins and ends there.
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

	IntcodeComputer part1(program);

	part1.RunProgram();

	program.assign(input.begin(), input.end());
//	std::vector<int> test({ 3,21,1008,21,8,20,1005,20,22,107,8,21,20,1006,20,31,1106,0,36,98,0,0,1002,21,125,20,4,20,1105,1,46,104,999,1105,1,46,1101,1000,1,20,4,20,1105,1,46,98,99 });
	IntcodeComputer part2(program);

	part2.RunProgram();
}

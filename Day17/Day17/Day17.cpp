// Day17.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "IntcodeComputer.h"

#include <iostream>

int main()
{
	auto input = IntcodeComputer::RaedProgram("input.txt");

	IntcodeComputer computer(input);

	computer.SetOutputCallback([](std::int64_t output)
		{
			std::cout << static_cast<char>(output);
		});

	computer.RunProgram();
}

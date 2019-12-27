// Day25.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "IntcodeComputer.h"

#include <iostream>
#include <queue>

int main()
{
	auto program = IntcodeComputer::ReadProgram("input.txt");

	IntcodeComputer comp(program);

	comp.SetOutputCallback([](std::int64_t value)
		{
			std::cout << static_cast<char>(value);
		});

	comp.SetInputCallback([]()->std::int64_t
		{
			int c = getchar();
			return static_cast<std::int64_t>(c);
		});

	comp.RunProgram();
}

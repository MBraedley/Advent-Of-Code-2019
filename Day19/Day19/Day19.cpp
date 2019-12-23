// Day19.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "IntcodeComputer.h"

#include <iostream>
#include <queue>

int main()
{
	auto input = IntcodeComputer::RaedProgram("input.txt");
	auto program = input;

	std::queue<std::int64_t> inputValues;

	for (std::int64_t x = 0; x < 50; x++)
	{
		for (std::int64_t y = 0; y < 50; y++)
		{
			inputValues.push(x);
			inputValues.push(y);
		}
	}

	std::int64_t count = 0;

	while (!inputValues.empty())
	{
		IntcodeComputer part1(program);

		part1.SetInputCallback([&]()->std::int64_t
			{
				std::int64_t value = inputValues.front();
				inputValues.pop();
				return value;
			});

		part1.SetOutputCallback([&](std::int64_t value)
			{
				count += value;
			});

		part1.RunProgram();
	}

	std::cout << count << std::endl;
}

// Day21.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "IntcodeComputer.h"

#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include <cassert>

int main()
{
	auto program = IntcodeComputer::ReadProgram("input.txt");

	std::queue<char> assembly;
	std::ifstream fileIn1("springscript1.txt");

	for (std::string line; std::getline(fileIn1, line); )
	{
		line.append("\n");
		if (line.front() != '#')
		{
			for (char c : line)
			{
				assembly.push(c);
			}
		}
	}

	IntcodeComputer part1(program);

	part1.SetInputCallback([&]()->std::int64_t
		{
			std::int64_t input = static_cast<std::int64_t>(assembly.front());
			assembly.pop();
			return input;
		});

	part1.SetOutputCallback([&](std::int64_t output)
		{
			if (output < 256)
				std::cout << static_cast<char>(output);
			else
				std::cout << "Damage: " << output << std::endl;
		});

	part1.RunProgram();

	//////////////////////////////////

	assert(assembly.empty());

	std::ifstream fileIn2("springscript2.txt");

	for (std::string line; std::getline(fileIn2, line); )
	{
		line.append("\n");
		if (line.front() != '#')
		{
			for (char c : line)
			{
				assembly.push(c);
			}
		}
	}

	IntcodeComputer part2(program);

	part2.SetInputCallback([&]()->std::int64_t
		{
			std::int64_t input = static_cast<std::int64_t>(assembly.front());
			assembly.pop();
			return input;
		});

	part2.SetOutputCallback([&](std::int64_t output)
		{
			if (output < 256)
				std::cout << static_cast<char>(output);
			else
				std::cout << "Damage: " << output << std::endl;
		});

	part2.RunProgram();
}


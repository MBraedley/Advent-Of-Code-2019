// Day17.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "IntcodeComputer.h"

#include <iostream>
#include <deque>

int main()
{
	auto input = IntcodeComputer::RaedProgram("input.txt");
	auto program = input;

	IntcodeComputer computer(program);

	std::string video;
	computer.SetOutputCallback([&](std::int64_t output)
		{
			video.push_back(static_cast<char>(output));
			std::cout << static_cast<char>(output);
		});

	computer.RunProgram();

	std::vector<char> row;
	std::vector<std::vector<char>> display;

	for (char pixel : video)
	{
		if (pixel <= 32 && !row.empty())
		{
			display.push_back(row);
			row.clear();
		}
		else
			row.push_back(pixel);
	}

	std::vector<std::pair<size_t, size_t>> intersections;
	for (size_t y = 1; y < display.size() - 1; y++)
	{
		for (size_t x = 1; x < display[y].size() - 1; x++)
		{
			if (display[y][x] == '#' &&
				display[y][x + 1] == '#' &&
				display[y][x - 1] == '#' &&
				display[y + 1][x] == '#' &&
				display[y - 1][x] == '#')
				intersections.push_back({ x, y });
		}
	}

	size_t alignmentParam = 0;
	for (auto coord : intersections)
	{
		alignmentParam += coord.first * coord.second;
	}

	std::cout << alignmentParam << std::endl;

	program = input;
	program[0] = 2;

	std::string mainRoutine = "A,B,A,C,B,A,B,C,C,B\n";
	std::string moveA = "L,12,L,12,R,4\n";
	std::string moveB = "R,10,R,6,R,4,R,4\n";
	std::string moveC = "R,6,L,12,L,12\n";

	std::deque<char> movements;
	movements.insert(movements.end(), mainRoutine.begin(), mainRoutine.end());
	movements.insert(movements.end(), moveA.begin(), moveA.end());
	movements.insert(movements.end(), moveB.begin(), moveB.end());
	movements.insert(movements.end(), moveC.begin(), moveC.end());
	movements.push_back('n');
	movements.push_back('\n');

	IntcodeComputer part2(program);
	
	part2.SetInputCallback([&]()->std::int64_t
		{
			std::int64_t input = static_cast<std::int64_t>(movements.front());
			movements.pop_front();
			return input;
		});

	part2.SetOutputCallback([&](std::int64_t output)
		{
			if (output < 256)
			{
				video.push_back(static_cast<char>(output));
				std::cout << static_cast<char>(output);
			}
			else
				std::cout << "Dust: " << output << std::endl;
		});

	part2.RunProgram();
}

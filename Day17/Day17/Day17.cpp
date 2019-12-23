// Day17.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "IntcodeComputer.h"

#include <iostream>

int main()
{
	auto input = IntcodeComputer::RaedProgram("input.txt");

	IntcodeComputer computer(input);

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
}

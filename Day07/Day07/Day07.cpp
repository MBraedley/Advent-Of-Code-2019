// Day07.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "IntcodeComputer.h"

#include <iostream>
#include <fstream>
#include <future>

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

	std::vector<std::vector<int>> permutations;
	std::ifstream permFile("permutations.txt");

	int a, b, c, d, e;
	while (permFile >> a >> split >> b >> split >> c >> split >> d >> split >>e)
	{
		permutations.push_back({ a, b, c, d, e });
	}

	int best = 0;

	for (auto permute : permutations)
	{
		int nextSignal = 0;
		for (int phase : permute)
		{
			program.assign(input.begin(), input.end());
			IntcodeComputer amp(program);

			amp.SetInputCallback([&]()->int
				{
					amp.SetInputCallback([&]()->int
						{
							return nextSignal;
						});

					return phase;
				});

			amp.SetOutputCallback([&](int signal)
				{
					nextSignal = signal;
				});

			amp.RunProgram();
		}
		if (nextSignal > best)
		{
			best = nextSignal;
		}
	}

	std::cout << best << std::endl;

	// Part 2
	//best = 0;

	//for (auto permute : permutations)
	//{
	//	int nextSignal = 0;
	//	for (int phase : permute)
	//	{
	//		program.assign(input.begin(), input.end());
	//		IntcodeComputer amp(program);

	//		amp.SetInputCallback([&]()->int
	//			{
	//				amp.SetInputCallback([&]()->int
	//					{
	//						return nextSignal;
	//					});

	//				return phase;
	//			});

	//		amp.SetOutputCallback([&](int signal)
	//			{
	//				nextSignal = signal;
	//			});

	//		amp.RunProgram();
	//	}
	//	if (nextSignal > best)
	//	{
	//		best = nextSignal;
	//	}
	//}

	//std::cout << best << std::endl;
}

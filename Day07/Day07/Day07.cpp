// Day07.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "IntcodeComputer.h"
#include "IOConnector.h"

#include <iostream>
#include <fstream>
#include <cassert>
#include <thread>

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
	best = 0;

	for (auto permute : permutations)
	{
		std::vector<std::shared_ptr<IntcodeComputer>> amps;
		for (int phase : permute)
		{
			program.assign(input.begin(), input.end());
			std::shared_ptr<IntcodeComputer> amp = std::make_shared<IntcodeComputer>(program);
			amps.push_back(amp);
		}
		std::vector<std::shared_ptr<IOConnector>> connectors;
		connectors.push_back(std::make_shared<IOConnector>(amps[amps.size() - 1], amps[0]));
		for (std::uint32_t i = 1; i < amps.size(); i++)
		{
			connectors.push_back(std::make_shared<IOConnector>(amps[i - 1], amps[i]));
		}

		assert(connectors.size() == permute.size());

		//Queue the phase arguments
		for (std::uint32_t i = 0; i < connectors.size(); i++)
		{
			connectors[i]->SetValue(permute[i] + 5);
		}

		//Queue up the starting value
		connectors[0]->SetValue(0);

		std::vector<std::thread> runningAmps;
		for (auto& amp : amps)
		{
			runningAmps.emplace_back(std::bind(&IntcodeComputer::RunProgram, amp));
		}

		for (auto& thd : runningAmps)
		{
			thd.join();
		}

		int output = connectors[0]->GetValue();
		if (output > best)
			best = output;
	}

	//std::vector<int> permute = { 4,3,2,1,0 };
	//std::vector<std::shared_ptr<IntcodeComputer>> amps;
	//for (int phase : permute)
	//{
	//	program = { 3,26,1001,26,-4,26,3,27,1002,27,2,27,1,27,26,27,4,27,1001,28,-1,28,1005,28,6,99,0,0,5 };
	//	std::shared_ptr<IntcodeComputer> amp = std::make_shared<IntcodeComputer>(program);
	//	amps.push_back(amp);
	//}
	//std::vector<std::shared_ptr<IOConnector>> connectors;
	//connectors.push_back(std::make_shared<IOConnector>(amps[amps.size() - 1], amps[0]));
	//for (std::uint32_t i = 1; i < amps.size(); i++)
	//{
	//	connectors.push_back(std::make_shared<IOConnector>(amps[i - 1], amps[i]));
	//}

	//assert(connectors.size() == permute.size());

	////Queue the phase arguments
	//for (std::uint32_t i = 0; i < connectors.size(); i++)
	//{
	//	connectors[i]->SetValue(permute[i] + 5);
	//}

	////Queue up the starting value
	//connectors[0]->SetValue(0);

	//std::vector<std::thread> runningAmps;
	//for (auto& amp : amps)
	//{
	//	runningAmps.emplace_back(std::bind(&IntcodeComputer::RunProgram, amp));
	//}

	//for (auto& thd : runningAmps)
	//{
	//	thd.join();
	//}

	//int output = connectors[0]->GetValue();
	//if (output > best)
	//	best = output;

	std::cout << best << std::endl;
}

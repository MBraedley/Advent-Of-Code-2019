// Day19.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "IntcodeComputer.h"

#include "readerwriterqueue.h"

#include <iostream>
#include <deque>

int main()
{
	auto input = IntcodeComputer::RaedProgram("input.txt");
	auto program = input;

	std::pair<std::int64_t, std::int64_t> testPoint = { 0, 0 };

	std::deque<std::int64_t> inputValues;

	//for (std::int64_t x = 0; x < 50; x++)
	//{
	//	for (std::int64_t y = 0; y < 50; y++)
	//	{
	//		inputValues.push_back(x);
	//		inputValues.push_back(y);
	//	}
	//}

	std::int64_t count = 0;
	std::int64_t totalCount = 0;
	bool inTractorBeam = false;

	IntcodeComputer part1(program);

	part1.SetInputCallback([&]()->std::int64_t
		{
			std::int64_t value = inputValues.front();
			inputValues.pop_front();
			return value;
		});

	part1.SetOutputCallback([&](std::int64_t value)
		{
			count += value;
			inTractorBeam = value == 1;
		});

	std::int64_t rowStart = 0;

	for (std::int64_t y = 0; y < 50; y++)
	{
		count = 0;
		for (std::int64_t x = 0; x < 50; x++)
		{
			if (x >= rowStart && (count == 0 || inTractorBeam))
			{
				inputValues.push_back(x);
				inputValues.push_back(y);
				part1.Reset(program);
				part1.RunProgram();

				std::cout << (inTractorBeam ? "#" : ".");
			}
			else
				std::cout << ".";
		}
		totalCount += count;
		std::cout << std::endl;
	}
	
	std::cout << totalCount << std::endl;

	///////////////////////////////////////////////////////////////////

	std::int64_t width = 0;
	std::int64_t height = 0;
	testPoint = { 1820, 1976 };

	while (true)
	{
		inputValues.clear();
		count = 0;
		inTractorBeam = true;
		for (std::int64_t x = testPoint.first; x < testPoint.first + 110; x++)
		{
			inputValues.push_back(x);
			inputValues.push_back(testPoint.second);
		}

		while (!inputValues.empty() && inTractorBeam)
		{
			part1.Reset(program);
			part1.RunProgram();
		}

		width = count;

		inputValues.clear();
		count = 0;
		inTractorBeam = true;
		for (std::int64_t y = testPoint.second; y < testPoint.second + 110; y++)
		{
			inputValues.push_back(testPoint.first);
			inputValues.push_back(y);
		}

		while (!inputValues.empty() && inTractorBeam)
		{
			part1.Reset(program);
			part1.RunProgram();
		}

		height = count;
		inputValues.clear();

		if (width == 100 && height == 100)
		{
			std::cout << testPoint.first * 10000 + testPoint.second;
			return 0;
		}

		if (width == height)
		{
			testPoint.first++;
			testPoint.second++;
		}
		else if (width > height)
			testPoint.first++;
		else
			testPoint.second++;
	}
}

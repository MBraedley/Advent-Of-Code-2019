// Day11.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "PainterRobot.h"

#include "IntcodeComputer.h"

#include <iostream>
#include <fstream>
#include <memory>

int main()
{
	std::vector<std::int64_t> input;
	std::vector<std::int64_t> program;

	std::int64_t value;
	char split;

	std::ifstream fileIn("input.txt");

	while (fileIn >> value >> split)
	{
		input.push_back(value);
	}
	fileIn >> value;
	input.push_back(value);

	program.assign(input.begin(), input.end());

	IntcodeComputer comp(program);

	PainterRobot robot;

	comp.SetInputCallback([&robot]() -> std::int64_t { return robot.Output(); });
	comp.SetOutputCallback([&robot](std::int64_t value) {robot.Input(value); });

	comp.RunProgram();

	auto numPanels = robot.GetNumPaintedPanels();

	//robot.Draw();
	std::cout << numPanels << std::endl;

	//Part 2
	program.assign(input.begin(), input.end());

	IntcodeComputer comp2(program);

	PainterRobot robot2;
	robot2.SetStartToWhite();

	comp2.SetInputCallback([&robot2]() -> std::int64_t { return robot2.Output(); });
	comp2.SetOutputCallback([&robot2](std::int64_t value) {robot2.Input(value); });

	comp2.RunProgram();

	robot2.Draw();
}

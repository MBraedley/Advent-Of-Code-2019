// Day13.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "ArcadeGame.h"
#include "IntcodeComputer.h"

#include <iostream>
#include <unordered_map>


int main()
{
	auto input = IntcodeComputer::RaedProgram("input.txt");
	auto program = input;

	IntcodeComputer computer(program);

	ArcadeGame game(computer);
	game.RunGame();

	std::cout << game.CountBlocks() << std::endl;

	IntcodeComputer computer2(input);
	computer2.SetValue(0, 2);

	ArcadeGame game2(computer2);
	game2.RunGame();
}

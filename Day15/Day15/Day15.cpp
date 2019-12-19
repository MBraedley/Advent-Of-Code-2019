// Day15.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "RepairDroidController.h"

#include "IntcodeComputer.h"

#include <iostream>

int main()
{
	auto input = IntcodeComputer::RaedProgram("input.txt");

	RepairDroidController controller;

	IntcodeComputer computer(input);

	computer.SetInputCallback(std::bind(&RepairDroidController::CommandMovement, &controller));
	computer.SetOutputCallback(std::bind(&RepairDroidController::RecieveStatus, &controller, std::placeholders::_1));

	computer.RunProgram();

	controller.Draw();

	controller.GetFillTime();
}

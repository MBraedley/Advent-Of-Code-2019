// Day2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <cassert>

void PrintProgram(const std::vector<int>& program)
{
	for (int value : program)
	{
		std::cout << value << ",";
	}
	std::cout << std::endl;
}

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

	program.assign(input.begin(), input.end());

	program[1] = 12;
	program[2] = 2;

	bool halt = false;
	int sp = 0;
	while (!halt)
	{
		switch (program[sp])
		{
		case 1:
			program[program[sp + 3]] = program[program[sp + 1]] + program[program[sp + 2]];
			break;
		case 2:
			program[program[sp + 3]] = program[program[sp + 1]] * program[program[sp + 2]];
			break;
		case 99:
			halt = true;
			break;
		default:
			assert(false);
		}
		sp += 4;
	}

	std::cout << program[0];

	//part 2

}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file

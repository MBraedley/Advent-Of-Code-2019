// Day16.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <vector>

int main()
{
	std::vector<int> pattern = { 0, 1, 0, -1 };
	std::vector<int> input;
	std::vector<int> output;

	std::ifstream file("input.txt");
	char value;

	while (file >> value)
	{
		input.push_back(value - '0');
	}
	output = input;

	for (int i = 0; i < 100; i++)
	{
		for (size_t outIndex = 0; outIndex < input.size(); outIndex++)
		{
			int value = 0;
			for (size_t inIndex = 0; inIndex < input.size(); inIndex++)
			{
				int patternIndex = ((inIndex + 1) / (outIndex + 1)) % pattern.size();
				value += input[inIndex] * pattern[patternIndex];
			}
			output[outIndex] = abs(value) % 10;
		}
		input.swap(output);
	}

	for (int i = 0; i < 8; i++)
	{
		std::cout << input[i];
	}
}

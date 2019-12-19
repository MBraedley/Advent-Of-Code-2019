// Day16.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <cassert>

int main()
{
	std::vector<int> pattern = { 0, 1, 0, -1 };
	std::vector<int> input;
	std::vector<int> output;
	std::vector<int> originalInput;

	std::ifstream file("input.txt");
	char value;

	while (file >> value)
	{
		originalInput.push_back(value - '0');
	}
	input = originalInput;
	output = originalInput;

	for (int i = 0; i < 100; i++)
	{
		for (size_t outIndex = 0; outIndex < input.size(); outIndex++)
		{
			int value = 0;
			for (size_t inIndex = outIndex; inIndex < input.size(); inIndex++)
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
	std::cout << std::endl;

	input.clear();
	for (int i = 0; i < 10000; i++)
	{
		input.insert(input.end(), originalInput.begin(), originalInput.end());
	}
	output = input;

	size_t offset = 0;
	for (int i = 0; i < 7; i++)
	{
		offset = offset * 10 + input[i];
	}

	assert(offset >= input.size() / 2);

	std::cout << offset << std::endl;

	for (int i = 0; i < 100; i++)
	{
		int sum = 0;
		for (int outIndex = output.size() - 1; outIndex >= offset; outIndex--)
		{
			sum += input[outIndex];
			output[outIndex] = abs(sum) % 10;
		}
		input.swap(output);
	}

	for (int i = 0; i < 8; i++)
	{
		std::cout << input[i + offset];
	}
	std::cout << std::endl;
}

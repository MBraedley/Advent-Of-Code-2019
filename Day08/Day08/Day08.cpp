// Day08.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <cassert>
#include <thread>
#include <vector>
#include <array>

#define NOMINMAX

int main()
{
	std::vector<int> input;

	char value;

	std::ifstream fileIn("input.txt");

	while (fileIn >> value)
	{
		input.push_back(value - '0');
	}
	
	static const int width = 25;
	static const int height = 6;
	static const int layerSize = width * height;
	int numLayers = input.size() / layerSize;
	int leastZeroes = std::numeric_limits<int>::max();
	int zeroLayer = -1;
	
	for (int i = 0; i < numLayers; i++)
	{
		int count = 0;
		for (int j = 0; j < layerSize; j++)
		{
			if (input[layerSize * i + j] == 0)
				count++;
		}
		if (count < leastZeroes)
		{
			leastZeroes = count;
			zeroLayer = i;
		}
	}
	assert(leastZeroes != std::numeric_limits<int>::max() && zeroLayer != 0);

	int oneCount = 0;
	int twoCount = 0;

	int offset = zeroLayer * layerSize;
	for (int i = 0; i < layerSize; i++)
	{
		if (input[i + offset] == 1)
			oneCount++;
		else if (input[i + offset] == 2)
			twoCount++;
	}

	std::cout << oneCount * twoCount << std::endl;

	std::array<std::array<int, width>, height> image;
	for (auto& row : image)
	{
		memset(row.data(), 2, row.size());
	}

	for (int i = numLayers - 1; i >= 0; i--)
	{
		for (int row = 0; row < height; row++)
		{
			for (int col = 0; col < width; col++)
			{
				int val = input[col + row * width + i * layerSize];
				if (val != 2)
					image[row][col] = val;
			}
		}
	}


	for (int row = 0; row < height; row++)
	{
		for (int col = 0; col < width; col++)
		{
			std::cout << (image[row][col] == 1 ? "#" : " ");
		}
		std::cout << std::endl;
	}
}

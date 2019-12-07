// Day06.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <map>
#include <vector>

int main()
{
	std::vector<std::string> parents;
	std::vector<std::string> children;
	std::ifstream fileIn("input.txt");

	std::string line;
	while (fileIn >> line)
	{
		parents.push_back(line.substr(0, 3));
		children.push_back(line.substr(4, 3));
	}
}

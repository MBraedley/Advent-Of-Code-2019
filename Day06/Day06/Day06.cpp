// Day06.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "Orbit.h"

#include <iostream>
#include <fstream>
#include <map>
#include <vector>

int main()
{
	std::ifstream fileIn("input.txt");

	std::map<std::string, std::shared_ptr<Orbit>> orbits;

	std::string line;
	while (fileIn >> line)
	{
		std::string parent = line.substr(0, 3);
		std::string child = line.substr(4, 3);

		if (orbits.find(parent) == orbits.end())
		{
			orbits[parent] = std::make_shared<Orbit>(parent);
		}

		if (orbits.find(child) == orbits.end())
		{
			orbits[child] = std::make_shared<Orbit>(child);
		}

		orbits[parent]->AddChild(orbits[child]);
	}

	for (auto& orbit : orbits)
	{
		if (!orbit.second->HasParent())
		{
			std::cout << orbit.second->GetOrbitCount(0) << std::endl;
		}
	}

	std::cout << Orbit::GetTransferCount(orbits["YOU"], orbits["SAN"]) << std::endl;

	return 0;
}

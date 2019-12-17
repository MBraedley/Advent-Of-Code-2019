// Day14.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <cassert>

std::map<std::string, std::map<std::string, std::int64_t>> ingredients;
std::map<std::string, std::int64_t> resultMultiplier;

void ParseReaction(std::string line)
{
	std::stringstream ingredStrm(line.substr(0, line.find_first_of('=')-1));

	std::uint64_t count;
	std::string ingredient;
	std::map<std::string, std::int64_t> ingredMap;
	while (ingredStrm >> count >> ingredient)
	{
		ingredient = ingredient.substr(0, ingredient.find_last_of(','));
		ingredMap.insert({ ingredient, count });
	}

	std::stringstream resultStrm(line.substr(line.find_first_of('>') + 1));
	resultStrm >> count >> ingredient;
	ingredients.insert({ ingredient, ingredMap });
	resultMultiplier.insert({ ingredient, count });
}

int main()
{
	std::map<std::string, std::int64_t> fuelMap;

	std::ifstream input("input.txt");
	
	for (std::string line; std::getline(input, line); )
	{
		ParseReaction(line);
	}

	fuelMap = ingredients["FUEL"];
	bool notdone;

	do
	{
		notdone = false;

		std::int64_t most = 0;
		auto best = fuelMap.end();

		for (auto iter = fuelMap.begin(); iter != fuelMap.end(); iter++)
		{
			if (ingredients[iter->first].size() > most && iter->second > 0)
			{
				most = ingredients[iter->first].size();
				best = iter;
				notdone = true;
			}
		}

		if (notdone && best != fuelMap.end())
		{
			std::uint64_t multiplier = (best->second + resultMultiplier[best->first] - 1) / resultMultiplier[best->first];
			for (auto iter : ingredients[best->first])
			{
				fuelMap[iter.first] += iter.second * multiplier;
			}
			fuelMap[best->first] -= resultMultiplier[best->first] * multiplier;
		}
	} while (notdone);

	for (auto& iter : fuelMap)
	{
		std::cout << iter.first << ": " << iter.second << std::endl;
	}

	// Part 2
	fuelMap = ingredients["FUEL"];
	fuelMap["ORE"] = -1000000000000;
	std::uint64_t fuelCount = 0;
	do
	{
		std::int64_t most = 0;
		auto best = fuelMap.end();

		for (auto iter = fuelMap.begin(); iter != fuelMap.end(); iter++)
		{
			if (ingredients[iter->first].size() > most&& iter->second > 0)
			{
				most = ingredients[iter->first].size();
				best = iter;
				notdone = true;
			}
		}

		if (best != fuelMap.end() && best->first != "ORE")
		{
			std::uint64_t multiplier = (best->second + resultMultiplier[best->first] - 1) / resultMultiplier[best->first];
			for (auto iter : ingredients[best->first])
			{
				fuelMap[iter.first] += iter.second * multiplier;
			}
			fuelMap[best->first] -= resultMultiplier[best->first] * multiplier;
		}
		else
		{
			fuelCount++;
			for (auto iter : ingredients["FUEL"])
			{
				fuelMap[iter.first] += iter.second;
			}
		}
	} while (fuelMap["ORE"] <= 0);

	std::cout << fuelCount - 1 << std::endl;
}

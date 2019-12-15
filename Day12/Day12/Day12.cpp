// Day12.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <set>
#include <sstream>
#include <numeric>

struct Vel3D
{
	std::int64_t x = 0;
	std::int64_t y = 0;
	std::int64_t z = 0;
};

struct Pos3D
{
	std::int64_t x = 0;
	std::int64_t y = 0;
	std::int64_t z = 0;

	Pos3D& operator+=(const Vel3D& vel)
	{
		this->x += vel.x;
		this->y += vel.y;
		this->z += vel.z;

		return *this;
	}
};

bool operator==(const Pos3D& lhs, const Pos3D& rhs)
{
	return lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z;
}

bool operator!=(const Pos3D& lhs, const Pos3D& rhs)
{
	return !(lhs == rhs);
}

bool operator==(const Vel3D& lhs, const Vel3D& rhs)
{
	return lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z;
}

bool operator!=(const Vel3D& lhs, const Vel3D& rhs)
{
	return !(lhs == rhs);
}

std::int64_t GetInt(std::string in)
{
	std::stringstream sstrm(in);
	std::int64_t out;
	sstrm >> out;
	return out;
}

void AdjustVelocities(const std::int64_t& pos1, std::int64_t& vel1, const std::int64_t& pos2, std::int64_t& vel2)
{
	if (pos1 < pos2)
	{
		vel1++;
		vel2--;
	}
	else if (pos1 > pos2)
	{
		vel1--;
		vel2++;
	}
	//Otherwise do nothing
}

void CalculateVelocities(std::vector<std::pair<Pos3D, Vel3D>>& orbits)
{
	for (int i = 0; i < orbits.size() - 1; i++)
	{
		auto& planet1 = orbits[i];
		for (int j = i + 1; j < orbits.size(); j++)
		{
			auto& planet2 = orbits[j];

			AdjustVelocities(planet1.first.x, planet1.second.x, planet2.first.x, planet2.second.x);
			AdjustVelocities(planet1.first.y, planet1.second.y, planet2.first.y, planet2.second.y);
			AdjustVelocities(planet1.first.z, planet1.second.z, planet2.first.z, planet2.second.z);
		}
	}
}

std::vector<bool> DimensionsMatch(const std::vector<std::pair<Pos3D, Vel3D>>& orbits1, const std::vector<std::pair<Pos3D, Vel3D>>& orbits2)
{
	if (orbits1.size() != orbits2.size())
		return { false, false, false };

	std::vector<bool> ret = { true, true, true };

	for (int i = 0; i < orbits1.size(); i++)
	{
		if (orbits1[i].first.x != orbits2[i].first.x || orbits1[i].second.x != orbits2[i].second.x)
			ret[0] = false;
		if (orbits1[i].first.y != orbits2[i].first.y || orbits1[i].second.y != orbits2[i].second.y)
			ret[1] = false;
		if (orbits1[i].first.z != orbits2[i].first.z || orbits1[i].second.z != orbits2[i].second.z)
			ret[2] = false;
	}
	return ret;
}

int main()
{
	std::vector<std::pair<Pos3D, Vel3D>> orbits;

	std::string lineX, lineY, lineZ;

	std::ifstream file("input.txt");
	while (file >> lineX >> lineY >> lineZ)
	{
		Pos3D pos;
		std::string xStr = lineX.substr(lineX.find_first_of('=') + 1);
		pos.x = GetInt(xStr);

		std::string yStr = lineY.substr(lineY.find_first_of('=') + 1);
		pos.y = GetInt(yStr);

		std::string zStr = lineZ.substr(lineZ.find_first_of('=') + 1);
		pos.z = GetInt(zStr);

		orbits.push_back({ pos, Vel3D() });
	}

	std::vector<std::pair<Pos3D, Vel3D>> initialOrbits = orbits;

	for (int i = 0; i < 1000; i++)
	{
		CalculateVelocities(orbits);
		for (auto& planet : orbits)
		{
			planet.first += planet.second;
		}
	}

	std::int64_t energy = 0;
	for (auto& planet : orbits)
	{
		int planetEnergy = (abs(planet.first.x) + abs(planet.first.y) + abs(planet.first.z)) * (abs(planet.second.x) + abs(planet.second.y) + abs(planet.second.z));
		energy += planetEnergy;
	}

	std::cout << energy << std::endl;

	std::uint64_t steps = 0;
	orbits = initialOrbits;

	std::uint64_t xRate = 0;
	std::uint64_t yRate = 0;
	std::uint64_t zRate = 0;

	do
	{
		CalculateVelocities(orbits);
		for (auto& planet : orbits)
		{
			planet.first += planet.second;
		}
		steps++;

		auto hasReps = DimensionsMatch(initialOrbits, orbits);
		if (hasReps[0] && xRate == 0)
			xRate = steps;
		if (hasReps[1] && yRate == 0)
			yRate = steps;
		if (hasReps[2] && zRate == 0)
			zRate = steps;

	} while ( xRate == 0 || yRate == 0 || zRate == 0);

	auto xyDiv = std::gcd(xRate, yRate);
	std::cout << std::lcm(xRate * yRate / xyDiv, zRate) << std::endl;
}

// Day10.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <numeric>
#include <set>
#include <optional>

static const double PI = 2.0 * atan2(1, 0);

struct Coord
{
	int x;
	int y;
};

bool operator<(const Coord& lhs, const Coord& rhs)
{
	double lAngle = atan2(lhs.x, 0 - lhs.y);
	if (lAngle < 0)
		lAngle += 2.0 * PI;
	double rAngle = atan2(rhs.x, 0 - rhs.y);
	if (rAngle < 0)
		rAngle += 2.0 * PI;

	return lAngle < rAngle;
}

bool operator==(const Coord& lhs, const Coord& rhs)
{
	int lGCD = std::gcd(abs(lhs.x), abs(lhs.y));
	int rGCD = std::gcd(abs(rhs.x), abs(rhs.y));
	return (lhs.x / lGCD == rhs.x / rGCD) && (lhs.y / lGCD == rhs.y / lGCD);
}

int CountRemaining(const std::vector<std::vector<char>>& field)
{
	int count = 0;
	for (const auto& row : field)
	{
		for (char c : row)
		{
			if (c == '#')
				count++;
		}
	}
	return count;
}

void ObscureAsteroid(std::vector<std::vector<char>>& field, int xStart, int yStart, int xOffset, int yOffset, int multiple)
{
	int width = field[0].size();
	int height = field.size();
	int xPos = xStart + xOffset * multiple;
	int yPos = yStart + yOffset * multiple;
	if (xPos < width && xPos >= 0 && yPos < height && yPos >= 0)
	{
		if (field[yPos][xPos] == '#')
			field[yPos][xPos] = '*';
		ObscureAsteroid(field, xStart, yStart, xOffset, yOffset, multiple + 1);
	}
}

void CheckAsteroid(std::vector<std::vector<char>>& field, int xStart, int yStart)
{
	int width = field[0].size();
	int height = field.size();

	for (int row = 0; row < height; row++)
	{
		for (int col = 0; col < width; col++)
		{
			if (!(col == xStart && row == yStart) && field[row][col] == '#')
			{
				int xOffset = col - xStart;
				int yOffset = row - yStart;
				int divisor = std::gcd(abs(xOffset), abs(yOffset));
				ObscureAsteroid(field, xStart, yStart, xOffset/divisor, yOffset/divisor, divisor+1);
			}
		}
	}
}

std::optional<Coord> BurnAsteroid(std::vector<std::vector<char>>& field, int xStart, int yStart, int xOffset, int yOffset, int multiple)
{
	std::optional<Coord> ret = std::nullopt;
	int width = field[0].size();
	int height = field.size();
	int xPos = xStart + xOffset * multiple;
	int yPos = yStart + yOffset * multiple;
	if (xPos < width && xPos >= 0 && yPos < height && yPos >= 0)
	{
		if (field[yPos][xPos] == '#')
		{
			Coord retObj;
			retObj.x = xPos;
			retObj.y = yPos;
			ret = retObj;
			field[yPos][xPos] = '.';
			return ret;
		}
		else
			return BurnAsteroid(field, xStart, yStart, xOffset, yOffset, multiple + 1);
	}
	return ret;
}

void FireLaser(std::vector<std::vector<char>>& field, int xStart, int yStart)
{
	int width = field[0].size();
	int height = field.size();
	std::set<Coord> laserOrder;

	for (int row = 0; row < height; row++)
	{
		for (int col = 0; col < width; col++)
		{
			if (!(col == xStart && row == yStart))
			{
				Coord offset;
				offset.x = col - xStart;
				offset.y = row - yStart;
				laserOrder.insert(offset);
			}
		}
	}

	int hits = 0;
	for (Coord offset : laserOrder)
	{
		int divisor = std::gcd(abs(offset.x), abs(offset.y));
		if (auto burned = BurnAsteroid(field, xStart, yStart, offset.x / divisor, offset.y / divisor, 1); burned != std::nullopt)
		{
			hits++;
			if (hits == 200)
				std::cout << burned.value().x << " " << burned.value().y;
		}
	}
}

int main()
{
	std::vector<std::vector<char>> input;

	std::ifstream fileIn("input.txt");
	std::string line;
	while (fileIn >> line)
	{
		input.push_back(std::vector<char>(line.begin(), line.end()));
	}

	int width = input[0].size();
	int height = input.size();

	int best = 0;
	int bestX;
	int bestY;

	for (int row = 0; row < height; row++)
	{
		for (int col = 0; col < width; col++)
		{
			auto field = input;
			CheckAsteroid(field, col, row);
			int count = CountRemaining(field);
			if (count > best)
			{
				best = count;
				bestX = col;
				bestY = row;
			}
		}
	}

	std::cout << "(" << bestX << "," << bestY << "): " << best - 1 << std::endl;
	auto field = input;
	CheckAsteroid(field, bestX, bestY);

	for (int row = 0; row < height; row++)
	{
		for (int col = 0; col < width; col++)
		{
			if (col == bestX && row == bestY)
				std::cout << '@';
			else
				std::cout << field[row][col];
		}
		std::cout << std::endl;
	}

	field = input;
	FireLaser(field, bestX, bestY);
}

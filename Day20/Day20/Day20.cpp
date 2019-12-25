// Day20.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <queue>
#include <string>
#include <numeric>
#include <cassert>

using TunnelMap_t = std::map<std::pair<int, int>, int>;

std::map<std::pair<int, int>, std::pair<std::string, bool>> GetPortalLocations(const std::vector<std::string>& map)
{
	std::map<std::pair<int, int>, std::pair<std::string, bool>> ret;
	for (int y = 0; y < map.size() - 1; y++)
	{
		for (int x = 0; x < map[y].size() - 1; x++)
		{
			char c1 = map[y][x];
			if (c1 >= 'A' && c1 <= 'Z')
			{
				char c2 = ' ';
				char cr = map[y][x + 1];
				if (cr >= 'A' && cr <= 'Z')
				{
					c2 = cr;
				}

				char cd = map[y + 1][x];
				if (cd >= 'A' && cd <= 'Z')
				{
					c2 = cd;
				}

				if (c2 != ' ')
				{
					bool dir;
					std::string label = { c1, c2 };
					int u = y - 1;
					int d = y + 2;
					int l = x - 1;
					int r = x + 2;
					std::pair<int, int> point = { x, y };
					if (u >= 0 && map[u][x] == '.')
					{
						point.second = u;
						dir = u != map.size() - 3;
					}
					else if (d < map.size() && map[d][x] == '.')
					{
						point.second = d;
						dir = d != 2;
					}
					else if (l >= 0 && map[y][l] == '.')
					{
						point.first = l;
						dir = l != map[y].size() - 3;
					}
					else if (r < map[y].size() && map[y][r] == '.')
					{
						point.first = r;
						dir = r != 2;
					}

					assert(point.first != x || point.second != y);

					ret.insert({ point, { label, dir} });
				}
			}
		}
	}
	return ret;
}

int main()
{
	std::vector<std::string> baseMap;
	std::ifstream fileIn("input.txt");
	for (std::string line; std::getline(fileIn, line); )
	{
		baseMap.push_back(line);
	}

	TunnelMap_t tunnelMap;

	for (int y = 2; y < baseMap.size() - 2; y++)
	{
		for (int x = 2; x < baseMap[y].size() - 2; x++)
		{
			if (baseMap[y][x] == '.')
				tunnelMap.insert({ {x, y}, std::numeric_limits<int>::max() });
		}
	}

	auto mapCopy = tunnelMap;

	auto posToLabels = GetPortalLocations(baseMap);
	std::map<std::pair<std::string, bool>, std::pair<int, int>> lablesToPos;
	for (auto item : posToLabels)
	{
		lablesToPos.insert({ item.second, item.first });
	}

	std::pair<int, int> start = lablesToPos.find({ "AA", false })->second;
	tunnelMap[start] = 0;

	std::priority_queue<std::pair<int, int>> pointQueue;
	pointQueue.push(start);

	while (!pointQueue.empty())
	{
		auto point = pointQueue.top();
		pointQueue.pop();

		int value = tunnelMap[point];

		std::pair<int, int> u = { point.first, point.second - 1 };
		if (tunnelMap.find(u) != tunnelMap.end())
		{
			if (tunnelMap[u] > value + 1)
			{
				tunnelMap[u] = value + 1;
				pointQueue.push(u);
			}
		}

		std::pair<int, int> d = { point.first, point.second + 1 };
		if (tunnelMap.find(d) != tunnelMap.end())
		{
			if (tunnelMap[d] > value + 1)
			{
				tunnelMap[d] = value + 1;
				pointQueue.push(d);
			}
		}

		std::pair<int, int> l = { point.first - 1, point.second };
		if (tunnelMap.find(l) != tunnelMap.end())
		{
			if (tunnelMap[l] > value + 1)
			{
				tunnelMap[l] = value + 1;
				pointQueue.push(l);
			}
		}

		std::pair<int, int> r = { point.first + 1, point.second };
		if (tunnelMap.find(r) != tunnelMap.end())
		{
			if (tunnelMap[r] > value + 1)
			{
				tunnelMap[r] = value + 1;
				pointQueue.push(r);
			}
		}

		if (posToLabels.find(point) != posToLabels.end())
		{
			auto labelDir = posToLabels[point];
			labelDir.second = !labelDir.second;
			auto otherPoint = lablesToPos.find(labelDir);
			if (otherPoint != lablesToPos.end() && tunnelMap[otherPoint->second] > value + 1)
			{
				tunnelMap[otherPoint->second] = value + 1;
				pointQueue.push(otherPoint->second);
			}
		}
	}

	std::cout << tunnelMap[lablesToPos.find({ "ZZ", false })->second] << std::endl;

	/////////////////////////////////////////////////////////////

	std::vector<TunnelMap_t> recursiveTunnelMap(1, mapCopy);
	int currentLevel = 0;

	recursiveTunnelMap[currentLevel][start] = 0;

	auto cmp = [&](std::pair<std::pair<int, int>, int> lhs, std::pair<std::pair<int, int>, int> rhs) -> bool
	{
		return recursiveTunnelMap[lhs.second][lhs.first] > recursiveTunnelMap[rhs.second][rhs.first];
	};

	std::priority_queue<std::pair<std::pair<int, int>, int>, std::vector<std::pair<std::pair<int, int>, int>>, decltype(cmp)> pointQueue2(cmp);
	pointQueue2.push({ start, currentLevel });

	while (!pointQueue2.empty())
	{
		auto point = pointQueue2.top().first;
		currentLevel = pointQueue2.top().second;
		pointQueue2.pop();

		int value = recursiveTunnelMap[currentLevel][point];

		std::pair<int, int> u = { point.first, point.second - 1 };
		if (recursiveTunnelMap[currentLevel].find(u) != recursiveTunnelMap[currentLevel].end())
		{
			if (recursiveTunnelMap[currentLevel][u] > value + 1)
			{
				recursiveTunnelMap[currentLevel][u] = value + 1;
				pointQueue2.push({ u, currentLevel });
			}
		}

		std::pair<int, int> d = { point.first, point.second + 1 };
		if (recursiveTunnelMap[currentLevel].find(d) != recursiveTunnelMap[currentLevel].end())
		{
			if (recursiveTunnelMap[currentLevel][d] > value + 1)
			{
				recursiveTunnelMap[currentLevel][d] = value + 1;
				pointQueue2.push({ d, currentLevel });
			}
		}

		std::pair<int, int> l = { point.first - 1, point.second };
		if (recursiveTunnelMap[currentLevel].find(l) != recursiveTunnelMap[currentLevel].end())
		{
			if (recursiveTunnelMap[currentLevel][l] > value + 1)
			{
				recursiveTunnelMap[currentLevel][l] = value + 1;
				pointQueue2.push({ l, currentLevel });
			}
		}

		std::pair<int, int> r = { point.first + 1, point.second };
		if (recursiveTunnelMap[currentLevel].find(r) != recursiveTunnelMap[currentLevel].end())
		{
			if (recursiveTunnelMap[currentLevel][r] > value + 1)
			{
				recursiveTunnelMap[currentLevel][r] = value + 1;
				pointQueue2.push({ r, currentLevel });
			}
		}

		if (posToLabels.find(point) != posToLabels.end())
		{
			auto labelDir = posToLabels[point];
			int portalLevel = currentLevel;
			portalLevel += labelDir.second ? 1 : -1;
			if (portalLevel == -1 && labelDir.first == "ZZ")
			{
				std::cout << recursiveTunnelMap[0][point];
				return 0;
			}

			if (portalLevel >= 0)
			{
				labelDir.second = !labelDir.second;
				auto otherPoint = lablesToPos.find(labelDir);
				if (portalLevel >= recursiveTunnelMap.size())
					recursiveTunnelMap.push_back(mapCopy);
				if (otherPoint != lablesToPos.end() && recursiveTunnelMap[portalLevel][otherPoint->second] > value + 1)
				{
					recursiveTunnelMap[portalLevel][otherPoint->second] = value + 1;
					pointQueue2.push({ otherPoint->second, portalLevel });
				}
			}
		}
	}
}

// Day24.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <memory>
#include <cassert>

struct Tile
{
	std::set<std::shared_ptr<Tile>> neightbours;
	bool alive = false;
	bool nextState = false;
};

struct Layer
{
	std::shared_ptr<Layer> outside = nullptr;
	std::map<std::pair<int, int>, std::shared_ptr<Tile>> tiles;
	std::shared_ptr<Layer> inside = nullptr;
};

const std::map<std::pair<int, int>, std::shared_ptr<Tile>> emptyLayer =
{
	{{0, 0}, nullptr},
	{{1, 0}, nullptr},
	{{2, 0}, nullptr},
	{{3, 0}, nullptr},
	{{4, 0}, nullptr},
	{{0, 1}, nullptr},
	{{1, 1}, nullptr},
	{{2, 1}, nullptr},
	{{3, 1}, nullptr},
	{{4, 1}, nullptr},
	{{0, 2}, nullptr},
	{{1, 2}, nullptr},
	{{3, 2}, nullptr},
	{{4, 2}, nullptr},
	{{0, 3}, nullptr},
	{{1, 3}, nullptr},
	{{2, 3}, nullptr},
	{{3, 3}, nullptr},
	{{4, 3}, nullptr},
	{{0, 4}, nullptr},
	{{1, 4}, nullptr},
	{{2, 4}, nullptr},
	{{3, 4}, nullptr},
	{{4, 4}, nullptr},
};

std::uint64_t GetBioCount(const std::vector<std::vector<bool>>& map)
{
	std::uint64_t count = 0;
	for (size_t y = 0; y < map.size(); y++)
	{
		for (size_t x = 0; x < map[y].size(); x++)
		{
			size_t power = y * map[0].size() + x;
			if (map[y][x])
				count += pow(2, power);
		}
	}

	return count;
}

void PrintMap(const std::vector<std::vector<bool>>& map)
{
	for (auto row : map)
	{
		for (bool point : row)
		{
			std::cout << (point ? "#" : ".");
		}
		std::cout << std::endl;
	}
}

void NextGeneration(std::vector<std::vector<bool>>& map)
{
	auto nextGen = map;
	for (size_t y = 0; y < map.size(); y++)
	{
		for (size_t x = 0; x < map[y].size(); x++)
		{
			int count = 0;
			if (y > 0 && map[y - 1][x])
				count++;
			if (y < map.size() - 1 && map[y + 1][x])
				count++;
			if (x > 0 && map[y][x - 1])
				count++;
			if (x < map[y].size() - 1 && map[y][x + 1])
				count++;

			if (map[y][x] && count != 1)
				nextGen[y][x] = false;

			if (!map[y][x] && (count == 1 || count == 2))
				nextGen[y][x] = true;
		}
	}

	map.swap(nextGen);
}

void InitializeInsideLayerConnections(std::shared_ptr<Layer> layer)
{
	assert(layer->inside != nullptr);

	layer->tiles[{2, 1}]->neightbours.insert(layer->inside->tiles[{0, 0}]);
	layer->tiles[{2, 1}]->neightbours.insert(layer->inside->tiles[{1, 0}]);
	layer->tiles[{2, 1}]->neightbours.insert(layer->inside->tiles[{2, 0}]);
	layer->tiles[{2, 1}]->neightbours.insert(layer->inside->tiles[{3, 0}]);
	layer->tiles[{2, 1}]->neightbours.insert(layer->inside->tiles[{4, 0}]);

	layer->tiles[{1, 2}]->neightbours.insert(layer->inside->tiles[{0, 0}]);
	layer->tiles[{1, 2}]->neightbours.insert(layer->inside->tiles[{0, 1}]);
	layer->tiles[{1, 2}]->neightbours.insert(layer->inside->tiles[{0, 2}]);
	layer->tiles[{1, 2}]->neightbours.insert(layer->inside->tiles[{0, 3}]);
	layer->tiles[{1, 2}]->neightbours.insert(layer->inside->tiles[{0, 4}]);

	layer->tiles[{2, 3}]->neightbours.insert(layer->inside->tiles[{0, 4}]);
	layer->tiles[{2, 3}]->neightbours.insert(layer->inside->tiles[{1, 4}]);
	layer->tiles[{2, 3}]->neightbours.insert(layer->inside->tiles[{2, 4}]);
	layer->tiles[{2, 3}]->neightbours.insert(layer->inside->tiles[{3, 4}]);
	layer->tiles[{2, 3}]->neightbours.insert(layer->inside->tiles[{4, 4}]);

	layer->tiles[{3, 2}]->neightbours.insert(layer->inside->tiles[{4, 0}]);
	layer->tiles[{3, 2}]->neightbours.insert(layer->inside->tiles[{4, 1}]);
	layer->tiles[{3, 2}]->neightbours.insert(layer->inside->tiles[{4, 2}]);
	layer->tiles[{3, 2}]->neightbours.insert(layer->inside->tiles[{4, 3}]);
	layer->tiles[{3, 2}]->neightbours.insert(layer->inside->tiles[{4, 4}]);
}

void InitializeOutsideLayerConnections(std::shared_ptr<Layer> layer)
{
	assert(layer->outside != nullptr);

	layer->tiles[{0, 0}]->neightbours.insert(layer->outside->tiles[{2, 1}]);
	layer->tiles[{1, 0}]->neightbours.insert(layer->outside->tiles[{2, 1}]);
	layer->tiles[{2, 0}]->neightbours.insert(layer->outside->tiles[{2, 1}]);
	layer->tiles[{3, 0}]->neightbours.insert(layer->outside->tiles[{2, 1}]);
	layer->tiles[{4, 0}]->neightbours.insert(layer->outside->tiles[{2, 1}]);

	layer->tiles[{0, 0}]->neightbours.insert(layer->outside->tiles[{1, 2}]);
	layer->tiles[{0, 1}]->neightbours.insert(layer->outside->tiles[{1, 2}]);
	layer->tiles[{0, 2}]->neightbours.insert(layer->outside->tiles[{1, 2}]);
	layer->tiles[{0, 3}]->neightbours.insert(layer->outside->tiles[{1, 2}]);
	layer->tiles[{0, 4}]->neightbours.insert(layer->outside->tiles[{1, 2}]);

	layer->tiles[{0, 4}]->neightbours.insert(layer->outside->tiles[{2, 3}]);
	layer->tiles[{1, 4}]->neightbours.insert(layer->outside->tiles[{2, 3}]);
	layer->tiles[{2, 4}]->neightbours.insert(layer->outside->tiles[{2, 3}]);
	layer->tiles[{3, 4}]->neightbours.insert(layer->outside->tiles[{2, 3}]);
	layer->tiles[{4, 4}]->neightbours.insert(layer->outside->tiles[{2, 3}]);

	layer->tiles[{4, 0}]->neightbours.insert(layer->outside->tiles[{3, 2}]);
	layer->tiles[{4, 1}]->neightbours.insert(layer->outside->tiles[{3, 2}]);
	layer->tiles[{4, 2}]->neightbours.insert(layer->outside->tiles[{3, 2}]);
	layer->tiles[{4, 3}]->neightbours.insert(layer->outside->tiles[{3, 2}]);
	layer->tiles[{4, 4}]->neightbours.insert(layer->outside->tiles[{3, 2}]);
}

void InitializeTileConnections(std::shared_ptr<Layer> layer)
{
	for (auto& tile : layer->tiles)
	{
		auto point = tile.first;
		auto up = point;
		up.second--;
		if (layer->tiles.find(up) != layer->tiles.end())
		{
			tile.second->neightbours.insert(layer->tiles[up]);
		}

		auto down = point;
		down.second++;
		if (layer->tiles.find(down) != layer->tiles.end())
		{
			tile.second->neightbours.insert(layer->tiles[down]);
		}

		auto left = point;
		left.first--;
		if (layer->tiles.find(left) != layer->tiles.end())
		{
			tile.second->neightbours.insert(layer->tiles[left]);
		}

		auto right = point;
		right.first++;
		if (layer->tiles.find(right) != layer->tiles.end())
		{
			tile.second->neightbours.insert(layer->tiles[right]);
		}
	}

	if (layer->inside != nullptr && layer->inside->outside == nullptr)
	{
		layer->inside->outside = layer;
		InitializeInsideLayerConnections(layer);
		InitializeOutsideLayerConnections(layer->inside);
	}

	if (layer->outside != nullptr && layer->outside->inside == nullptr)
	{
		layer->outside->inside = layer;
		InitializeOutsideLayerConnections(layer);
		InitializeInsideLayerConnections(layer->outside);
	}
}

void InitializeLayer(std::shared_ptr<Layer> layer)
{
	layer->tiles = emptyLayer;
	for (auto& tile : layer->tiles)
	{
		tile.second = std::make_shared<Tile>();
	}

	InitializeTileConnections(layer);
}

int GetAliveNeighbourCount(std::shared_ptr<Tile> tile)
{
	int count = 0;
	for (auto neighbour : tile->neightbours)
	{
		if (neighbour->alive)
			count++;
	}

	return count;
}

void GetNextGeneration(std::shared_ptr<Layer> layer)
{
	for (auto& tile : layer->tiles)
	{
		int count = GetAliveNeighbourCount(tile.second);

		tile.second->nextState = tile.second->alive;

		if (tile.second->alive && count != 1)
			tile.second->nextState = false;

		if (!tile.second->alive && (count == 1 || count == 2))
			tile.second->nextState = true;
	}

	if (layer->inside != nullptr)
		GetNextGeneration(layer->inside);

	for (auto& tile : layer->tiles)
	{
		tile.second->alive = tile.second->nextState;
	}
}

std::uint64_t GetLayerAliveCount(std::shared_ptr<Layer> layer)
{
	std::uint64_t count = 0;

	for (auto tile : layer->tiles)
	{
		if (tile.second->alive)
			count++;
	}

	return count;
}

std::uint64_t GetTotalAliveCount(std::shared_ptr<Layer> layer)
{
	std::uint64_t count = GetLayerAliveCount(layer);
	
	if (layer->inside != nullptr)
		count += GetTotalAliveCount(layer->inside);

	return count;
}

void DrawLayer(std::shared_ptr<Layer> layer)
{
	std::vector<bool> row(5, false);
	std::vector<std::vector<bool>> vecLayer(5, row);

	for (auto& tile : layer->tiles)
	{
		vecLayer[tile.first.second][tile.first.first] = tile.second->alive;
	}

	for (auto row : vecLayer)
	{
		for (bool tile : row)
		{
			std::cout << (tile ? "#" : ".");
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

void DrawAllLayers(std::shared_ptr<Layer> layer)
{
	DrawLayer(layer);

	if (layer->inside != nullptr)
		DrawAllLayers(layer->inside);
}

int main()
{
	std::set<std::uint64_t> previousCounts;
	std::uint64_t nextCount;

	//Easier to hard code it than read from file
	std::vector<std::vector<bool>> map;
	map.assign(
	{
		{false, true, false, true, true},
		{false, true, true, true, false},
		{true, true, false, true, false},
		{true, true, true, true, false},
		{true, true, false, true, true}
	});

	nextCount = GetBioCount(map);
	PrintMap(map);
	std::cout << nextCount << std::endl << std::endl;

	do
	{
		previousCounts.insert(nextCount);
		NextGeneration(map);
		nextCount = GetBioCount(map);
		//PrintMap(map);
		//std::cout << nextCount << std::endl << std::endl;
	} while (previousCounts.find(nextCount) == previousCounts.end());

	std::cout << nextCount << std::endl;

	////////////////////////////////////////////////////////////////////////////

	std::shared_ptr<Layer> startingLayer = std::make_shared<Layer>();
	InitializeLayer(startingLayer);
	std::shared_ptr<Layer> top = std::make_shared<Layer>();
	top->inside = startingLayer;
	InitializeLayer(top);
	std::shared_ptr<Layer> bottom = std::make_shared<Layer>();
	bottom->outside = startingLayer;
	InitializeLayer(bottom);

	startingLayer->tiles[{1, 0}]->alive = true;
	startingLayer->tiles[{3, 0}]->alive = true;
	startingLayer->tiles[{4, 0}]->alive = true;
	startingLayer->tiles[{1, 1}]->alive = true;
	startingLayer->tiles[{2, 1}]->alive = true;
	startingLayer->tiles[{3, 1}]->alive = true;
	startingLayer->tiles[{0, 2}]->alive = true;
	startingLayer->tiles[{1, 2}]->alive = true;
	startingLayer->tiles[{3, 2}]->alive = true;
	startingLayer->tiles[{0, 3}]->alive = true;
	startingLayer->tiles[{1, 3}]->alive = true;
	startingLayer->tiles[{2, 3}]->alive = true;
	startingLayer->tiles[{3, 3}]->alive = true;
	startingLayer->tiles[{0, 4}]->alive = true;
	startingLayer->tiles[{1, 4}]->alive = true;
	startingLayer->tiles[{3, 4}]->alive = true;
	startingLayer->tiles[{4, 4}]->alive = true;

	//startingLayer->tiles[{4, 0}]->alive = true;
	//startingLayer->tiles[{0, 1}]->alive = true;
	//startingLayer->tiles[{3, 1}]->alive = true;
	//startingLayer->tiles[{0, 2}]->alive = true;
	//startingLayer->tiles[{3, 2}]->alive = true;
	//startingLayer->tiles[{4, 2}]->alive = true;
	//startingLayer->tiles[{2, 3}]->alive = true;
	//startingLayer->tiles[{0, 4}]->alive = true;

	DrawLayer(startingLayer);
	std::cout << "-------------------" << std::endl;

	for (int i = 0; i < 200; i++)
	{
		GetNextGeneration(top);

		//DrawAllLayers(top);
		//std::cout << "-------------------" << std::endl;

		if (GetLayerAliveCount(top) > 0)
		{
			std::shared_ptr<Layer> nextTop = std::make_shared<Layer>();
			nextTop->inside = top;
			InitializeLayer(nextTop);
			top = nextTop;
		}

		if (GetLayerAliveCount(bottom) > 0)
		{
			std::shared_ptr<Layer> nextBottom = std::make_shared<Layer>();
			nextBottom->outside = bottom;
			InitializeLayer(nextBottom);
			bottom = nextBottom;
		}
	}

//	DrawAllLayers(top);

	std::cout << GetTotalAliveCount(top) << std::endl;
}

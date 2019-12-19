#pragma once

#include <cstdint>
#include <map>

class RepairDroidController
{
public:
	enum class Direction : std::int64_t
	{
		North = 1,
		South,
		West,
		East,
	};

	RepairDroidController() = default;
	~RepairDroidController() = default;

	std::int64_t CommandMovement();
	void RecieveStatus(std::int64_t response);

	void Draw();

	int GetFillTime();

private:

	void TurnLeft();
	void Traverse(std::pair<int, int> nextPos, int nextValue, std::map<std::pair<int, int>, int>& maze);

	std::pair<std::pair<int, int>, int> m_CurrentPos = { {0, 0}, 0 };
	std::pair<int, int> m_NextPos;
	std::pair<int, int> m_Oxygen;

	bool m_OxygenFound = false;
	bool m_EntranceFound = false;

	std::map<std::pair<int, int>, int> m_Map;

	Direction m_Facing = Direction::North;
};

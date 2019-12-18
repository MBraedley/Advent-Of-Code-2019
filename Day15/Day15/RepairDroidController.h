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
	void RecieveStatus(std::int64_t);

private:

	std::pair<std::pair<int, int>, int> m_CurrentPos = { {0, 0}, 0 };

	std::map<std::pair<int, int>, int> m_Map;

	Direction m_LastDir = Direction::West;	//Set it up to move north first
};

#include "RepairDroidController.h"

std::int64_t RepairDroidController::CommandMovement()
{
	Direction nextMove;
	switch (m_LastDir)
	{
	case RepairDroidController::Direction::North:
		nextMove = Direction::East;
		break;
	case RepairDroidController::Direction::South:
		nextMove = Direction::West;
		break;
	case RepairDroidController::Direction::West:
		nextMove = Direction::North;
		break;
	case RepairDroidController::Direction::East:
		nextMove = Direction::South;
		break;
	default:
		break;
	}
	m_LastDir = nextMove;
	return static_cast<std::int64_t>(nextMove);
}

void RepairDroidController::RecieveStatus(std::int64_t)
{
}

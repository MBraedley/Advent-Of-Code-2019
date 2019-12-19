#include "RepairDroidController.h"

#include <iostream>
#include <vector>
#include <numeric>

std::int64_t RepairDroidController::CommandMovement()
{
    if (m_OxygenFound && m_EntranceFound)
        return 0;

    m_NextPos = m_CurrentPos.first;
    Direction moveDir;
	switch (m_Facing)
	{
    case RepairDroidController::Direction::North:
        m_NextPos.first++;
        moveDir = Direction::East;
        break;
    case RepairDroidController::Direction::South:
        m_NextPos.first--;
        moveDir = Direction::West;
        break;
    case RepairDroidController::Direction::West:
        m_NextPos.second--;
        moveDir = Direction::North;
        break;
    case RepairDroidController::Direction::East:
        m_NextPos.second++;
        moveDir = Direction::South;
        break;
    default:
        break;
	}

    auto iter = m_Map.find(m_NextPos);
    if (iter == m_Map.end() || iter->second >= 0)
    {
        m_Facing = moveDir;
        return static_cast<std::int64_t>(m_Facing);
    }

    TurnLeft();

    return CommandMovement();
}

void RepairDroidController::RecieveStatus(std::int64_t response)
{
    auto nextPos = m_Map.find(m_NextPos);
    switch (response)
    {
    case 0:
        TurnLeft();
        TurnLeft();
        m_Map.insert({ m_NextPos, -1 });
        return;
    case 1:
        m_CurrentPos.first = m_NextPos;
        if (nextPos == m_Map.end() || m_CurrentPos.second < nextPos->second)
        {
            m_CurrentPos.second++;
            m_Map.insert(m_CurrentPos);
        }
        else
            m_CurrentPos.second = nextPos->second;
        if (m_CurrentPos.first == std::pair<int, int>(0, 0) && m_OxygenFound)
            m_EntranceFound = true;
        return;
    case 2:
        m_CurrentPos.first = m_NextPos;
        if (nextPos == m_Map.end() || m_CurrentPos.second < nextPos->second)
        {
            m_CurrentPos.second++;
            m_Map.insert(m_CurrentPos);
        }
        else
            m_CurrentPos.second = nextPos->second;
        std::cout << m_CurrentPos.second << std::endl;
        m_OxygenFound = true;
        m_Oxygen = m_CurrentPos.first;
    default:
        break;
    }
}

void RepairDroidController::Draw()
{
    std::int64_t minX = std::numeric_limits<std::int64_t>::max();
    std::int64_t minY = std::numeric_limits<std::int64_t>::max();
    std::int64_t maxX = std::numeric_limits<std::int64_t>::min();
    std::int64_t maxY = std::numeric_limits<std::int64_t>::min();

    for (auto square : m_Map)
    {
        auto pos = square.first;

        if (pos.first < minX)
            minX = pos.first;
        if (pos.second < minY)
            minY = pos.second;
        if (pos.first > maxX)
            maxX = pos.first;
        if (pos.second > maxY)
            maxY = pos.second;
    }

    std::vector<char> row(maxX - minX + 1, '@');
    std::vector<std::vector<char>> hallways(maxY - minY + 1, row);

    for (auto square : m_Map)
    {
        hallways[square.first.second - minY][square.first.first - minX] = square.second == -1 ? '#' : ' ';
    }

    hallways[m_CurrentPos.first.second - minY][m_CurrentPos.first.first - minX] = 'O';

    for (auto pRow : hallways)
    {
        for (std::int8_t square : pRow)
        {
            std::cout << square;
        }
        std::cout << std::endl;
    }
}

int RepairDroidController::GetFillTime()
{
    auto maze = m_Map;
    for (auto& pos : maze)
    {
        if (pos.second > 0)
            pos.second = std::numeric_limits<int>::max();
    }

    Traverse(m_Oxygen, 0, maze);

    int longest = 0;

    for (auto& pos : maze)
    {
        if (pos.second > longest)
            longest = pos.second;
    }

    std::cout << longest << std::endl;

    return longest;
}

void RepairDroidController::TurnLeft()
{
    switch (m_Facing)
    {
    case RepairDroidController::Direction::North:
        m_Facing = Direction::West;
        break;
    case RepairDroidController::Direction::South:
        m_Facing = Direction::East;
        break;
    case RepairDroidController::Direction::West:
        m_Facing = Direction::South;
        break;
    case RepairDroidController::Direction::East:
        m_Facing = Direction::North;
        break;
    default:
        break;
    }
}

void RepairDroidController::Traverse(std::pair<int, int> nextPos, int nextValue, std::map<std::pair<int, int>, int>& maze)
{
    if (maze.find(nextPos) != maze.end() && maze[nextPos] > nextValue)
    {
        maze[nextPos] = nextValue;

        nextValue++;
        int x = nextPos.first;
        int y = nextPos.second;

        std::pair<int, int> up(x, y - 1);
        std::pair<int, int> down(x, y + 1);
        std::pair<int, int> left(x -1, y);
        std::pair<int, int> right(x + 1, y);

        Traverse(up, nextValue, maze);
        Traverse(down, nextValue, maze);
        Traverse(left, nextValue, maze);
        Traverse(right, nextValue, maze);
    }
}

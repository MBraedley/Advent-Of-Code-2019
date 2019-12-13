#include "PainterRobot.h"

#include <vector>
#include <cassert>
#include <iostream>

void PainterRobot::Input(std::int64_t value)
{
	if (m_DoPaint)
	{
		m_Hull[m_CurrentPos] = value;
	}
	else
	{
		if (value == 0)
		{
			switch (m_Facing)
			{
			case Direction::UP:
				m_Facing = Direction::LEFT;
				break;
			case Direction::RIGHT:
				m_Facing = Direction::UP;
				break;
			case Direction::DOWN:
				m_Facing = Direction::RIGHT;
				break;
			case Direction::LEFT:
				m_Facing = Direction::DOWN;
				break;
			default:
				break;
			}
		}
		else
		{
			assert(value == 1);
			switch (m_Facing)
			{
			case Direction::UP:
				m_Facing = Direction::RIGHT;
				break;
			case Direction::RIGHT:
				m_Facing = Direction::DOWN;
				break;
			case Direction::DOWN:
				m_Facing = Direction::LEFT;
				break;
			case Direction::LEFT:
				m_Facing = Direction::UP;
				break;
			default:
				break;
			}
		}

		switch (m_Facing)
		{
		case Direction::UP:
			m_CurrentPos.second--;
			break;
		case Direction::RIGHT:
			m_CurrentPos.first++;
			break;
		case Direction::DOWN:
			m_CurrentPos.second++;
			break;
		case Direction::LEFT:
			m_CurrentPos.first--;
			break;
		default:
			break;
		}
	}

	m_DoPaint = !m_DoPaint;
}

std::int64_t PainterRobot::Output()
{
	std::int64_t paint = 0;
	if (m_Hull.find(m_CurrentPos) != m_Hull.end())
		paint = m_Hull[m_CurrentPos];
	return paint;
}

void PainterRobot::Draw()
{
	std::int64_t minX = std::numeric_limits<std::int64_t>::max();
	std::int64_t minY = std::numeric_limits<std::int64_t>::max();
	std::int64_t maxX = std::numeric_limits<std::int64_t>::min();
	std::int64_t maxY = std::numeric_limits<std::int64_t>::min();

	for (auto square : m_Hull)
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

	std::vector<std::int8_t> row(maxX - minX + 1);
	std::vector<std::vector<std::int8_t>> paintedHull(maxY - minY + 1, row);

	for (auto square : m_Hull)
	{
		paintedHull[square.first.second - minY][square.first.first - minX] = static_cast<std::int8_t>(square.second);
	}

	for (auto pRow : paintedHull)
	{
		for (std::int8_t square : pRow)
		{
			std::cout << (square == 1 ? '#' : ' ');
		}
		std::cout << std::endl;
	}
}

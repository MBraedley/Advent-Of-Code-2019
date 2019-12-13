#pragma once
#include <map>

enum class Direction
{
	UP,
	RIGHT,
	DOWN,
	LEFT,
};

class PainterRobot
{
public:
	PainterRobot() = default;
	~PainterRobot() = default;

	void Input(std::int64_t value);
	std::int64_t Output();

	void SetStartToWhite() { m_Hull[{0, 0}] = 1; }

	size_t GetNumPaintedPanels() { return m_Hull.size(); }

	void Draw();

private:
	std::map<std::pair<std::int64_t, std::int64_t>, std::int64_t> m_Hull = { { {0, 0}, 0 } };
	bool m_DoPaint = true;

	Direction m_Facing = Direction::UP;
	std::pair<std::int64_t, std::int64_t> m_CurrentPos = { 0, 0 };
};


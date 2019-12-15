#pragma once
#include "IntcodeComputer.h"

#include <stack>
#include <map>

enum class Tiles
{
	Empty,
	Wall,
	Block,
	Paddle,
	Ball,
};

class ArcadeGame
{
public:
    ArcadeGame(IntcodeComputer& computer);
	~ArcadeGame() = default;

	void InputX(std::int64_t input);
	void InputY(std::int64_t input);

	void InputTileId(std::int64_t input);
	void ShowScore(std::int64_t input);

	void RunGame();

	std::int64_t MovePaddle();

	std::uint32_t CountBlocks();

private:
	IntcodeComputer m_Computer;
	std::stack<std::pair<IntcodeComputer, std::int64_t>> m_SaveStates;

	std::map<std::pair<std::int64_t, std::int64_t>, Tiles> m_Board;

	std::int64_t m_LastXInput = 0;
	std::int64_t m_LastYInput = 0;

	std::int64_t m_BestScore = 0;

	std::int64_t m_BallPosX = 0;
	std::int64_t m_PaddlePosX = 0;
};


#include "ArcadeGame.h"

ArcadeGame::ArcadeGame(IntcodeComputer& computer) :
	m_Computer(computer)
{
	m_Computer.SetOutputCallback(std::bind(&ArcadeGame::InputX, this, std::placeholders::_1));
	m_Computer.SetInputCallback(std::bind(&ArcadeGame::MovePaddle, this));
}

void ArcadeGame::InputX(std::int64_t input)
{
	m_LastXInput = input;
	m_Computer.SetOutputCallback(std::bind(&ArcadeGame::InputY, this, std::placeholders::_1));
}

void ArcadeGame::InputY(std::int64_t input)
{
	m_LastYInput = input;
	if (m_LastXInput == -1 && m_LastYInput == 0)
		m_Computer.SetOutputCallback(std::bind(&ArcadeGame::ShowScore, this, std::placeholders::_1));
	else
		m_Computer.SetOutputCallback(std::bind(&ArcadeGame::InputTileId, this, std::placeholders::_1));
}

void ArcadeGame::InputTileId(std::int64_t input)
{
	Tiles tile = static_cast<Tiles>(input);
	m_Board.insert({ {m_LastXInput, m_LastYInput}, tile });
	switch (tile)
	{
	case Tiles::Paddle:
		m_PaddlePosX = m_LastXInput;
		break;
	case Tiles::Ball:
		m_BallPosX = m_LastXInput;
		break;
	case Tiles::Empty:
	case Tiles::Wall:
	case Tiles::Block:
	default:
		break;
	}
	m_Computer.SetOutputCallback(std::bind(&ArcadeGame::InputX, this, std::placeholders::_1));
}

void ArcadeGame::ShowScore(std::int64_t input)
{
	std::cout << "Score: " << input << std::endl;
	if (input > m_BestScore)
		m_BestScore = input;
	m_Computer.SetOutputCallback(std::bind(&ArcadeGame::InputX, this, std::placeholders::_1));
}

void ArcadeGame::RunGame()
{
	m_Computer.RunProgram();
}

std::int64_t ArcadeGame::MovePaddle()
{
	if (m_PaddlePosX < m_BallPosX)
		return 1;
	else if (m_PaddlePosX == m_BallPosX)
		return 0;
	else //if (m_PaddlePosX > m_BallPosX)
		return -1;
}

std::uint32_t ArcadeGame::CountBlocks()
{
	std::uint32_t count = 0;

	for (auto tile : m_Board)
	{
		if (tile.second == Tiles::Block)
			count++;
	}
	return count;
}

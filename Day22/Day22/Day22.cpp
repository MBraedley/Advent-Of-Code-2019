// Day22.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <deque>
#include <sstream>
#include <regex>
#include <cassert>

void DealNewStack(std::deque<std::uint64_t>& deck)
{
	std::deque<std::uint64_t> nextDeck(deck.rbegin(), deck.rend());
	deck.swap(nextDeck);
}

void CutDeck(std::deque<std::uint64_t>& deck, std::int64_t cutPos)
{
	if (cutPos < 0)
		cutPos += deck.size();

	std::deque<std::uint64_t> nextDeck;
	nextDeck.insert(nextDeck.end(), deck.begin() + cutPos, deck.end());
	nextDeck.insert(nextDeck.end(), deck.begin(), deck.begin() + cutPos);
	deck.swap(nextDeck);
}

void DealWithIncrement(std::deque<std::uint64_t>& deck, std::int64_t increment)
{
	std::deque<std::uint64_t> nextDeck(deck.size());

	for (size_t i = 0; i < deck.size(); i++)
	{
		nextDeck[(i * increment) % deck.size()] = deck[i];
	}

	deck.swap(nextDeck);
}

enum class ShuffleType
{
	NewStack,
	Cut,
	Increment,
};

int main()
{
	std::deque<std::pair<ShuffleType, std::int64_t>> instructions;
	std::regex stackRegex("deal into new stack");
	std::regex cutRegex("cut (-?[0-9]+)");
	std::regex incrementRegex("deal with increment ([0-9]+)");

	std::ifstream input("input.txt");

	for (std::string line; std::getline(input, line); )
	{
		std::smatch result;
		std::int64_t value = 0;
		if (std::regex_match(line, stackRegex))
			instructions.push_back({ ShuffleType::NewStack, 0 });
		else if (std::regex_search(line, result, cutRegex))
		{
			assert(result.size() == 2);

			std::stringstream sstrm(result.str(1));
			sstrm >> value;
			instructions.push_back({ ShuffleType::Cut, value });
		}
		else if (std::regex_search(line, result, incrementRegex))
		{
			assert(result.size() == 2);

			std::stringstream sstrm(result.str(1));
			sstrm >> value;
			instructions.push_back({ ShuffleType::Increment, value });
		}
	}

	std::deque<std::uint64_t> deck(10007);
	for (std::uint64_t i = 0; i < deck.size(); i++)
	{
		deck[i] = i;
	}

	for (auto instruction : instructions)
	{
		switch (instruction.first)
		{
		case ShuffleType::NewStack:
			DealNewStack(deck);
			break;
		case ShuffleType::Cut:
			CutDeck(deck, instruction.second);
			break;
		case ShuffleType::Increment:
			DealWithIncrement(deck, instruction.second);
			break;
		default:
			break;
		}
	}

	std::cout << deck[2019] << std::endl;
	for (size_t i = 0; i < deck.size(); i++)
	{
		if (deck[i] == 2019)
			std::cout << i << std::endl;
	}

	////////////////////////////////////////////////////////////////////////////////

	const std::uint64_t deckSize(119315717514047);
	const std::uint64_t iterationCount(101741582076661);
	std::deque<std::uint64_t> deck2;
	for (std::uint64_t i = 0; i < deckSize; i++)
	{
		deck2.push_back(i);
	}

	for (std::uint64_t i = 0; i < iterationCount; i++)
	{
		for (auto instruction : instructions)
		{
			switch (instruction.first)
			{
			case ShuffleType::NewStack:
				DealNewStack(deck2);
				break;
			case ShuffleType::Cut:
				CutDeck(deck2, instruction.second);
				break;
			case ShuffleType::Increment:
				DealWithIncrement(deck2, instruction.second);
				break;
			default:
				break;
			}
		}
	}

	std::cout << deck2[2020] << std::endl;

	return 0;
}

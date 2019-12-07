#pragma once

#include <vector>

class IntcodeComputer
{
public:
	IntcodeComputer() = default;
	explicit IntcodeComputer(std::vector<int>& program);
	~IntcodeComputer() = default;

	void RunProgram();
	std::uint32_t RunInstruction(std::uint32_t ip);

	int GetValue(std::uint32_t location);
	void SetValue(std::uint32_t location, int value);

	std::vector<int> GetProgram() { return m_Program; }

private:
	std::vector<int> m_Program;
	std::uint32_t m_IP = 0;

	bool m_Halted = true;
};
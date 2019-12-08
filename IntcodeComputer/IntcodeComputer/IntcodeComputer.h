#pragma once

#include <vector>
#include <functional>
#include <iostream>

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

	void SetInputCallback(std::function<int(void)> function) { m_InputFunction = function; }
	void SetOutputCallback(std::function<void(int)> function) { m_OutputFunction = function; }

	std::vector<int> GetProgram() { return m_Program; }

private:
	std::vector<int> m_Program;
	std::uint32_t m_IP = 0;

	bool m_Halted = true;

	std::function<int(void)> m_InputFunction = []() -> int
	{
		int input;
		std::cout << "Input value: ";
		std::cin >> input;
		return input;
	};

	std::function<void(int)> m_OutputFunction = [](int output)
	{
		std::cout << "Output value: " << output << std::endl;
	};
};
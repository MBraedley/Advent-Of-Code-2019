#pragma once

#include <map>
#include <vector>
#include <functional>
#include <iostream>

class IntcodeComputer
{
public:
	IntcodeComputer() = default;
	explicit IntcodeComputer(std::vector<std::int64_t>& program);
	~IntcodeComputer() = default;

	static std::vector<std::int64_t> ReadProgram(std::string filename);

	void RunProgram();
	std::uint64_t RunInstruction(std::uint64_t ip);

	std::int64_t GetValue(std::uint64_t location);
	void SetValue(std::uint64_t location, std::int64_t value);

	void SetInputCallback(std::function<std::int64_t(void)> function) { m_InputFunction = function; }
	void SetOutputCallback(std::function<void(std::int64_t)> function) { m_OutputFunction = function; }

	void Reset(std::vector<std::int64_t>& program);

private:
	void LoadProgramIntoMemory(std::vector<int64_t>& program);

	std::map<std::int64_t, std::int64_t> m_Program;
	std::uint64_t m_IP = 0;
	std::int64_t m_RB = 0;

	bool m_Halted = true;

	std::function<std::int64_t(void)> m_InputFunction = []() -> std::int64_t
	{
		std::int64_t input;
		std::cout << "Input value: ";
		std::cin >> input;
		return input;
	};

	std::function<void(std::int64_t)> m_OutputFunction = [](std::int64_t output)
	{
		std::cout << "Output value: " << output << std::endl;
	};
};
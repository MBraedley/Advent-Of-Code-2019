// IntcodeComputer.cpp : Defines the functions for the static library.
//

#include "IntcodeComputer.h"
#include <cassert>

IntcodeComputer::IntcodeComputer(std::vector<std::int64_t>& program)
{
	for (std::uint64_t i = 0; i < program.size(); i++)
	{
		m_Program.insert({ i, program[i] });
	}
}

void IntcodeComputer::RunProgram()
{
	m_Halted = false;
	while (!m_Halted)
	{
		m_IP = RunInstruction(m_IP);
	}
}

std::uint64_t IntcodeComputer::RunInstruction(std::uint64_t ip)
{
	assert(ip < m_Program.size());
	std::int64_t opcode = m_Program[ip] % 100;
	std::int64_t paramMode1 = -1;
	std::int64_t paramMode2 = -1;
	std::int64_t paramMode3 = -1;
	switch (opcode)
	{
	case 1:
	case 2:
	case 7:
	case 8:
		paramMode3 = (m_Program[ip] / 10000) % 10;
	case 5:
	case 6:
		paramMode2 = (m_Program[ip] / 1000) % 10;
	case 3:
	case 4:
	case 9:
		paramMode1 = (m_Program[ip] / 100) % 10;
	default:
		break;
	}

	std::int64_t param1 = 0;
	std::int64_t param2 = 0;
	std::int64_t param3 = 0;

	if (paramMode1 == 0)
		param1 = m_Program[ip + 1];
	else if (paramMode1 == 1)
		param1 = ip + 1;
	else if (paramMode1 == 2)
		param1 = m_Program[ip + 1] + m_RB;

	if (paramMode2 == 0)
		param2 = m_Program[ip + 2];
	else if (paramMode2 == 1)
		param2= ip + 2;
	else if (paramMode2 == 2)
		param2 = m_Program[ip + 2] + m_RB;

	if (paramMode3 == 0)
		param3 = m_Program[ip + 3];
	else if (paramMode3 == 1)
	{
		assert(false);
		param3 = ip + 3;
	}
	else if (paramMode3 == 2)
		param3 = m_Program[ip + 3] + m_RB;

	auto jit = [&ip, param1, param2, this]()
	{
		if (m_Program[param1] > 0)
			ip = m_Program[param2];
		else
			ip += 3;
	};

	auto jif = [&ip, param1, param2, this]()
	{
		if (m_Program[param1] == 0)
			ip = m_Program[param2];
		else
			ip += 3;
	};

	auto lt = [&ip, param1, param2, param3, this]()
	{
		if (m_Program[param1] < m_Program[param2])
			m_Program[param3] = 1;
		else
			m_Program[param3] = 0;
		ip += 4;
	};

	auto eq = [&ip, param1, param2, param3, this]()
	{
		if (m_Program[param1] == m_Program[param2])
			m_Program[param3] = 1;
		else
			m_Program[param3] = 0;
		ip += 4;
	};

	switch (opcode)
	{
	case 1:
		m_Program[param3] = m_Program[param1] + m_Program[param2];
		ip += 4;
		break;
	case 2:
		m_Program[param3] = m_Program[param1] * m_Program[param2];
		ip += 4;
		break;
	case 3:
		m_Program[param1] = m_InputFunction();
		ip += 2;
		break;
	case 4:
		m_OutputFunction(m_Program[param1]);
		ip += 2;
		break;
	case 5:
		jit();
		break;
	case 6:
		jif();
		break;
	case 7:
		lt();
		break;
	case 8:
		eq();
		break;
	case 9:
		m_RB += m_Program[param1];
		ip += 2;
		break;
	case 99:
		m_Halted = true;
		break;
	default:
		assert(false);
	}
	return ip;
}

std::int64_t IntcodeComputer::GetValue(std::uint64_t location)
{
	assert(location < m_Program.size());
	return m_Program[location];
}

void IntcodeComputer::SetValue(std::uint64_t location, std::int64_t value)
{
	assert(location < m_Program.size());
	m_Program[location] = value;
}

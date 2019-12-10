#include "IOConnector.h"
#include <thread>
#include <chrono>

static const std::chrono::microseconds SLEEP_TIME(1);

void IOConnector::SetValue(int input)
{
	while (m_ValueReady)
	{
		std::this_thread::sleep_for(SLEEP_TIME);
	}
	m_Value = input;
	m_ValueReady = true;
}

int IOConnector::GetValue()
{
	int ret = 0;

	while (!m_ValueReady)
	{
		std::this_thread::sleep_for(SLEEP_TIME);
	}
	ret = m_Value;
	m_ValueReady = false;

	return ret;
}

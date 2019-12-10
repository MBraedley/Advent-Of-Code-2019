#pragma once
#include <atomic>
#include <functional>

class IOConnector
{
public:
	IOConnector() = default;
	~IOConnector() = default;

	void SetValue(int input);
	int GetValue();

private:
	std::atomic_bool m_ValueReady = false;
	std::atomic<int> m_Value = 0;
};

#pragma once
#include "IntcodeComputer.h"

#include "readerwriterqueue.h"

#include <memory>
#include <functional>

class IOConnector
{
public:
	IOConnector();
	IOConnector(std::shared_ptr<IntcodeComputer> source, std::shared_ptr<IntcodeComputer> sink);
	~IOConnector() = default;

	void SetValue(int input);
	int GetValue();

private:
	std::unique_ptr<moodycamel::BlockingReaderWriterQueue<int>> m_Values = nullptr;
};

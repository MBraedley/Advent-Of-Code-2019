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

	void SetValue(std::int64_t input);
	std::int64_t GetValue();

private:
	std::unique_ptr<moodycamel::BlockingReaderWriterQueue<std::int64_t>> m_Values = nullptr;
};

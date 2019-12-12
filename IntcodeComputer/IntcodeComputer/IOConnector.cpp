#include "IOConnector.h"
#include <thread>
#include <chrono>

static const std::chrono::microseconds SLEEP_TIME(1);

IOConnector::IOConnector()
{
	m_Values = std::make_unique<moodycamel::BlockingReaderWriterQueue<std::int64_t>>();
}

IOConnector::IOConnector(std::shared_ptr<IntcodeComputer> source, std::shared_ptr<IntcodeComputer> sink)
{
	m_Values = std::make_unique<moodycamel::BlockingReaderWriterQueue<std::int64_t>>();
	source->SetOutputCallback(std::bind(&IOConnector::SetValue, this, std::placeholders::_1));
	sink->SetInputCallback(std::bind(&IOConnector::GetValue, this));
}

void IOConnector::SetValue(std::int64_t input)
{
	m_Values->enqueue(input);
}

std::int64_t IOConnector::GetValue()
{
	std::int64_t ret = 0;

	m_Values->wait_dequeue(ret);

	return ret;
}

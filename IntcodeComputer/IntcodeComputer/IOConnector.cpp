#include "IOConnector.h"
#include <thread>
#include <chrono>

static const std::chrono::microseconds SLEEP_TIME(1);

IOConnector::IOConnector()
{
	m_Values = std::make_unique<moodycamel::BlockingReaderWriterQueue<int>>();
}

IOConnector::IOConnector(std::shared_ptr<IntcodeComputer> source, std::shared_ptr<IntcodeComputer> sink)
{
	m_Values = std::make_unique<moodycamel::BlockingReaderWriterQueue<int>>();
	source->SetOutputCallback(std::bind(&IOConnector::SetValue, this, std::placeholders::_1));
	sink->SetInputCallback(std::bind(&IOConnector::GetValue, this));
}

void IOConnector::SetValue(int input)
{
	m_Values->enqueue(input);
}

int IOConnector::GetValue()
{
	int ret = 0;

	m_Values->wait_dequeue(ret);

	return ret;
}

// Day23.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "IntcodeComputer.h"

#include "readerwriterqueue.h"

#include <iostream>
#include <vector>
#include <functional>
#include <thread>
#include <mutex>
#include <chrono>

int main()
{
	auto program = IntcodeComputer::ReadProgram("input.txt");

	std::vector<IntcodeComputer> nics(50, IntcodeComputer(program));
	std::vector<moodycamel::BlockingReaderWriterQueue<std::int64_t>> inputQueues(50);
	std::vector<moodycamel::BlockingReaderWriterQueue<std::int64_t>> outputQueues(50);
	std::vector<std::thread> queueProcessors;
	std::vector<std::thread> computers;

	std::int64_t natXValue = 0;
	std::int64_t natYValue = 0;
	std::int64_t lastNatYValue = 0;

	std::chrono::system_clock::time_point lastPacketSent = std::chrono::system_clock::now();

	std::atomic_bool startNat = false;

	bool halted = false;

	for (std::int64_t i = 0; i < inputQueues.size(); i++)
	{
		inputQueues[i].enqueue(i);

		nics[i].SetInputCallback([&, i = i]() -> std::int64_t
			{
				std::int64_t value;
				if (inputQueues[i].try_dequeue(value))
				{
					return value;
				}
				else
				{
					return -1;
				}
			});

		nics[i].SetOutputCallback([&, i = i](std::int64_t value)
			{
				lastPacketSent = std::chrono::system_clock::now();
				outputQueues[i].enqueue(value);
			});

		queueProcessors.emplace_back([&, i = i]()
			{
				while (!halted)
				{
					if (outputQueues[i].size_approx() > 0)
					{
						std::int64_t address;
						std::int64_t x;
						std::int64_t y;
						outputQueues[i].wait_dequeue(address);
						outputQueues[i].wait_dequeue(x);
						outputQueues[i].wait_dequeue(y);

						if (address < 50)
						{
							inputQueues[address].enqueue(x);
							inputQueues[address].enqueue(y);
						}

						if (address == 255)
						{
							startNat = true;
							natXValue = x;
							natYValue = y;
						}
					}
					else
						std::this_thread::sleep_for(std::chrono::milliseconds(1));
				}
			});
	}

	for (auto& comp : nics)
		computers.emplace_back(std::bind(&IntcodeComputer::RunProgram, comp));

	while (!startNat)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}

	while (true)
	{
		auto timeSince = std::chrono::system_clock::now() - lastPacketSent;

		if (timeSince > std::chrono::milliseconds(500))
		{
			std::cout << natYValue << std::endl;
			inputQueues[0].enqueue(natXValue);
			inputQueues[0].enqueue(natYValue);

			if (natYValue == lastNatYValue)
				break;
			lastNatYValue = natYValue;
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}

	for (int i = 0; i < nics.size(); i++)
	{
		nics[i].Halt();
	}

	for (auto& thd : computers)
	{
		thd.join();
	}

	halted = true;
	for (auto& thd : queueProcessors)
	{
		thd.join();
	}
}

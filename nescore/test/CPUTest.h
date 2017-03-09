#include "gtest/gtest.h"
#include "CPU.h"
#include "TestMemory.h"

class CPUTest: public ::testing::Test
{
public:
	CPUTest()
	:memory(std::make_shared<TestMemory>()),
	cpu(memory)
	{
		// Execute the reset interrupt
		cpu.step();
	}

	std::shared_ptr<TestMemory> memory;
	nescore::CPU cpu;
};
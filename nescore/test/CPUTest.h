#include "gtest/gtest.h"
#include "CPU.h"
#include "TestMemory.h"

class CPUTest: public ::testing::Test
{
public:
	CPUTest()
	:cpu(memory)
	{
	}

	nescore::CPU cpu;
	TestMemory memory;
};
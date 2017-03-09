#include "gtest/gtest.h"
#include "CPU.h"
#include "NESMemory.h"
#include "ROMFile.h"
#include "NROMCartridge.h"
#include "FilePaths.h"
#include <fstream>
#include <regex>

using namespace nescore;

TEST(CPUTestSuite, testSuite)
{
	// Load the test rom
    std::ifstream nestest(PATH_EXTERNAL "/nestest/nestest.nes", std::ifstream::in | std::ifstream::binary);
    ROMFile file;
    file.loadROM(nestest);
    
    auto cartridge = std::make_shared<NROMCartridge>(std::move(file));
    auto memory = std::make_shared<NESMemory>(cartridge);
    CPU cpu(memory);

	// Load the reference data
	std::ifstream reference(PATH_EXTERNAL "/nestest/nestest.log", std::ifstream::in);
	if (!nestest)
	{
		FAIL();
	}

	// Setup the CPU
	unsigned long numCycles = 0;
	cpu.step(); // Threat the reset interrupt
    cpu.setPC(0xC000); // The manual tests start from 0xC000.

	unsigned int lineNumber = 1;
	std::string line;
    while(std::getline(reference, line))
    {
		// Extract the expected values
		std::regex reg("^([[:xdigit:]]{4}).*A:([[:xdigit:]]{2}) X:([[:xdigit:]]{2}) Y:([[:xdigit:]]{2}) P:([[:xdigit:]]{2}) SP:([[:xdigit:]]{2}) CYC:\\s*([[:xdigit:]]{1,3})$");
		std::smatch matches;

		if(!std::regex_match(line, matches, reg) && matches.size() != 8)
		{
			FAIL();
		}

		WORD pc = std::stoul(matches[1].str(), 0, 16);
		BYTE a = std::stoul(matches[2].str(), 0, 16);
		BYTE x = std::stoul(matches[3].str(), 0, 16);
		BYTE y = std::stoul(matches[4].str(), 0, 16);
		BYTE p = std::stoul(matches[5].str(), 0, 16);
		BYTE sp = std::stoul(matches[6].str(), 0, 16);
		unsigned long cyc = std::stoul(matches[7].str());

		std::cout << "A:" << std::uppercase << std::setfill('0') << std::setw(2) << std::hex << (unsigned int)cpu.getA();
		std::cout << " X:" << std::uppercase << std::setfill('0') << std::setw(2) << std::hex << (unsigned int)cpu.getX();
		std::cout << " Y:" << std::uppercase << std::setfill('0') << std::setw(2) << std::hex << (unsigned int)cpu.getY();
		std::cout << " P:" << std::uppercase << std::setfill('0') << std::setw(2) << std::hex << (unsigned int)cpu.getP();
		std::cout << " SP:" << std::uppercase << std::setfill('0') << std::setw(2) << std::hex << (unsigned int)cpu.getSP();
		std::cout << " CYC:" << std::uppercase << std::setfill(' ') << std::setw(3) << std::dec << (unsigned int)numCycles;
		std::cout << std::endl;

		SCOPED_TRACE(lineNumber);

		// Compare the values
		ASSERT_EQ(pc, cpu.getPC());
		ASSERT_EQ(a, cpu.getA());
		ASSERT_EQ(x, cpu.getX());
		ASSERT_EQ(y, cpu.getY());
		ASSERT_EQ(p, cpu.getP());
		ASSERT_EQ(sp, cpu.getSP());
		ASSERT_EQ(cyc, numCycles);

		// Execute the CPU
		// Note: In the reference file, the cycles are counted per clock ticks.
		//       The runs 3 times faster then the CPU.
		numCycles += (cpu.step() * 3);
		numCycles = numCycles % 341;

		++lineNumber;
    }
}
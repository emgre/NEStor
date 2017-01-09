#include "gtest/gtest.h"
#include "CPU.h"
#include "NESMemory.h"
#include "ROMFile.h"
#include "NROMCartridge.h"
#include "FilePaths.h"
#include <fstream>
#include <memory>

using namespace nescore;

TEST(CPUTestSuite, testSuite)
{
    std::ifstream nestest(PATH_EXTERNAL "/nestest/nestest.nes", std::ifstream::in|std::ifstream::binary);
    auto file = std::make_unique<ROMFile>();
    ROMFile::loadROM(*file, nestest);
    
    NROMCartridge cartridge(std::move(file));
    NESMemory memory(&cartridge);
    CPU cpu(memory);

    cpu.setPC(0xc000);
    for(unsigned int i = 0; i < 20; ++i)
    {
        cpu.executeSingleInstruction();
        std::cout << "A:" << std::uppercase << std::setfill('0') << std::setw(2) << std::hex << (unsigned int)cpu.getA();
        std::cout << " X:" << std::uppercase << std::setfill('0') << std::setw(2) << std::hex << (unsigned int)cpu.getX();
        std::cout << " Y:" << std::uppercase << std::setfill('0') << std::setw(2) << std::hex << (unsigned int)cpu.getY();
        std::cout << " P:" << std::uppercase << std::setfill('0') << std::setw(2) << std::hex << (unsigned int)cpu.getP();
        std::cout << " SP:" << std::uppercase << std::setfill('0') << std::setw(2) << std::hex << (unsigned int)cpu.getSP();
        std::cout << std::endl;
    }
}
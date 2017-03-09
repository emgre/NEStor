#include "CPUTest.h"

using namespace nescore;

TEST_F(CPUTest, jmpAbsolute)
{
	memory->addMemoryBlock(0x8000, { 0x4C, 0x42, 0x21 });
	auto numCycles = cpu.step();

	EXPECT_EQ(3, numCycles);
	EXPECT_EQ(0x2142, cpu.getPC());
}

TEST_F(CPUTest, jmpIndirect)
{
    memory->addMemoryBlock(0x8000, { 0x6C, 0x42, 0x21 });
    memory->addMemoryBlock(0x2142, { 0x76, 0x98});
    auto numCycles = cpu.step();

    EXPECT_EQ(5, numCycles);
    EXPECT_EQ(0x9876, cpu.getPC());
}

TEST_F(CPUTest, jmpIndirectBug)
{
    memory->addMemoryBlock(0x8000, { 0x6C, 0xFF, 0x30 });
    memory->addMemoryBlock(0x30FF, { 0x21, 0x43 });
    memory->addMemoryBlock(0x3000, { 0x98 });
    auto numCycles = cpu.step();

    EXPECT_EQ(5, numCycles);
    EXPECT_EQ(0x9821, cpu.getPC());
}

TEST_F(CPUTest, jsr)
{
    cpu.setPC(0x8042);
	cpu.setSP(0xFF);
    memory->addMemoryBlock(0x8042, { 0x20, 0x21, 0x43 });
    auto numCycles = cpu.step();

    EXPECT_EQ(6, numCycles);
    EXPECT_EQ(0x4321, cpu.getPC());
    EXPECT_EQ(0xFD, cpu.getSP());
    EXPECT_EQ(0x80, memory->read(0x01FF));
    EXPECT_EQ(0x44, memory->read(0x01FE));
}

TEST_F(CPUTest, jsrStackRollover)
{
    cpu.setPC(0x8042);
    cpu.setSP(0x00);
    memory->addMemoryBlock(0x8042, { 0x20, 0x21, 0x43 });
    auto numCycles = cpu.step();

    EXPECT_EQ(6, numCycles);
    EXPECT_EQ(0x4321, cpu.getPC());
    EXPECT_EQ(0xFE, cpu.getSP());
    EXPECT_EQ(0x80, memory->read(0x0100));
    EXPECT_EQ(0x44, memory->read(0x01FF));
}

TEST_F(CPUTest, rts)
{
    cpu.setSP(0xFD);
    memory->addMemoryBlock(0x8000, { 0x60 });
    memory->addMemoryBlock(0x01FE, { 0x20, 0x43 });
    auto numCycles = cpu.step();

    EXPECT_EQ(6, numCycles);
    EXPECT_EQ(0x4321, cpu.getPC());
    EXPECT_EQ(0xFF, cpu.getSP());
}

TEST_F(CPUTest, rtsRollover)
{
    cpu.setSP(0xFF);
    memory->addMemoryBlock(0x8000, { 0x60 });
    memory->addMemoryBlock(0x0100, { 0x20, 0x43 });
    auto numCycles = cpu.step();

    EXPECT_EQ(6, numCycles);
    EXPECT_EQ(0x4321, cpu.getPC());
    EXPECT_EQ(0x01, cpu.getSP());
}
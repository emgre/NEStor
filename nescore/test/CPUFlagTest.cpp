#include "CPUTest.h"

using namespace nescore;

TEST_F(CPUTest, clcNoChange)
{
	cpu.setStatusFlag(CPU::StatusFlag::C, false);

	memory->addMemoryBlock(0x8000, { 0x18 });
	auto numCycles = cpu.step();

	EXPECT_EQ(2, numCycles);
	EXPECT_FALSE(cpu.getStatusFlag(CPU::StatusFlag::C));
}

TEST_F(CPUTest, clcChange)
{
	cpu.setStatusFlag(CPU::StatusFlag::C, true);

    memory->addMemoryBlock(0x8000, { 0x18 });
	auto numCycles = cpu.step();

	EXPECT_EQ(2, numCycles);
	EXPECT_FALSE(cpu.getStatusFlag(CPU::StatusFlag::C));
}

TEST_F(CPUTest, cldNoChange)
{
	cpu.setStatusFlag(CPU::StatusFlag::D, false);

	memory->addMemoryBlock(0x8000, { 0xD8 });
	auto numCycles = cpu.step();

	EXPECT_EQ(2, numCycles);
	EXPECT_FALSE(cpu.getStatusFlag(CPU::StatusFlag::D));
}

TEST_F(CPUTest, cldChange)
{
	cpu.setStatusFlag(CPU::StatusFlag::D, true);

	memory->addMemoryBlock(0x8000, { 0xD8 });
	auto numCycles = cpu.step();

	EXPECT_EQ(2, numCycles);
	EXPECT_FALSE(cpu.getStatusFlag(CPU::StatusFlag::D));
}

TEST_F(CPUTest, cliNoChange)
{
	cpu.setStatusFlag(CPU::StatusFlag::I, false);

	memory->addMemoryBlock(0x8000, { 0x58 });
	auto numCycles = cpu.step();

	EXPECT_EQ(2, numCycles);
	EXPECT_FALSE(cpu.getStatusFlag(CPU::StatusFlag::I));
}

TEST_F(CPUTest, cliChange)
{
	cpu.setStatusFlag(CPU::StatusFlag::I, true);

    memory->addMemoryBlock(0x8000, { 0x58 });
	auto numCycles = cpu.step();

	EXPECT_EQ(2, numCycles);
	EXPECT_FALSE(cpu.getStatusFlag(CPU::StatusFlag::I));
}

TEST_F(CPUTest, clvNoChange)
{
	cpu.setStatusFlag(CPU::StatusFlag::V, false);

	memory->addMemoryBlock(0x8000, { 0xB8 });
	auto numCycles = cpu.step();

	EXPECT_EQ(2, numCycles);
	EXPECT_FALSE(cpu.getStatusFlag(CPU::StatusFlag::V));
}

TEST_F(CPUTest, clvChange)
{
	cpu.setStatusFlag(CPU::StatusFlag::V, true);

    memory->addMemoryBlock(0x8000, { 0xB8 });
	auto numCycles = cpu.step();

	EXPECT_EQ(2, numCycles);
	EXPECT_FALSE(cpu.getStatusFlag(CPU::StatusFlag::V));
}

TEST_F(CPUTest, secNoChange)
{
	cpu.setStatusFlag(CPU::StatusFlag::C, false);

	memory->addMemoryBlock(0x8000, { 0x38 });
	auto numCycles = cpu.step();

	EXPECT_EQ(2, numCycles);
	EXPECT_TRUE(cpu.getStatusFlag(CPU::StatusFlag::C));
}

TEST_F(CPUTest, secChange)
{
	cpu.setStatusFlag(CPU::StatusFlag::C, true);

    memory->addMemoryBlock(0x8000, { 0x38 });
	auto numCycles = cpu.step();

	EXPECT_EQ(2, numCycles);
	EXPECT_TRUE(cpu.getStatusFlag(CPU::StatusFlag::C));
}

TEST_F(CPUTest, sedNoChange)
{
	cpu.setStatusFlag(CPU::StatusFlag::D, false);

	memory->addMemoryBlock(0x8000, { 0xF8 });
	auto numCycles = cpu.step();

	EXPECT_EQ(2, numCycles);
	EXPECT_TRUE(cpu.getStatusFlag(CPU::StatusFlag::D));
}

TEST_F(CPUTest, sedChange)
{
	cpu.setStatusFlag(CPU::StatusFlag::D, true);

	memory->addMemoryBlock(0x8000, { 0xF8 });
	auto numCycles = cpu.step();

	EXPECT_EQ(2, numCycles);
	EXPECT_TRUE(cpu.getStatusFlag(CPU::StatusFlag::D));
}

TEST_F(CPUTest, seiNoChange)
{
	cpu.setStatusFlag(CPU::StatusFlag::I, false);

	memory->addMemoryBlock(0x8000, { 0x78 });
	auto numCycles = cpu.step();

	EXPECT_EQ(2, numCycles);
	EXPECT_TRUE(cpu.getStatusFlag(CPU::StatusFlag::I));
}

TEST_F(CPUTest, seiChange)
{
	cpu.setStatusFlag(CPU::StatusFlag::I, true);

    memory->addMemoryBlock(0x8000, { 0x78 });
	auto numCycles = cpu.step();

	EXPECT_EQ(2, numCycles);
	EXPECT_TRUE(cpu.getStatusFlag(CPU::StatusFlag::I));
}
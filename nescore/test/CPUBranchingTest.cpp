#include "CPUTest.h"

using namespace nescore;

TEST_F(CPUTest, bccFlagClearPositiveOffsetNoPageCrossing)
{
	cpu.setStatusFlag(CPU::StatusFlag::C, false);
	memory.addMemoryBlock(0x8000, { 0x90, 0x12 });
	auto numCycles = cpu.executeSingleInstruction();

	EXPECT_EQ(3, numCycles);
	EXPECT_EQ(0x8014, cpu.getPC());
}

TEST_F(CPUTest, bccFlagClearNegativeOffsetWithPageCrossing)
{
	cpu.setStatusFlag(CPU::StatusFlag::C, false);
	memory.addMemoryBlock(0x8000, { 0x90, 0xF9 /*= -7*/ });
	auto numCycles = cpu.executeSingleInstruction();

	EXPECT_EQ(4, numCycles);
	EXPECT_EQ(0x7FFB, cpu.getPC());
}

TEST_F(CPUTest, bccFlagSet)
{
	cpu.setStatusFlag(CPU::StatusFlag::C, true);
	memory.addMemoryBlock(0x8000, { 0x90, 0xF9 /*= -7*/ });
	auto numCycles = cpu.executeSingleInstruction();

	EXPECT_EQ(2, numCycles);
	EXPECT_EQ(0x8002, cpu.getPC());
}

TEST_F(CPUTest, bcsFlagSetPositiveOffsetNoPageCrossing)
{
	cpu.setStatusFlag(CPU::StatusFlag::C, true);
	memory.addMemoryBlock(0x8000, { 0xB0, 0x12 });
	auto numCycles = cpu.executeSingleInstruction();

	EXPECT_EQ(3, numCycles);
	EXPECT_EQ(0x8014, cpu.getPC());
}

TEST_F(CPUTest, bcsFlagSetNegativeOffsetWithPageCrossing)
{
	cpu.setStatusFlag(CPU::StatusFlag::C, true);
	memory.addMemoryBlock(0x8000, { 0xB0, 0xF9 /*= -7*/ });
	auto numCycles = cpu.executeSingleInstruction();

	EXPECT_EQ(4, numCycles);
	EXPECT_EQ(0x7FFB, cpu.getPC());
}

TEST_F(CPUTest, bcsFlagClear)
{
	cpu.setStatusFlag(CPU::StatusFlag::C, false);
	memory.addMemoryBlock(0x8000, { 0xB0, 0xF9 /*= -7*/ });
	auto numCycles = cpu.executeSingleInstruction();

	EXPECT_EQ(2, numCycles);
	EXPECT_EQ(0x8002, cpu.getPC());
}

TEST_F(CPUTest, beqFlagSetPositiveOffsetNoPageCrossing)
{
	cpu.setStatusFlag(CPU::StatusFlag::Z, true);
	memory.addMemoryBlock(0x8000, { 0xF0, 0x12 });
	auto numCycles = cpu.executeSingleInstruction();

	EXPECT_EQ(3, numCycles);
	EXPECT_EQ(0x8014, cpu.getPC());
}

TEST_F(CPUTest, beqFlagSetNegativeOffsetWithPageCrossing)
{
	cpu.setStatusFlag(CPU::StatusFlag::Z, true);
	memory.addMemoryBlock(0x8000, { 0xF0, 0xF9 /*= -7*/ });
	auto numCycles = cpu.executeSingleInstruction();

	EXPECT_EQ(4, numCycles);
	EXPECT_EQ(0x7FFB, cpu.getPC());
}

TEST_F(CPUTest, beqFlagClear)
{
	cpu.setStatusFlag(CPU::StatusFlag::Z, false);
	memory.addMemoryBlock(0x8000, { 0xF0, 0xF9 /*= -7*/ });
	auto numCycles = cpu.executeSingleInstruction();

	EXPECT_EQ(2, numCycles);
	EXPECT_EQ(0x8002, cpu.getPC());
}

TEST_F(CPUTest, bmiFlagSetPositiveOffsetNoPageCrossing)
{
	cpu.setStatusFlag(CPU::StatusFlag::N, true);
	memory.addMemoryBlock(0x8000, { 0x30, 0x12 });
	auto numCycles = cpu.executeSingleInstruction();

	EXPECT_EQ(3, numCycles);
	EXPECT_EQ(0x8014, cpu.getPC());
}

TEST_F(CPUTest, bmiFlagSetNegativeOffsetWithPageCrossing)
{
	cpu.setStatusFlag(CPU::StatusFlag::N, true);
	memory.addMemoryBlock(0x8000, { 0x30, 0xF9 /*= -7*/ });
	auto numCycles = cpu.executeSingleInstruction();

	EXPECT_EQ(4, numCycles);
	EXPECT_EQ(0x7FFB, cpu.getPC());
}

TEST_F(CPUTest, bmiFlagClear)
{
	cpu.setStatusFlag(CPU::StatusFlag::N, false);
	memory.addMemoryBlock(0x8000, { 0x30, 0xF9 /*= -7*/ });
	auto numCycles = cpu.executeSingleInstruction();

	EXPECT_EQ(2, numCycles);
	EXPECT_EQ(0x8002, cpu.getPC());
}

TEST_F(CPUTest, bneFlagClearPositiveOffsetNoPageCrossing)
{
	cpu.setStatusFlag(CPU::StatusFlag::Z, false);
	memory.addMemoryBlock(0x8000, { 0xD0, 0x12 });
	auto numCycles = cpu.executeSingleInstruction();

	EXPECT_EQ(3, numCycles);
	EXPECT_EQ(0x8014, cpu.getPC());
}

TEST_F(CPUTest, bneFlagClearNegativeOffsetWithPageCrossing)
{
	cpu.setStatusFlag(CPU::StatusFlag::Z, false);
	memory.addMemoryBlock(0x8000, { 0xD0, 0xF9 /*= -7*/ });
	auto numCycles = cpu.executeSingleInstruction();

	EXPECT_EQ(4, numCycles);
	EXPECT_EQ(0x7FFB, cpu.getPC());
}

TEST_F(CPUTest, bneFlagSet)
{
	cpu.setStatusFlag(CPU::StatusFlag::Z, true);
	memory.addMemoryBlock(0x8000, { 0xD0, 0xF9 /*= -7*/ });
	auto numCycles = cpu.executeSingleInstruction();

	EXPECT_EQ(2, numCycles);
	EXPECT_EQ(0x8002, cpu.getPC());
}

TEST_F(CPUTest, bplFlagClearPositiveOffsetNoPageCrossing)
{
	cpu.setStatusFlag(CPU::StatusFlag::N, false);
	memory.addMemoryBlock(0x8000, { 0x10, 0x12 });
	auto numCycles = cpu.executeSingleInstruction();

	EXPECT_EQ(3, numCycles);
	EXPECT_EQ(0x8014, cpu.getPC());
}

TEST_F(CPUTest, bplFlagClearNegativeOffsetWithPageCrossing)
{
	cpu.setStatusFlag(CPU::StatusFlag::N, false);
	memory.addMemoryBlock(0x8000, { 0x10, 0xF9 /*= -7*/ });
	auto numCycles = cpu.executeSingleInstruction();

	EXPECT_EQ(4, numCycles);
	EXPECT_EQ(0x7FFB, cpu.getPC());
}

TEST_F(CPUTest, bplFlagSet)
{
	cpu.setStatusFlag(CPU::StatusFlag::N, true);
	memory.addMemoryBlock(0x8000, { 0x10, 0xF9 /*= -7*/ });
	auto numCycles = cpu.executeSingleInstruction();

	EXPECT_EQ(2, numCycles);
	EXPECT_EQ(0x8002, cpu.getPC());
}

TEST_F(CPUTest, bvcFlagClearPositiveOffsetNoPageCrossing)
{
	cpu.setStatusFlag(CPU::StatusFlag::V, false);
	memory.addMemoryBlock(0x8000, { 0x50, 0x12 });
	auto numCycles = cpu.executeSingleInstruction();

	EXPECT_EQ(3, numCycles);
	EXPECT_EQ(0x8014, cpu.getPC());
}

TEST_F(CPUTest, bvcFlagClearNegativeOffsetWithPageCrossing)
{
	cpu.setStatusFlag(CPU::StatusFlag::V, false);
	memory.addMemoryBlock(0x8000, { 0x50, 0xF9 /*= -7*/ });
	auto numCycles = cpu.executeSingleInstruction();

	EXPECT_EQ(4, numCycles);
	EXPECT_EQ(0x7FFB, cpu.getPC());
}

TEST_F(CPUTest, bvcFlagSet)
{
	cpu.setStatusFlag(CPU::StatusFlag::V, true);
	memory.addMemoryBlock(0x8000, { 0x50, 0xF9 /*= -7*/ });
	auto numCycles = cpu.executeSingleInstruction();

	EXPECT_EQ(2, numCycles);
	EXPECT_EQ(0x8002, cpu.getPC());
}

TEST_F(CPUTest, bvsFlagSetPositiveOffsetNoPageCrossing)
{
	cpu.setStatusFlag(CPU::StatusFlag::V, true);
	memory.addMemoryBlock(0x8000, { 0x70, 0x12 });
	auto numCycles = cpu.executeSingleInstruction();

	EXPECT_EQ(3, numCycles);
	EXPECT_EQ(0x8014, cpu.getPC());
}

TEST_F(CPUTest, bvsFlagSetNegativeOffsetWithPageCrossing)
{
	cpu.setStatusFlag(CPU::StatusFlag::V, true);
	memory.addMemoryBlock(0x8000, { 0x70, 0xF9 /*= -7*/ });
	auto numCycles = cpu.executeSingleInstruction();

	EXPECT_EQ(4, numCycles);
	EXPECT_EQ(0x7FFB, cpu.getPC());
}

TEST_F(CPUTest, bvsFlagClear)
{
	cpu.setStatusFlag(CPU::StatusFlag::V, false);
	memory.addMemoryBlock(0x8000, { 0x70, 0xF9 /*= -7*/ });
	auto numCycles = cpu.executeSingleInstruction();

	EXPECT_EQ(2, numCycles);
	EXPECT_EQ(0x8002, cpu.getPC());
}
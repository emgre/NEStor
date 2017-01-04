#include "CPUTest.h"

using namespace nescore;

TEST_F(CPUTest, pha)
{
    cpu.setA(0x42);
	memory.addMemoryBlock(0x8000, { 0x48 });
	auto numCycles = cpu.executeSingleInstruction();

	EXPECT_EQ(3, numCycles);
    EXPECT_EQ(0x42, cpu.getA());
    EXPECT_EQ(0xFE, cpu.getSP());
    EXPECT_EQ(0x42, memory.read(0x01FF));
}

TEST_F(CPUTest, phaRollover)
{
    cpu.setSP(0x00);
    cpu.setA(0x42);
	memory.addMemoryBlock(0x8000, { 0x48 });
	auto numCycles = cpu.executeSingleInstruction();

	EXPECT_EQ(3, numCycles);
    EXPECT_EQ(0x42, cpu.getA());
    EXPECT_EQ(0xFF, cpu.getSP());
    EXPECT_EQ(0x42, memory.read(0x0100));
}

TEST_F(CPUTest, php)
{
    cpu.setStatusFlag(CPU::StatusFlag::N, true);
    cpu.setStatusFlag(CPU::StatusFlag::V, false);
    cpu.setStatusFlag(CPU::StatusFlag::B, false);
    cpu.setStatusFlag(CPU::StatusFlag::I, false);
    cpu.setStatusFlag(CPU::StatusFlag::Z, true);
    cpu.setStatusFlag(CPU::StatusFlag::C, false);
	memory.addMemoryBlock(0x8000, { 0x08 });
	auto numCycles = cpu.executeSingleInstruction();

	EXPECT_EQ(3, numCycles);
    EXPECT_TRUE(cpu.getStatusFlag(CPU::StatusFlag::N));
    EXPECT_FALSE(cpu.getStatusFlag(CPU::StatusFlag::V));
    EXPECT_FALSE(cpu.getStatusFlag(CPU::StatusFlag::B));
    EXPECT_FALSE(cpu.getStatusFlag(CPU::StatusFlag::I));
    EXPECT_TRUE(cpu.getStatusFlag(CPU::StatusFlag::Z));
    EXPECT_FALSE(cpu.getStatusFlag(CPU::StatusFlag::C));
    EXPECT_EQ(0xFE, cpu.getSP());
    EXPECT_EQ(0b10000010, memory.read(0x01FF) & 0b11010111);
}

TEST_F(CPUTest, phpRollOver)
{
    cpu.setStatusFlag(CPU::StatusFlag::N, true);
    cpu.setStatusFlag(CPU::StatusFlag::V, false);
    cpu.setStatusFlag(CPU::StatusFlag::B, false);
    cpu.setStatusFlag(CPU::StatusFlag::I, false);
    cpu.setStatusFlag(CPU::StatusFlag::Z, true);
    cpu.setStatusFlag(CPU::StatusFlag::C, false);
    cpu.setSP(0x00);
	memory.addMemoryBlock(0x8000, { 0x08 });
	auto numCycles = cpu.executeSingleInstruction();

	EXPECT_EQ(3, numCycles);
    EXPECT_TRUE(cpu.getStatusFlag(CPU::StatusFlag::N));
    EXPECT_FALSE(cpu.getStatusFlag(CPU::StatusFlag::V));
    EXPECT_FALSE(cpu.getStatusFlag(CPU::StatusFlag::B));
    EXPECT_FALSE(cpu.getStatusFlag(CPU::StatusFlag::I));
    EXPECT_TRUE(cpu.getStatusFlag(CPU::StatusFlag::Z));
    EXPECT_FALSE(cpu.getStatusFlag(CPU::StatusFlag::C));
    EXPECT_EQ(0xFF, cpu.getSP());
    EXPECT_EQ(0b10000010, memory.read(0x0100) & 0b11010111);
}

TEST_F(CPUTest, pla)
{
    cpu.setA(0x76);
    cpu.setSP(0xFE);
	memory.addMemoryBlock(0x8000, { 0x68 });
    memory.addMemoryBlock(0x01FF, { 0x42 });
	auto numCycles = cpu.executeSingleInstruction();

	EXPECT_EQ(4, numCycles);
    EXPECT_EQ(0x42, cpu.getA());
    EXPECT_EQ(0xFF, cpu.getSP());
    EXPECT_FALSE(cpu.getStatusFlag(CPU::StatusFlag::Z));
    EXPECT_FALSE(cpu.getStatusFlag(CPU::StatusFlag::N));
}

TEST_F(CPUTest, plaZero)
{
    cpu.setA(0x76);
    cpu.setSP(0xFE);
	memory.addMemoryBlock(0x8000, { 0x68 });
    memory.addMemoryBlock(0x01FF, { 0x00 });
	auto numCycles = cpu.executeSingleInstruction();

	EXPECT_EQ(4, numCycles);
    EXPECT_EQ(0x00, cpu.getA());
    EXPECT_EQ(0xFF, cpu.getSP());
    EXPECT_TRUE(cpu.getStatusFlag(CPU::StatusFlag::Z));
    EXPECT_FALSE(cpu.getStatusFlag(CPU::StatusFlag::N));
}

TEST_F(CPUTest, plaNegative)
{
    cpu.setA(0x76);
    cpu.setSP(0xFE);
	memory.addMemoryBlock(0x8000, { 0x68 });
    memory.addMemoryBlock(0x01FF, { 0x82 });
	auto numCycles = cpu.executeSingleInstruction();

	EXPECT_EQ(4, numCycles);
    EXPECT_EQ(0x82, cpu.getA());
    EXPECT_EQ(0xFF, cpu.getSP());
    EXPECT_FALSE(cpu.getStatusFlag(CPU::StatusFlag::Z));
    EXPECT_TRUE(cpu.getStatusFlag(CPU::StatusFlag::N));
}

TEST_F(CPUTest, plaRollover)
{
    cpu.setA(0x76);
    cpu.setSP(0xFF);
	memory.addMemoryBlock(0x8000, { 0x68 });
    memory.addMemoryBlock(0x0100, { 0x42 });
	auto numCycles = cpu.executeSingleInstruction();

	EXPECT_EQ(4, numCycles);
    EXPECT_EQ(0x42, cpu.getA());
    EXPECT_EQ(0x00, cpu.getSP());
    EXPECT_FALSE(cpu.getStatusFlag(CPU::StatusFlag::Z));
    EXPECT_FALSE(cpu.getStatusFlag(CPU::StatusFlag::N));
}

TEST_F(CPUTest, plp)
{
    cpu.setSP(0xFE);
	memory.addMemoryBlock(0x8000, { 0x28 });
    memory.addMemoryBlock(0x01FF, { 0b10000010 });
	auto numCycles = cpu.executeSingleInstruction();

	EXPECT_EQ(4, numCycles);
    EXPECT_EQ(0xFF, cpu.getSP());
    EXPECT_TRUE(cpu.getStatusFlag(CPU::StatusFlag::N));
    EXPECT_FALSE(cpu.getStatusFlag(CPU::StatusFlag::V));
    EXPECT_FALSE(cpu.getStatusFlag(CPU::StatusFlag::B));
    EXPECT_FALSE(cpu.getStatusFlag(CPU::StatusFlag::I));
    EXPECT_TRUE(cpu.getStatusFlag(CPU::StatusFlag::Z));
    EXPECT_FALSE(cpu.getStatusFlag(CPU::StatusFlag::C));
}

TEST_F(CPUTest, plpRollover)
{
    cpu.setSP(0xFF);
	memory.addMemoryBlock(0x8000, { 0x28 });
    memory.addMemoryBlock(0x0100, { 0b10000010 });
	auto numCycles = cpu.executeSingleInstruction();

	EXPECT_EQ(4, numCycles);
    EXPECT_EQ(0x00, cpu.getSP());
    EXPECT_TRUE(cpu.getStatusFlag(CPU::StatusFlag::N));
    EXPECT_FALSE(cpu.getStatusFlag(CPU::StatusFlag::V));
    EXPECT_FALSE(cpu.getStatusFlag(CPU::StatusFlag::B));
    EXPECT_FALSE(cpu.getStatusFlag(CPU::StatusFlag::I));
    EXPECT_TRUE(cpu.getStatusFlag(CPU::StatusFlag::Z));
    EXPECT_FALSE(cpu.getStatusFlag(CPU::StatusFlag::C));
}
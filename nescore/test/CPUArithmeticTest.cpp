#include "CPUTest.h"

using namespace nescore;

// Examples for ADC were taken from "MCS6500 Microcomputer
// Family Programming Manual, Revision A", published in
// January 1976.

TEST_F(CPUTest, adcImmediate)
{
	// Example 2.1
	cpu.setStatusFlag(CPU::StatusFlag::C, true);
	cpu.setStatusFlag(CPU::StatusFlag::V, false);
	cpu.setA(0x0D /* 13 */);

	memory.addMemoryBlock(0x8000, { 0x69, 0xD3 /* 211 */ });
	auto numCycles = cpu.executeSingleInstruction();

	EXPECT_EQ(2, numCycles);
	EXPECT_EQ(0xE1 /* 225 */, cpu.getA());
	EXPECT_FALSE(cpu.getStatusFlag(CPU::StatusFlag::Z));
	EXPECT_TRUE(cpu.getStatusFlag(CPU::StatusFlag::N));
	EXPECT_FALSE(cpu.getStatusFlag(CPU::StatusFlag::C));
	EXPECT_FALSE(cpu.getStatusFlag(CPU::StatusFlag::V));
}

TEST_F(CPUTest, adcZeroPage)
{
	// Example 2.2
	cpu.setStatusFlag(CPU::StatusFlag::C, true);
	cpu.setStatusFlag(CPU::StatusFlag::V, false);
	cpu.setA(0xFE /* 254 */);

	memory.addMemoryBlock(0x8000, { 0x65, 0x00 });
	memory.addMemoryBlock(0x0000, { 0x06 });
	auto numCycles = cpu.executeSingleInstruction();

	EXPECT_EQ(3, numCycles);
	EXPECT_EQ(0x05, cpu.getA());
	EXPECT_FALSE(cpu.getStatusFlag(CPU::StatusFlag::Z));
	EXPECT_FALSE(cpu.getStatusFlag(CPU::StatusFlag::N));
	EXPECT_TRUE(cpu.getStatusFlag(CPU::StatusFlag::C));
	EXPECT_FALSE(cpu.getStatusFlag(CPU::StatusFlag::V));
}

TEST_F(CPUTest, adcZeroPageX)
{
	// Example 2.7
	cpu.setStatusFlag(CPU::StatusFlag::C, false);
	cpu.setStatusFlag(CPU::StatusFlag::V, false);
	cpu.setA(0x7F /* 127 */);
	cpu.setX(1);

	memory.addMemoryBlock(0x8000, { 0x75, 0x00 });
	memory.addMemoryBlock(0x0001, { 2 });
	auto numCycles = cpu.executeSingleInstruction();

	EXPECT_EQ(4, numCycles);
	EXPECT_EQ(0x81, cpu.getA());
	EXPECT_FALSE(cpu.getStatusFlag(CPU::StatusFlag::Z));
	EXPECT_TRUE(cpu.getStatusFlag(CPU::StatusFlag::N));
	EXPECT_FALSE(cpu.getStatusFlag(CPU::StatusFlag::C));
	EXPECT_TRUE(cpu.getStatusFlag(CPU::StatusFlag::V));
}

TEST_F(CPUTest, adcAbsolute)
{
	// Example 2.8
	cpu.setStatusFlag(CPU::StatusFlag::C, false);
	cpu.setStatusFlag(CPU::StatusFlag::V, false);
	cpu.setA(0x05);

	memory.addMemoryBlock(0x8000, { 0x6D, 0x03, 0x80, 0xFD /*= -3*/ });
	auto numCycles = cpu.executeSingleInstruction();

	EXPECT_EQ(4, numCycles);
	EXPECT_EQ(0x02, cpu.getA());
	EXPECT_FALSE(cpu.getStatusFlag(CPU::StatusFlag::Z));
	EXPECT_FALSE(cpu.getStatusFlag(CPU::StatusFlag::N));
	EXPECT_TRUE(cpu.getStatusFlag(CPU::StatusFlag::C));
	EXPECT_FALSE(cpu.getStatusFlag(CPU::StatusFlag::V));
}

TEST_F(CPUTest, adcAbsoluteX)
{
	// Example 2.9
	cpu.setStatusFlag(CPU::StatusFlag::C, false);
	cpu.setStatusFlag(CPU::StatusFlag::V, false);
	cpu.setA(0x05);
	cpu.setX(0x01);

	memory.addMemoryBlock(0x8000, { 0x7D, 0x02, 0x80, 0xF9 /*= -7*/ });
	auto numCycles = cpu.executeSingleInstruction();

	EXPECT_EQ(4, numCycles);
	EXPECT_EQ(0xFE /* -2 */, cpu.getA());
	EXPECT_FALSE(cpu.getStatusFlag(CPU::StatusFlag::Z));
	EXPECT_TRUE(cpu.getStatusFlag(CPU::StatusFlag::N));
	EXPECT_FALSE(cpu.getStatusFlag(CPU::StatusFlag::C));
	EXPECT_FALSE(cpu.getStatusFlag(CPU::StatusFlag::V));
}

TEST_F(CPUTest, andImmediateOneBit)
{
	cpu.setA(0b11001111);

	memory.addMemoryBlock(0x8000, { 0x29, 0b11110111 });
	auto numCycles = cpu.executeSingleInstruction();

	EXPECT_EQ(2, numCycles);
	EXPECT_EQ(0b11000111, cpu.getA());
	EXPECT_FALSE(cpu.getStatusFlag(CPU::StatusFlag::Z));
	EXPECT_TRUE(cpu.getStatusFlag(CPU::StatusFlag::N));
}

TEST_F(CPUTest, andZeroPageAllBits)
{
	cpu.setA(0b11001111);

	memory.addMemoryBlock(0x8000, { 0x25, 0x01 });
	memory.addMemoryBlock(0x0001, { 0b00000000 });
	auto numCycles = cpu.executeSingleInstruction();

	EXPECT_EQ(3, numCycles);
	EXPECT_EQ(0b00000000, cpu.getA());
	EXPECT_TRUE(cpu.getStatusFlag(CPU::StatusFlag::Z));
	EXPECT_FALSE(cpu.getStatusFlag(CPU::StatusFlag::N));
}

TEST_F(CPUTest, aslAccNoCarryNegative)
{
	cpu.setA(0b01110011);
	memory.addMemoryBlock(0x8000, { 0x0A });
	auto numCycles = cpu.executeSingleInstruction();

	EXPECT_EQ(2, numCycles);
	EXPECT_EQ(0b11100110, cpu.getA());
	EXPECT_FALSE(cpu.getStatusFlag(CPU::StatusFlag::C));
	EXPECT_FALSE(cpu.getStatusFlag(CPU::StatusFlag::Z));
	EXPECT_TRUE(cpu.getStatusFlag(CPU::StatusFlag::N));
}

TEST_F(CPUTest, aslAccWithCarryZero)
{
	cpu.setA(0b10000000);
	memory.addMemoryBlock(0x8000, { 0x0A });
	auto numCycles = cpu.executeSingleInstruction();

	EXPECT_EQ(2, numCycles);
	EXPECT_EQ(0b00000000, cpu.getA());
	EXPECT_TRUE(cpu.getStatusFlag(CPU::StatusFlag::C));
	EXPECT_TRUE(cpu.getStatusFlag(CPU::StatusFlag::Z));
	EXPECT_FALSE(cpu.getStatusFlag(CPU::StatusFlag::N));
}

TEST_F(CPUTest, aslZeroPageNoCarryZero)
{
	memory.addMemoryBlock(0x8000, { 0x06 });
	memory.addMemoryBlock(0x0000, { 0b00000000 });
	auto numCycles = cpu.executeSingleInstruction();

	EXPECT_EQ(5, numCycles);
	EXPECT_EQ(0b00000000, memory.read(0x0000));
	EXPECT_FALSE(cpu.getStatusFlag(CPU::StatusFlag::C));
	EXPECT_TRUE(cpu.getStatusFlag(CPU::StatusFlag::Z));
	EXPECT_FALSE(cpu.getStatusFlag(CPU::StatusFlag::N));
}

TEST_F(CPUTest, aslAbsoluteWithCarryNegative)
{
	memory.addMemoryBlock(0x8000, { 0x0E, 0x42, 0x00 });
	memory.addMemoryBlock(0x0042, { 0b11000000 });
	auto numCycles = cpu.executeSingleInstruction();

	EXPECT_EQ(6, numCycles);
	EXPECT_EQ(0b10000000, memory.read(0x0042));
	EXPECT_TRUE(cpu.getStatusFlag(CPU::StatusFlag::C));
	EXPECT_FALSE(cpu.getStatusFlag(CPU::StatusFlag::Z));
	EXPECT_TRUE(cpu.getStatusFlag(CPU::StatusFlag::N));
}

TEST_F(CPUTest, bitZeroPageZeroBit6And7Set)
{
	cpu.setA(0b00111111);
	memory.addMemoryBlock(0x8000, { 0x24, 0x00 });
	memory.addMemoryBlock(0x0000, { 0b11000000 });
	auto numCycles = cpu.executeSingleInstruction();

	EXPECT_EQ(3, numCycles);
	EXPECT_TRUE(cpu.getStatusFlag(CPU::StatusFlag::Z));
	EXPECT_TRUE(cpu.getStatusFlag(CPU::StatusFlag::N));
	EXPECT_TRUE(cpu.getStatusFlag(CPU::StatusFlag::V));
}

TEST_F(CPUTest, bitAbsoluteNotZeroBit6And7NotSet)
{
    cpu.setA(0b00001000);
	memory.addMemoryBlock(0x8000, { 0x2C, 0x00, 0x00 });
	memory.addMemoryBlock(0x0000, { 0b00001000 });
	auto numCycles = cpu.executeSingleInstruction();

	EXPECT_EQ(4, numCycles);
	EXPECT_FALSE(cpu.getStatusFlag(CPU::StatusFlag::Z));
	EXPECT_FALSE(cpu.getStatusFlag(CPU::StatusFlag::N));
	EXPECT_FALSE(cpu.getStatusFlag(CPU::StatusFlag::V));
}
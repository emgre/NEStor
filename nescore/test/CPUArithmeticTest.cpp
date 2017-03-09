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

	memory->addMemoryBlock(0x8000, { 0x69, 0xD3 /* 211 */ });
	auto numCycles = cpu.step();

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

	memory->addMemoryBlock(0x8000, { 0x65, 0x00 });
	memory->addMemoryBlock(0x0000, { 0x06 });
	auto numCycles = cpu.step();

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

	memory->addMemoryBlock(0x8000, { 0x75, 0x00 });
	memory->addMemoryBlock(0x0001, { 2 });
	auto numCycles = cpu.step();

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

	memory->addMemoryBlock(0x8000, { 0x6D, 0x03, 0x80, 0xFD /*= -3*/ });
	auto numCycles = cpu.step();

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

	memory->addMemoryBlock(0x8000, { 0x7D, 0x02, 0x80, 0xF9 /*= -7*/ });
	auto numCycles = cpu.step();

	EXPECT_EQ(4, numCycles);
	EXPECT_EQ(0xFE /* -2 */, cpu.getA());
	EXPECT_FALSE(cpu.getStatusFlag(CPU::StatusFlag::Z));
	EXPECT_TRUE(cpu.getStatusFlag(CPU::StatusFlag::N));
	EXPECT_FALSE(cpu.getStatusFlag(CPU::StatusFlag::C));
	EXPECT_FALSE(cpu.getStatusFlag(CPU::StatusFlag::V));
}

TEST_F(CPUTest, adcImmediateMaximumNoCarry)
{
	cpu.setStatusFlag(CPU::StatusFlag::C, true);
	cpu.setStatusFlag(CPU::StatusFlag::V, false);
	cpu.setA(0x7F /* 127 */);

	memory->addMemoryBlock(0x8000, { 0x69, 0x7F /* 127 */ });
	auto numCycles = cpu.step();

	EXPECT_EQ(2, numCycles);
	EXPECT_EQ(0xFF /* 255 */, cpu.getA());
	EXPECT_FALSE(cpu.getStatusFlag(CPU::StatusFlag::Z));
	EXPECT_TRUE(cpu.getStatusFlag(CPU::StatusFlag::N));
	EXPECT_FALSE(cpu.getStatusFlag(CPU::StatusFlag::C));
	EXPECT_TRUE(cpu.getStatusFlag(CPU::StatusFlag::V));
}

TEST_F(CPUTest, andImmediateOneBit)
{
	cpu.setA(0b11001111);

	memory->addMemoryBlock(0x8000, { 0x29, 0b11110111 });
	auto numCycles = cpu.step();

	EXPECT_EQ(2, numCycles);
	EXPECT_EQ(0b11000111, cpu.getA());
	EXPECT_FALSE(cpu.getStatusFlag(CPU::StatusFlag::Z));
	EXPECT_TRUE(cpu.getStatusFlag(CPU::StatusFlag::N));
}

TEST_F(CPUTest, andZeroPageAllBits)
{
	cpu.setA(0b11001111);

	memory->addMemoryBlock(0x8000, { 0x25, 0x01 });
	memory->addMemoryBlock(0x0001, { 0b00000000 });
	auto numCycles = cpu.step();

	EXPECT_EQ(3, numCycles);
	EXPECT_EQ(0b00000000, cpu.getA());
	EXPECT_TRUE(cpu.getStatusFlag(CPU::StatusFlag::Z));
	EXPECT_FALSE(cpu.getStatusFlag(CPU::StatusFlag::N));
}

TEST_F(CPUTest, aslAccNoCarryNegative)
{
	cpu.setA(0b01110011);
	memory->addMemoryBlock(0x8000, { 0x0A });
	auto numCycles = cpu.step();

	EXPECT_EQ(2, numCycles);
	EXPECT_EQ(0b11100110, cpu.getA());
	EXPECT_FALSE(cpu.getStatusFlag(CPU::StatusFlag::C));
	EXPECT_FALSE(cpu.getStatusFlag(CPU::StatusFlag::Z));
	EXPECT_TRUE(cpu.getStatusFlag(CPU::StatusFlag::N));
}

TEST_F(CPUTest, aslAccWithCarryZero)
{
	cpu.setA(0b10000000);
	memory->addMemoryBlock(0x8000, { 0x0A });
	auto numCycles = cpu.step();

	EXPECT_EQ(2, numCycles);
	EXPECT_EQ(0b00000000, cpu.getA());
	EXPECT_TRUE(cpu.getStatusFlag(CPU::StatusFlag::C));
	EXPECT_TRUE(cpu.getStatusFlag(CPU::StatusFlag::Z));
	EXPECT_FALSE(cpu.getStatusFlag(CPU::StatusFlag::N));
}

TEST_F(CPUTest, aslZeroPageNoCarryZero)
{
	memory->addMemoryBlock(0x8000, { 0x06 });
	memory->addMemoryBlock(0x0000, { 0b00000000 });
	auto numCycles = cpu.step();

	EXPECT_EQ(5, numCycles);
	EXPECT_EQ(0b00000000, memory->read(0x0000));
	EXPECT_FALSE(cpu.getStatusFlag(CPU::StatusFlag::C));
	EXPECT_TRUE(cpu.getStatusFlag(CPU::StatusFlag::Z));
	EXPECT_FALSE(cpu.getStatusFlag(CPU::StatusFlag::N));
}

TEST_F(CPUTest, aslAbsoluteWithCarryNegative)
{
	memory->addMemoryBlock(0x8000, { 0x0E, 0x42, 0x00 });
	memory->addMemoryBlock(0x0042, { 0b11000000 });
	auto numCycles = cpu.step();

	EXPECT_EQ(6, numCycles);
	EXPECT_EQ(0b10000000, memory->read(0x0042));
	EXPECT_TRUE(cpu.getStatusFlag(CPU::StatusFlag::C));
	EXPECT_FALSE(cpu.getStatusFlag(CPU::StatusFlag::Z));
	EXPECT_TRUE(cpu.getStatusFlag(CPU::StatusFlag::N));
}

TEST_F(CPUTest, bitZeroPageZeroBit6And7Set)
{
	cpu.setA(0b00111111);
	memory->addMemoryBlock(0x8000, { 0x24, 0x00 });
	memory->addMemoryBlock(0x0000, { 0b11000000 });
	auto numCycles = cpu.step();

	EXPECT_EQ(3, numCycles);
	EXPECT_TRUE(cpu.getStatusFlag(CPU::StatusFlag::Z));
	EXPECT_TRUE(cpu.getStatusFlag(CPU::StatusFlag::N));
	EXPECT_TRUE(cpu.getStatusFlag(CPU::StatusFlag::V));
}

TEST_F(CPUTest, bitAbsoluteNotZeroBit6And7NotSet)
{
    cpu.setA(0b00001000);
	memory->addMemoryBlock(0x8000, { 0x2C, 0x00, 0x00 });
	memory->addMemoryBlock(0x0000, { 0b00001000 });
	auto numCycles = cpu.step();

	EXPECT_EQ(4, numCycles);
	EXPECT_FALSE(cpu.getStatusFlag(CPU::StatusFlag::Z));
	EXPECT_FALSE(cpu.getStatusFlag(CPU::StatusFlag::N));
	EXPECT_FALSE(cpu.getStatusFlag(CPU::StatusFlag::V));
}

TEST_F(CPUTest, cmpImmediateEqual)
{
	cpu.setA(0x42);
	memory->addMemoryBlock(0x8000, { 0xC9, 0x42 });
	auto numCycles = cpu.step();

	EXPECT_EQ(2, numCycles);
	EXPECT_TRUE(cpu.getStatusFlag(CPU::StatusFlag::C));
	EXPECT_TRUE(cpu.getStatusFlag(CPU::StatusFlag::Z));
	EXPECT_FALSE(cpu.getStatusFlag(CPU::StatusFlag::N));
}

TEST_F(CPUTest, cmpZeroPageSmaller)
{
	cpu.setA(0x42);
	memory->addMemoryBlock(0x8000, { 0xC5 });
	memory->addMemoryBlock(0x0000, { 0x10 });
	auto numCycles = cpu.step();

	EXPECT_EQ(3, numCycles);
	EXPECT_FALSE(cpu.getStatusFlag(CPU::StatusFlag::C));
	EXPECT_FALSE(cpu.getStatusFlag(CPU::StatusFlag::Z));
	EXPECT_FALSE(cpu.getStatusFlag(CPU::StatusFlag::N));
}

TEST_F(CPUTest, cmpAbsoluteXPageCrossingBigger)
{
	cpu.setA(0x42);
	cpu.setX(2);
	memory->addMemoryBlock(0x8000, { 0xDD, 0xFF, 0x80 });
	memory->addMemoryBlock(0x8101, { 0xAA });
	auto numCycles = cpu.step();

	EXPECT_EQ(5, numCycles);
	EXPECT_TRUE(cpu.getStatusFlag(CPU::StatusFlag::C));
	EXPECT_FALSE(cpu.getStatusFlag(CPU::StatusFlag::Z));
	EXPECT_TRUE(cpu.getStatusFlag(CPU::StatusFlag::N));
}

TEST_F(CPUTest, cpxImmediateEqual)
{
	cpu.setX(0x42);
	memory->addMemoryBlock(0x8000, { 0xE0, 0x42 });
	auto numCycles = cpu.step();

	EXPECT_EQ(2, numCycles);
	EXPECT_TRUE(cpu.getStatusFlag(CPU::StatusFlag::C));
	EXPECT_TRUE(cpu.getStatusFlag(CPU::StatusFlag::Z));
	EXPECT_FALSE(cpu.getStatusFlag(CPU::StatusFlag::N));
}

TEST_F(CPUTest, cpxZeroPageSmaller)
{
	cpu.setX(0x42);
	memory->addMemoryBlock(0x8000, { 0xE4 });
	memory->addMemoryBlock(0x0000, { 0x10 });
	auto numCycles = cpu.step();

	EXPECT_EQ(3, numCycles);
	EXPECT_FALSE(cpu.getStatusFlag(CPU::StatusFlag::C));
	EXPECT_FALSE(cpu.getStatusFlag(CPU::StatusFlag::Z));
	EXPECT_FALSE(cpu.getStatusFlag(CPU::StatusFlag::N));
}

TEST_F(CPUTest, cpxAbsoluteBigger)
{
	cpu.setX(0x42);
	memory->addMemoryBlock(0x8000, { 0xEC, 0x03, 0x80, 0xAA });
	auto numCycles = cpu.step();

	EXPECT_EQ(4, numCycles);
	EXPECT_TRUE(cpu.getStatusFlag(CPU::StatusFlag::C));
	EXPECT_FALSE(cpu.getStatusFlag(CPU::StatusFlag::Z));
	EXPECT_TRUE(cpu.getStatusFlag(CPU::StatusFlag::N));
}

TEST_F(CPUTest, cpyImmediateEqual)
{
	cpu.setY(0x42);
	memory->addMemoryBlock(0x8000, { 0xC0, 0x42 });
	auto numCycles = cpu.step();

	EXPECT_EQ(2, numCycles);
	EXPECT_TRUE(cpu.getStatusFlag(CPU::StatusFlag::C));
	EXPECT_TRUE(cpu.getStatusFlag(CPU::StatusFlag::Z));
	EXPECT_FALSE(cpu.getStatusFlag(CPU::StatusFlag::N));
}

TEST_F(CPUTest, cpyZeroPageSmaller)
{
	cpu.setY(0x42);
	memory->addMemoryBlock(0x8000, { 0xC4 });
	memory->addMemoryBlock(0x0000, { 0x10 });
	auto numCycles = cpu.step();

	EXPECT_EQ(3, numCycles);
	EXPECT_FALSE(cpu.getStatusFlag(CPU::StatusFlag::C));
	EXPECT_FALSE(cpu.getStatusFlag(CPU::StatusFlag::Z));
	EXPECT_FALSE(cpu.getStatusFlag(CPU::StatusFlag::N));
}

TEST_F(CPUTest, cpyAbsoluteBigger)
{
	cpu.setY(0x42);
	memory->addMemoryBlock(0x8000, { 0xCC, 0x03, 0x80, 0xAA });
	auto numCycles = cpu.step();

	EXPECT_EQ(4, numCycles);
	EXPECT_TRUE(cpu.getStatusFlag(CPU::StatusFlag::C));
	EXPECT_FALSE(cpu.getStatusFlag(CPU::StatusFlag::Z));
	EXPECT_TRUE(cpu.getStatusFlag(CPU::StatusFlag::N));
}

TEST_F(CPUTest, eorImmediateZero)
{
	cpu.setA(0b10101010);

	memory->addMemoryBlock(0x8000, { 0x49, 0b10101010 });
	auto numCycles = cpu.step();

	EXPECT_EQ(2, numCycles);
	EXPECT_EQ(0b00000000, cpu.getA());
	EXPECT_TRUE(cpu.getStatusFlag(CPU::StatusFlag::Z));
	EXPECT_FALSE(cpu.getStatusFlag(CPU::StatusFlag::N));
}

TEST_F(CPUTest, eorZeroPageAll)
{
	cpu.setStatusFlag(CPU::StatusFlag::N, true);
	cpu.setA(0b10101010);
	memory->addMemoryBlock(0x8000, { 0x45, 0x00 });
	memory->addMemoryBlock(0x0000, { 0b01010101 });
	auto numCycles = cpu.step();

	EXPECT_EQ(3, numCycles);
	EXPECT_EQ(0b11111111, cpu.getA());
	EXPECT_FALSE(cpu.getStatusFlag(CPU::StatusFlag::Z));
	EXPECT_TRUE(cpu.getStatusFlag(CPU::StatusFlag::N));
}

TEST_F(CPUTest, lsrAccNoCarryNegative)
{
	cpu.setStatusFlag(CPU::StatusFlag::N, true);
	cpu.setA(0b01110010);
	memory->addMemoryBlock(0x8000, { 0x4A });
	auto numCycles = cpu.step();

	EXPECT_EQ(2, numCycles);
	EXPECT_EQ(0b00111001, cpu.getA());
	EXPECT_FALSE(cpu.getStatusFlag(CPU::StatusFlag::C));
	EXPECT_FALSE(cpu.getStatusFlag(CPU::StatusFlag::Z));
	EXPECT_FALSE(cpu.getStatusFlag(CPU::StatusFlag::N));
}

TEST_F(CPUTest, lsrAccWithCarryZero)
{
	cpu.setStatusFlag(CPU::StatusFlag::N, true);
	cpu.setA(0b00000001);
	memory->addMemoryBlock(0x8000, { 0x4A });
	auto numCycles = cpu.step();

	EXPECT_EQ(2, numCycles);
	EXPECT_EQ(0b00000000, cpu.getA());
	EXPECT_TRUE(cpu.getStatusFlag(CPU::StatusFlag::C));
	EXPECT_TRUE(cpu.getStatusFlag(CPU::StatusFlag::Z));
	EXPECT_FALSE(cpu.getStatusFlag(CPU::StatusFlag::N));
}

TEST_F(CPUTest, lsrZeroPageNoCarryZero)
{
	cpu.setStatusFlag(CPU::StatusFlag::N, true);
	memory->addMemoryBlock(0x8000, { 0x46 });
	memory->addMemoryBlock(0x0000, { 0b00000000 });
	auto numCycles = cpu.step();

	EXPECT_EQ(5, numCycles);
	EXPECT_EQ(0b00000000, memory->read(0x0000));
	EXPECT_FALSE(cpu.getStatusFlag(CPU::StatusFlag::C));
	EXPECT_TRUE(cpu.getStatusFlag(CPU::StatusFlag::Z));
	EXPECT_FALSE(cpu.getStatusFlag(CPU::StatusFlag::N));
}

TEST_F(CPUTest, lsrAbsoluteWithCarry)
{
	cpu.setStatusFlag(CPU::StatusFlag::N, true);
	memory->addMemoryBlock(0x8000, { 0x4E, 0x42, 0x00 });
	memory->addMemoryBlock(0x0042, { 0b00000011 });
	auto numCycles = cpu.step();

	EXPECT_EQ(6, numCycles);
	EXPECT_EQ(0b00000001, memory->read(0x0042));
	EXPECT_TRUE(cpu.getStatusFlag(CPU::StatusFlag::C));
	EXPECT_FALSE(cpu.getStatusFlag(CPU::StatusFlag::Z));
	EXPECT_FALSE(cpu.getStatusFlag(CPU::StatusFlag::N));
}

TEST_F(CPUTest, oraImmediateSame)
{
	cpu.setA(0b10101010);

	memory->addMemoryBlock(0x8000, { 0x09, 0b10101010 });
	auto numCycles = cpu.step();

	EXPECT_EQ(2, numCycles);
	EXPECT_EQ(0b10101010, cpu.getA());
	EXPECT_FALSE(cpu.getStatusFlag(CPU::StatusFlag::Z));
	EXPECT_TRUE(cpu.getStatusFlag(CPU::StatusFlag::N));
}

TEST_F(CPUTest, oraZeroPageAll)
{
	cpu.setA(0b10101010);

	memory->addMemoryBlock(0x8000, { 0x05, 0x00 });
	memory->addMemoryBlock(0x0000, { 0b01010101 });
	auto numCycles = cpu.step();

	EXPECT_EQ(3, numCycles);
	EXPECT_EQ(0b11111111, cpu.getA());
	EXPECT_FALSE(cpu.getStatusFlag(CPU::StatusFlag::Z));
	EXPECT_TRUE(cpu.getStatusFlag(CPU::StatusFlag::N));
}

TEST_F(CPUTest, oraAbsoluteZero)
{
	cpu.setA(0b00000000);

	memory->addMemoryBlock(0x8000, { 0x0D, 0x03, 0x80, 0b00000000 });
	auto numCycles = cpu.step();

	EXPECT_EQ(4, numCycles);
	EXPECT_EQ(0b00000000, cpu.getA());
	EXPECT_TRUE(cpu.getStatusFlag(CPU::StatusFlag::Z));
	EXPECT_FALSE(cpu.getStatusFlag(CPU::StatusFlag::N));
}

TEST_F(CPUTest, rolAccNoCarryNegativeNoGeneratedCarry)
{
	cpu.setStatusFlag(CPU::StatusFlag::C, false);
	cpu.setA(0b01110011);
	memory->addMemoryBlock(0x8000, { 0x2A });
	auto numCycles = cpu.step();

	EXPECT_EQ(2, numCycles);
	EXPECT_EQ(0b11100110, cpu.getA());
	EXPECT_FALSE(cpu.getStatusFlag(CPU::StatusFlag::C));
	EXPECT_FALSE(cpu.getStatusFlag(CPU::StatusFlag::Z));
	EXPECT_TRUE(cpu.getStatusFlag(CPU::StatusFlag::N));
}

TEST_F(CPUTest, rolAccNoCarryZeroGenerateCarry)
{
	cpu.setStatusFlag(CPU::StatusFlag::C, false);
	cpu.setA(0b10000000);
	memory->addMemoryBlock(0x8000, { 0x2A });
	auto numCycles = cpu.step();

	EXPECT_EQ(2, numCycles);
	EXPECT_EQ(0b00000000, cpu.getA());
	EXPECT_TRUE(cpu.getStatusFlag(CPU::StatusFlag::C));
	EXPECT_TRUE(cpu.getStatusFlag(CPU::StatusFlag::Z));
	EXPECT_FALSE(cpu.getStatusFlag(CPU::StatusFlag::N));
}

TEST_F(CPUTest, rolAccWithCarryZeroNoGeneratedCarry)
{
	cpu.setStatusFlag(CPU::StatusFlag::C, true);
	cpu.setA(0b00000000);
	memory->addMemoryBlock(0x8000, { 0x2A });
	auto numCycles = cpu.step();

	EXPECT_EQ(2, numCycles);
	EXPECT_EQ(0b00000001, cpu.getA());
	EXPECT_FALSE(cpu.getStatusFlag(CPU::StatusFlag::C));
	EXPECT_FALSE(cpu.getStatusFlag(CPU::StatusFlag::Z));
	EXPECT_FALSE(cpu.getStatusFlag(CPU::StatusFlag::N));
}

TEST_F(CPUTest, rolZeroPageNoCarryZeroGenerateCarry)
{
	cpu.setStatusFlag(CPU::StatusFlag::C, false);
	memory->addMemoryBlock(0x8000, { 0x26 });
	memory->addMemoryBlock(0x0000, { 0b10000000 });
	auto numCycles = cpu.step();

	EXPECT_EQ(5, numCycles);
	EXPECT_EQ(0b00000000, memory->read(0x0000));
	EXPECT_TRUE(cpu.getStatusFlag(CPU::StatusFlag::C));
	EXPECT_TRUE(cpu.getStatusFlag(CPU::StatusFlag::Z));
	EXPECT_FALSE(cpu.getStatusFlag(CPU::StatusFlag::N));
}

TEST_F(CPUTest, rolAbsoluteWithCarryNegativeNoGeneratedCarry)
{
	cpu.setStatusFlag(CPU::StatusFlag::C, true);
	memory->addMemoryBlock(0x8000, { 0x2E, 0x42, 0x00 });
	memory->addMemoryBlock(0x0042, { 0b01000000 });
	auto numCycles = cpu.step();

	EXPECT_EQ(6, numCycles);
	EXPECT_EQ(0b10000001, memory->read(0x0042));
	EXPECT_FALSE(cpu.getStatusFlag(CPU::StatusFlag::C));
	EXPECT_FALSE(cpu.getStatusFlag(CPU::StatusFlag::Z));
	EXPECT_TRUE(cpu.getStatusFlag(CPU::StatusFlag::N));
}

TEST_F(CPUTest, rorAccNoCarryNoGeneratedCarry)
{
	cpu.setStatusFlag(CPU::StatusFlag::C, false);
	cpu.setA(0b11001110);
	memory->addMemoryBlock(0x8000, { 0x6A });
	auto numCycles = cpu.step();

	EXPECT_EQ(2, numCycles);
	EXPECT_EQ(0b01100111, cpu.getA());
	EXPECT_FALSE(cpu.getStatusFlag(CPU::StatusFlag::C));
	EXPECT_FALSE(cpu.getStatusFlag(CPU::StatusFlag::Z));
	EXPECT_FALSE(cpu.getStatusFlag(CPU::StatusFlag::N));
}

TEST_F(CPUTest, rorAccNoCarryZeroGenerateCarry)
{
	cpu.setStatusFlag(CPU::StatusFlag::C, false);
	cpu.setA(0b00000001);
	memory->addMemoryBlock(0x8000, { 0x6A });
	auto numCycles = cpu.step();

	EXPECT_EQ(2, numCycles);
	EXPECT_EQ(0b00000000, cpu.getA());
	EXPECT_TRUE(cpu.getStatusFlag(CPU::StatusFlag::C));
	EXPECT_TRUE(cpu.getStatusFlag(CPU::StatusFlag::Z));
	EXPECT_FALSE(cpu.getStatusFlag(CPU::StatusFlag::N));
}

TEST_F(CPUTest, rorAccWithCarryNegativeNoGeneratedCarry)
{
	cpu.setStatusFlag(CPU::StatusFlag::C, true);
	cpu.setA(0b00000000);
	memory->addMemoryBlock(0x8000, { 0x6A });
	auto numCycles = cpu.step();

	EXPECT_EQ(2, numCycles);
	EXPECT_EQ(0b10000000, cpu.getA());
	EXPECT_FALSE(cpu.getStatusFlag(CPU::StatusFlag::C));
	EXPECT_FALSE(cpu.getStatusFlag(CPU::StatusFlag::Z));
	EXPECT_TRUE(cpu.getStatusFlag(CPU::StatusFlag::N));
}

TEST_F(CPUTest, rorZeroPageNoCarryZeroGenerateCarry)
{
	cpu.setStatusFlag(CPU::StatusFlag::C, false);
	memory->addMemoryBlock(0x8000, { 0x66 });
	memory->addMemoryBlock(0x0000, { 0b00000001 });
	auto numCycles = cpu.step();

	EXPECT_EQ(5, numCycles);
	EXPECT_EQ(0b00000000, memory->read(0x0000));
	EXPECT_TRUE(cpu.getStatusFlag(CPU::StatusFlag::C));
	EXPECT_TRUE(cpu.getStatusFlag(CPU::StatusFlag::Z));
	EXPECT_FALSE(cpu.getStatusFlag(CPU::StatusFlag::N));
}

TEST_F(CPUTest, rorAbsoluteWithCarryNegativeNoGeneratedCarry)
{
	cpu.setStatusFlag(CPU::StatusFlag::C, true);
	memory->addMemoryBlock(0x8000, { 0x6E, 0x42, 0x00 });
	memory->addMemoryBlock(0x0042, { 0b00000010 });
	auto numCycles = cpu.step();

	EXPECT_EQ(6, numCycles);
	EXPECT_EQ(0b10000001, memory->read(0x0042));
	EXPECT_FALSE(cpu.getStatusFlag(CPU::StatusFlag::C));
	EXPECT_FALSE(cpu.getStatusFlag(CPU::StatusFlag::Z));
	EXPECT_TRUE(cpu.getStatusFlag(CPU::StatusFlag::N));
}

// Examples for SBC were taken from "MCS6500 Microcomputer
// Family Programming Manual, Revision A", published in
// January 1976.

TEST_F(CPUTest, sbcImmediate)
{
	// Example 2.13
	cpu.setStatusFlag(CPU::StatusFlag::C, true);
	cpu.setStatusFlag(CPU::StatusFlag::V, false);
	cpu.setA(0x05);

	memory->addMemoryBlock(0x8000, { 0xE9, 0x03 });
	auto numCycles = cpu.step();

	EXPECT_EQ(2, numCycles);
	EXPECT_EQ(0x02, cpu.getA());
	EXPECT_FALSE(cpu.getStatusFlag(CPU::StatusFlag::Z));
	EXPECT_FALSE(cpu.getStatusFlag(CPU::StatusFlag::N));
	EXPECT_TRUE(cpu.getStatusFlag(CPU::StatusFlag::C));
	EXPECT_FALSE(cpu.getStatusFlag(CPU::StatusFlag::V));
}

TEST_F(CPUTest, adcZeroPageNegativeWithBorrow)
{
	// Example 2.14
	cpu.setStatusFlag(CPU::StatusFlag::C, true);
	cpu.setStatusFlag(CPU::StatusFlag::V, false);
	cpu.setA(0x05);

	memory->addMemoryBlock(0x8000, { 0xE5, 0x00 });
	memory->addMemoryBlock(0x0000, { 0x06 });
	auto numCycles = cpu.step();

	EXPECT_EQ(3, numCycles);
	EXPECT_EQ(0xFF /* -1 */, cpu.getA());
	EXPECT_FALSE(cpu.getStatusFlag(CPU::StatusFlag::Z));
	EXPECT_TRUE(cpu.getStatusFlag(CPU::StatusFlag::N));
	EXPECT_FALSE(cpu.getStatusFlag(CPU::StatusFlag::C));
	EXPECT_FALSE(cpu.getStatusFlag(CPU::StatusFlag::V));
}

TEST_F(CPUTest, sbcAbsoluteNoCarry)
{
	// Example 2.18
	cpu.setStatusFlag(CPU::StatusFlag::C, false);
	cpu.setStatusFlag(CPU::StatusFlag::V, false);
	cpu.setA(0x2C /* 44 */);

	memory->addMemoryBlock(0x8000, { 0xED, 0x03, 0x80, 0x1D /* 29 */ });
	auto numCycles = cpu.step();

	EXPECT_EQ(4, numCycles);
	EXPECT_EQ(0x10 /* 16 */, cpu.getA());
	EXPECT_FALSE(cpu.getStatusFlag(CPU::StatusFlag::Z));
	EXPECT_FALSE(cpu.getStatusFlag(CPU::StatusFlag::N));
	EXPECT_TRUE(cpu.getStatusFlag(CPU::StatusFlag::C));
	EXPECT_FALSE(cpu.getStatusFlag(CPU::StatusFlag::V));
}
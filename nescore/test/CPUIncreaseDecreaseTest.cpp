#include "CPUTest.h"

using namespace nescore;

TEST_F(CPUTest, decZeroPageZero)
{
	memory->addMemoryBlock(0x8000, { 0xC6, 0x00 });
    memory->addMemoryBlock(0x0000, { 0x01 });
	auto numCycles = cpu.step();

	EXPECT_EQ(5, numCycles);
    EXPECT_EQ(0x00, memory->read(0x0000));
	EXPECT_TRUE(cpu.getStatusFlag(CPU::StatusFlag::Z));
	EXPECT_FALSE(cpu.getStatusFlag(CPU::StatusFlag::N));
}

TEST_F(CPUTest, decZeroPageRollOver)
{
	memory->addMemoryBlock(0x8000, { 0xC6, 0x00 });
    memory->addMemoryBlock(0x0000, { 0x00 });
	auto numCycles = cpu.step();

	EXPECT_EQ(5, numCycles);
    EXPECT_EQ(0xFF, memory->read(0x0000));
	EXPECT_FALSE(cpu.getStatusFlag(CPU::StatusFlag::Z));
	EXPECT_TRUE(cpu.getStatusFlag(CPU::StatusFlag::N));
}

TEST_F(CPUTest, decZeroPageXZero)
{
    cpu.setX(1);
	memory->addMemoryBlock(0x8000, { 0xD6, 0x00 });
    memory->addMemoryBlock(0x0001, { 0x01 });
	auto numCycles = cpu.step();

	EXPECT_EQ(6, numCycles);
    EXPECT_EQ(0x00, memory->read(0x0001));
	EXPECT_TRUE(cpu.getStatusFlag(CPU::StatusFlag::Z));
	EXPECT_FALSE(cpu.getStatusFlag(CPU::StatusFlag::N));
}

TEST_F(CPUTest, decZeroPageXRollOver)
{
    cpu.setX(1);
	memory->addMemoryBlock(0x8000, { 0xD6, 0x00 });
    memory->addMemoryBlock(0x0001, { 0x00 });
	auto numCycles = cpu.step();

	EXPECT_EQ(6, numCycles);
    EXPECT_EQ(0xFF, memory->read(0x0001));
	EXPECT_FALSE(cpu.getStatusFlag(CPU::StatusFlag::Z));
	EXPECT_TRUE(cpu.getStatusFlag(CPU::StatusFlag::N));
}

TEST_F(CPUTest, decAbsoluteZero)
{
	memory->addMemoryBlock(0x8000, { 0xCE, 0x03, 0x80, 0x01 });
	auto numCycles = cpu.step();

	EXPECT_EQ(6, numCycles);
    EXPECT_EQ(0x00, memory->read(0x8003));
	EXPECT_TRUE(cpu.getStatusFlag(CPU::StatusFlag::Z));
	EXPECT_FALSE(cpu.getStatusFlag(CPU::StatusFlag::N));
}

TEST_F(CPUTest, decAbsoluteRollOver)
{
	memory->addMemoryBlock(0x8000, { 0xCE, 0x03, 0x80, 0x00 });
	auto numCycles = cpu.step();

	EXPECT_EQ(6, numCycles);
    EXPECT_EQ(0xFF, memory->read(0x8003));
	EXPECT_FALSE(cpu.getStatusFlag(CPU::StatusFlag::Z));
	EXPECT_TRUE(cpu.getStatusFlag(CPU::StatusFlag::N));
}

TEST_F(CPUTest, decAbsoluteXZero)
{
    cpu.setX(1);
	memory->addMemoryBlock(0x8000, { 0xDE, 0x02, 0x80, 0x01 });
	auto numCycles = cpu.step();

	EXPECT_EQ(7, numCycles);
    EXPECT_EQ(0x00, memory->read(0x8003));
	EXPECT_TRUE(cpu.getStatusFlag(CPU::StatusFlag::Z));
	EXPECT_FALSE(cpu.getStatusFlag(CPU::StatusFlag::N));
}

TEST_F(CPUTest, decAbsoluteXRollOver)
{
    cpu.setX(1);
	memory->addMemoryBlock(0x8000, { 0xDE, 0x02, 0x80, 0x00 });
	auto numCycles = cpu.step();

	EXPECT_EQ(7, numCycles);
    EXPECT_EQ(0xFF, memory->read(0x8003));
	EXPECT_FALSE(cpu.getStatusFlag(CPU::StatusFlag::Z));
	EXPECT_TRUE(cpu.getStatusFlag(CPU::StatusFlag::N));
}

TEST_F(CPUTest, dexZero)
{
    cpu.setX(0x01);
	memory->addMemoryBlock(0x8000, { 0xCA });
	auto numCycles = cpu.step();

	EXPECT_EQ(2, numCycles);
    EXPECT_EQ(0x00, cpu.getX());
	EXPECT_TRUE(cpu.getStatusFlag(CPU::StatusFlag::Z));
	EXPECT_FALSE(cpu.getStatusFlag(CPU::StatusFlag::N));
}

TEST_F(CPUTest, dexRollOver)
{
    cpu.setX(0x00);
	memory->addMemoryBlock(0x8000, { 0xCA });
	auto numCycles = cpu.step();

	EXPECT_EQ(2, numCycles);
    EXPECT_EQ(0xFF, cpu.getX());
	EXPECT_FALSE(cpu.getStatusFlag(CPU::StatusFlag::Z));
	EXPECT_TRUE(cpu.getStatusFlag(CPU::StatusFlag::N));
}

TEST_F(CPUTest, deyZero)
{
    cpu.setY(0x01);
	memory->addMemoryBlock(0x8000, { 0x88 });
	auto numCycles = cpu.step();

	EXPECT_EQ(2, numCycles);
    EXPECT_EQ(0x00, cpu.getY());
	EXPECT_TRUE(cpu.getStatusFlag(CPU::StatusFlag::Z));
	EXPECT_FALSE(cpu.getStatusFlag(CPU::StatusFlag::N));
}

TEST_F(CPUTest, deyRollOver)
{
    cpu.setY(0x00);
	memory->addMemoryBlock(0x8000, { 0x88 });
	auto numCycles = cpu.step();

	EXPECT_EQ(2, numCycles);
    EXPECT_EQ(0xFF, cpu.getY());
	EXPECT_FALSE(cpu.getStatusFlag(CPU::StatusFlag::Z));
	EXPECT_TRUE(cpu.getStatusFlag(CPU::StatusFlag::N));
}

TEST_F(CPUTest, incZeroPageZero)
{
	memory->addMemoryBlock(0x8000, { 0xE6, 0x00 });
    memory->addMemoryBlock(0x0000, { 0xAA });
	auto numCycles = cpu.step();

	EXPECT_EQ(5, numCycles);
    EXPECT_EQ(0xAB, memory->read(0x0000));
	EXPECT_FALSE(cpu.getStatusFlag(CPU::StatusFlag::Z));
	EXPECT_TRUE(cpu.getStatusFlag(CPU::StatusFlag::N));
}

TEST_F(CPUTest, incZeroPageRollOver)
{
	memory->addMemoryBlock(0x8000, { 0xE6, 0x00 });
    memory->addMemoryBlock(0x0000, { 0xFF });
	auto numCycles = cpu.step();

	EXPECT_EQ(5, numCycles);
    EXPECT_EQ(0x00, memory->read(0x0000));
	EXPECT_TRUE(cpu.getStatusFlag(CPU::StatusFlag::Z));
	EXPECT_FALSE(cpu.getStatusFlag(CPU::StatusFlag::N));
}

TEST_F(CPUTest, incZeroPageXZero)
{
    cpu.setX(1);
	memory->addMemoryBlock(0x8000, { 0xF6, 0x00 });
    memory->addMemoryBlock(0x0001, { 0xAA });
	auto numCycles = cpu.step();

	EXPECT_EQ(6, numCycles);
    EXPECT_EQ(0xAB, memory->read(0x0001));
	EXPECT_FALSE(cpu.getStatusFlag(CPU::StatusFlag::Z));
	EXPECT_TRUE(cpu.getStatusFlag(CPU::StatusFlag::N));
}

TEST_F(CPUTest, incZeroPageXRollOver)
{
    cpu.setX(1);
	memory->addMemoryBlock(0x8000, { 0xF6, 0x00 });
    memory->addMemoryBlock(0x0001, { 0xFF });
	auto numCycles = cpu.step();

	EXPECT_EQ(6, numCycles);
    EXPECT_EQ(0x00, memory->read(0x0001));
	EXPECT_TRUE(cpu.getStatusFlag(CPU::StatusFlag::Z));
	EXPECT_FALSE(cpu.getStatusFlag(CPU::StatusFlag::N));
}

TEST_F(CPUTest, incAbsoluteZero)
{
	memory->addMemoryBlock(0x8000, { 0xEE, 0x03, 0x80, 0xAA });
	auto numCycles = cpu.step();

	EXPECT_EQ(6, numCycles);
    EXPECT_EQ(0xAB, memory->read(0x8003));
	EXPECT_FALSE(cpu.getStatusFlag(CPU::StatusFlag::Z));
	EXPECT_TRUE(cpu.getStatusFlag(CPU::StatusFlag::N));
}

TEST_F(CPUTest, incAbsoluteRollOver)
{
	memory->addMemoryBlock(0x8000, { 0xEE, 0x03, 0x80, 0xFF });
	auto numCycles = cpu.step();

	EXPECT_EQ(6, numCycles);
    EXPECT_EQ(0x00, memory->read(0x8003));
	EXPECT_TRUE(cpu.getStatusFlag(CPU::StatusFlag::Z));
	EXPECT_FALSE(cpu.getStatusFlag(CPU::StatusFlag::N));
}

TEST_F(CPUTest, incAbsoluteXZero)
{
    cpu.setX(1);
	memory->addMemoryBlock(0x8000, { 0xFE, 0x02, 0x80, 0xAA });
	auto numCycles = cpu.step();

	EXPECT_EQ(7, numCycles);
    EXPECT_EQ(0xAB, memory->read(0x8003));
	EXPECT_FALSE(cpu.getStatusFlag(CPU::StatusFlag::Z));
	EXPECT_TRUE(cpu.getStatusFlag(CPU::StatusFlag::N));
}

TEST_F(CPUTest, incAbsoluteXRollOver)
{
    cpu.setX(1);
	memory->addMemoryBlock(0x8000, { 0xFE, 0x02, 0x80, 0xFF });
	auto numCycles = cpu.step();

	EXPECT_EQ(7, numCycles);
    EXPECT_EQ(0x00, memory->read(0x8003));
	EXPECT_TRUE(cpu.getStatusFlag(CPU::StatusFlag::Z));
	EXPECT_FALSE(cpu.getStatusFlag(CPU::StatusFlag::N));
}

TEST_F(CPUTest, inxZero)
{
    cpu.setX(0xAA);
	memory->addMemoryBlock(0x8000, { 0xE8 });
	auto numCycles = cpu.step();

	EXPECT_EQ(2, numCycles);
    EXPECT_EQ(0xAB, cpu.getX());
	EXPECT_FALSE(cpu.getStatusFlag(CPU::StatusFlag::Z));
	EXPECT_TRUE(cpu.getStatusFlag(CPU::StatusFlag::N));
}

TEST_F(CPUTest, inxRollOver)
{
    cpu.setX(0xFF);
	memory->addMemoryBlock(0x8000, { 0xE8 });
	auto numCycles = cpu.step();

	EXPECT_EQ(2, numCycles);
    EXPECT_EQ(0x00, cpu.getX());
	EXPECT_TRUE(cpu.getStatusFlag(CPU::StatusFlag::Z));
	EXPECT_FALSE(cpu.getStatusFlag(CPU::StatusFlag::N));
}

TEST_F(CPUTest, inyZero)
{
    cpu.setY(0xAA);
	memory->addMemoryBlock(0x8000, { 0xC8 });
	auto numCycles = cpu.step();

	EXPECT_EQ(2, numCycles);
    EXPECT_EQ(0xAB, cpu.getY());
	EXPECT_FALSE(cpu.getStatusFlag(CPU::StatusFlag::Z));
	EXPECT_TRUE(cpu.getStatusFlag(CPU::StatusFlag::N));
}

TEST_F(CPUTest, inyRollOver)
{
    cpu.setY(0xFF);
	memory->addMemoryBlock(0x8000, { 0xC8 });
	auto numCycles = cpu.step();

	EXPECT_EQ(2, numCycles);
    EXPECT_EQ(0x00, cpu.getY());
	EXPECT_TRUE(cpu.getStatusFlag(CPU::StatusFlag::Z));
	EXPECT_FALSE(cpu.getStatusFlag(CPU::StatusFlag::N));
}
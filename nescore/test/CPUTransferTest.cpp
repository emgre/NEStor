#include "CPUTest.h"

using namespace nescore;

TEST_F(CPUTest,  tax)
{
    cpu.setA(0x42);
    cpu.setX(0x00);
	memory->addMemoryBlock(0x8000, { 0xAA });
	auto numCycles = cpu.executeSingleInstruction();

	EXPECT_EQ(2, numCycles);
    EXPECT_EQ(0x42, cpu.getA());
    EXPECT_EQ(0x42, cpu.getX());
	EXPECT_FALSE(cpu.getStatusFlag(CPU::StatusFlag::Z));
	EXPECT_FALSE(cpu.getStatusFlag(CPU::StatusFlag::N));
}

TEST_F(CPUTest,  taxNegative)
{
    cpu.setA(0x82);
    cpu.setX(0x00);
	memory->addMemoryBlock(0x8000, { 0xAA });
	auto numCycles = cpu.executeSingleInstruction();

	EXPECT_EQ(2, numCycles);
    EXPECT_EQ(0x82, cpu.getA());
    EXPECT_EQ(0x82, cpu.getX());
	EXPECT_FALSE(cpu.getStatusFlag(CPU::StatusFlag::Z));
	EXPECT_TRUE(cpu.getStatusFlag(CPU::StatusFlag::N));
}

TEST_F(CPUTest,  taxZero)
{
	cpu.setA(0x00);
    cpu.setX(0x42);
	memory->addMemoryBlock(0x8000, { 0xAA });
	auto numCycles = cpu.executeSingleInstruction();

	EXPECT_EQ(2, numCycles);
    EXPECT_EQ(0x00, cpu.getA());
    EXPECT_EQ(0x00, cpu.getX());
	EXPECT_TRUE(cpu.getStatusFlag(CPU::StatusFlag::Z));
	EXPECT_FALSE(cpu.getStatusFlag(CPU::StatusFlag::N));
}

TEST_F(CPUTest,  tay)
{
    cpu.setA(0x42);
    cpu.setY(0x00);
	memory->addMemoryBlock(0x8000, { 0xA8 });
	auto numCycles = cpu.executeSingleInstruction();

	EXPECT_EQ(2, numCycles);
    EXPECT_EQ(0x42, cpu.getA());
    EXPECT_EQ(0x42, cpu.getY());
	EXPECT_FALSE(cpu.getStatusFlag(CPU::StatusFlag::Z));
	EXPECT_FALSE(cpu.getStatusFlag(CPU::StatusFlag::N));
}

TEST_F(CPUTest,  tayNegative)
{
    cpu.setA(0x82);
    cpu.setY(0x00);
	memory->addMemoryBlock(0x8000, { 0xA8 });
	auto numCycles = cpu.executeSingleInstruction();

	EXPECT_EQ(2, numCycles);
    EXPECT_EQ(0x82, cpu.getA());
    EXPECT_EQ(0x82, cpu.getY());
	EXPECT_FALSE(cpu.getStatusFlag(CPU::StatusFlag::Z));
	EXPECT_TRUE(cpu.getStatusFlag(CPU::StatusFlag::N));
}

TEST_F(CPUTest,  tayZero)
{
	cpu.setA(0x00);
    cpu.setY(0x42);
	memory->addMemoryBlock(0x8000, { 0xA8 });
	auto numCycles = cpu.executeSingleInstruction();

	EXPECT_EQ(2, numCycles);
    EXPECT_EQ(0x00, cpu.getA());
    EXPECT_EQ(0x00, cpu.getY());
	EXPECT_TRUE(cpu.getStatusFlag(CPU::StatusFlag::Z));
	EXPECT_FALSE(cpu.getStatusFlag(CPU::StatusFlag::N));
}

TEST_F(CPUTest,  tsx)
{
    cpu.setSP(0x42);
    cpu.setX(0x00);
	memory->addMemoryBlock(0x8000, { 0xBA });
	auto numCycles = cpu.executeSingleInstruction();

	EXPECT_EQ(2, numCycles);
    EXPECT_EQ(0x42, cpu.getSP());
    EXPECT_EQ(0x42, cpu.getX());
	EXPECT_FALSE(cpu.getStatusFlag(CPU::StatusFlag::Z));
	EXPECT_FALSE(cpu.getStatusFlag(CPU::StatusFlag::N));
}

TEST_F(CPUTest,  tsxNegative)
{
    cpu.setSP(0x82);
    cpu.setX(0x00);
	memory->addMemoryBlock(0x8000, { 0xBA });
	auto numCycles = cpu.executeSingleInstruction();

	EXPECT_EQ(2, numCycles);
    EXPECT_EQ(0x82, cpu.getSP());
    EXPECT_EQ(0x82, cpu.getX());
	EXPECT_FALSE(cpu.getStatusFlag(CPU::StatusFlag::Z));
	EXPECT_TRUE(cpu.getStatusFlag(CPU::StatusFlag::N));
}

TEST_F(CPUTest,  tsxZero)
{
	cpu.setSP(0x00);
    cpu.setX(0x42);
	memory->addMemoryBlock(0x8000, { 0xBA });
	auto numCycles = cpu.executeSingleInstruction();

	EXPECT_EQ(2, numCycles);
    EXPECT_EQ(0x00, cpu.getSP());
    EXPECT_EQ(0x00, cpu.getX());
	EXPECT_TRUE(cpu.getStatusFlag(CPU::StatusFlag::Z));
	EXPECT_FALSE(cpu.getStatusFlag(CPU::StatusFlag::N));
}

TEST_F(CPUTest,  txa)
{
    cpu.setX(0x42);
    cpu.setA(0x00);
	memory->addMemoryBlock(0x8000, { 0x8A });
	auto numCycles = cpu.executeSingleInstruction();

	EXPECT_EQ(2, numCycles);
    EXPECT_EQ(0x42, cpu.getX());
    EXPECT_EQ(0x42, cpu.getA());
	EXPECT_FALSE(cpu.getStatusFlag(CPU::StatusFlag::Z));
	EXPECT_FALSE(cpu.getStatusFlag(CPU::StatusFlag::N));
}

TEST_F(CPUTest,  txaNegative)
{
    cpu.setX(0x82);
    cpu.setA(0x00);
	memory->addMemoryBlock(0x8000, { 0x8A });
	auto numCycles = cpu.executeSingleInstruction();

	EXPECT_EQ(2, numCycles);
    EXPECT_EQ(0x82, cpu.getX());
    EXPECT_EQ(0x82, cpu.getA());
	EXPECT_FALSE(cpu.getStatusFlag(CPU::StatusFlag::Z));
	EXPECT_TRUE(cpu.getStatusFlag(CPU::StatusFlag::N));
}

TEST_F(CPUTest,  txaZero)
{
	cpu.setX(0x00);
    cpu.setA(0x42);
	memory->addMemoryBlock(0x8000, { 0x8A });
	auto numCycles = cpu.executeSingleInstruction();

	EXPECT_EQ(2, numCycles);
    EXPECT_EQ(0x00, cpu.getX());
    EXPECT_EQ(0x00, cpu.getA());
	EXPECT_TRUE(cpu.getStatusFlag(CPU::StatusFlag::Z));
	EXPECT_FALSE(cpu.getStatusFlag(CPU::StatusFlag::N));
}

TEST_F(CPUTest,  txs)
{
    cpu.setX(0x42);
    cpu.setSP(0x00);
	memory->addMemoryBlock(0x8000, { 0x9A });
	auto numCycles = cpu.executeSingleInstruction();

	EXPECT_EQ(2, numCycles);
    EXPECT_EQ(0x42, cpu.getX());
    EXPECT_EQ(0x42, cpu.getSP());
	EXPECT_FALSE(cpu.getStatusFlag(CPU::StatusFlag::Z));
	EXPECT_FALSE(cpu.getStatusFlag(CPU::StatusFlag::N));
}

TEST_F(CPUTest,  txsNegative)
{
    cpu.setX(0x82);
    cpu.setSP(0x00);
	memory->addMemoryBlock(0x8000, { 0x9A });
	auto numCycles = cpu.executeSingleInstruction();

	EXPECT_EQ(2, numCycles);
    EXPECT_EQ(0x82, cpu.getX());
    EXPECT_EQ(0x82, cpu.getSP());
	EXPECT_FALSE(cpu.getStatusFlag(CPU::StatusFlag::Z));
	EXPECT_FALSE(cpu.getStatusFlag(CPU::StatusFlag::N));
}

TEST_F(CPUTest,  txsZero)
{
	cpu.setX(0x00);
    cpu.setSP(0x42);
	memory->addMemoryBlock(0x8000, { 0x9A });
	auto numCycles = cpu.executeSingleInstruction();

	EXPECT_EQ(2, numCycles);
    EXPECT_EQ(0x00, cpu.getX());
    EXPECT_EQ(0x00, cpu.getSP());
	EXPECT_FALSE(cpu.getStatusFlag(CPU::StatusFlag::Z));
	EXPECT_FALSE(cpu.getStatusFlag(CPU::StatusFlag::N));
}

TEST_F(CPUTest,  tya)
{
    cpu.setY(0x42);
    cpu.setA(0x00);
	memory->addMemoryBlock(0x8000, { 0x98 });
	auto numCycles = cpu.executeSingleInstruction();

	EXPECT_EQ(2, numCycles);
    EXPECT_EQ(0x42, cpu.getY());
    EXPECT_EQ(0x42, cpu.getA());
	EXPECT_FALSE(cpu.getStatusFlag(CPU::StatusFlag::Z));
	EXPECT_FALSE(cpu.getStatusFlag(CPU::StatusFlag::N));
}

TEST_F(CPUTest,  tyaNegative)
{
    cpu.setY(0x82);
    cpu.setA(0x00);
	memory->addMemoryBlock(0x8000, { 0x98 });
	auto numCycles = cpu.executeSingleInstruction();

	EXPECT_EQ(2, numCycles);
    EXPECT_EQ(0x82, cpu.getY());
    EXPECT_EQ(0x82, cpu.getA());
	EXPECT_FALSE(cpu.getStatusFlag(CPU::StatusFlag::Z));
	EXPECT_TRUE(cpu.getStatusFlag(CPU::StatusFlag::N));
}

TEST_F(CPUTest,  tyaZero)
{
	cpu.setY(0x00);
    cpu.setA(0x42);
	memory->addMemoryBlock(0x8000, { 0x98 });
	auto numCycles = cpu.executeSingleInstruction();

	EXPECT_EQ(2, numCycles);
    EXPECT_EQ(0x00, cpu.getY());
    EXPECT_EQ(0x00, cpu.getA());
	EXPECT_TRUE(cpu.getStatusFlag(CPU::StatusFlag::Z));
	EXPECT_FALSE(cpu.getStatusFlag(CPU::StatusFlag::N));
}
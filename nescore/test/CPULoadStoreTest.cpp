#include "CPUTest.h"

using namespace nescore;

TEST_F(CPUTest, ldaImmediateNegative)
{
	memory->addMemoryBlock(0x8000, { 0xA9, 0x82 });
	auto numCycles = cpu.step();

	EXPECT_EQ(2, numCycles);
    EXPECT_EQ(0x82, cpu.getA());
	EXPECT_FALSE(cpu.getStatusFlag(CPU::StatusFlag::Z));
	EXPECT_TRUE(cpu.getStatusFlag(CPU::StatusFlag::N));
}

TEST_F(CPUTest, ldaImmediateZero)
{
	memory->addMemoryBlock(0x8000, { 0xA9, 0x00 });
	auto numCycles = cpu.step();

	EXPECT_EQ(2, numCycles);
    EXPECT_EQ(0x00, cpu.getA());
	EXPECT_TRUE(cpu.getStatusFlag(CPU::StatusFlag::Z));
	EXPECT_FALSE(cpu.getStatusFlag(CPU::StatusFlag::N));
}

TEST_F(CPUTest, ldaZeroPageNegative)
{
	memory->addMemoryBlock(0x8000, { 0xA5, 0x42 });
    memory->addMemoryBlock(0x42, { 0x82 });
	auto numCycles = cpu.step();

	EXPECT_EQ(3, numCycles);
    EXPECT_EQ(0x82, cpu.getA());
	EXPECT_FALSE(cpu.getStatusFlag(CPU::StatusFlag::Z));
	EXPECT_TRUE(cpu.getStatusFlag(CPU::StatusFlag::N));
}

TEST_F(CPUTest, ldaZeroPageZero)
{
	memory->addMemoryBlock(0x8000, { 0xA5, 0x42 });
    memory->addMemoryBlock(0x42, { 0x00 });
	auto numCycles = cpu.step();

	EXPECT_EQ(3, numCycles);
    EXPECT_EQ(0x00, cpu.getA());
	EXPECT_TRUE(cpu.getStatusFlag(CPU::StatusFlag::Z));
	EXPECT_FALSE(cpu.getStatusFlag(CPU::StatusFlag::N));
}

TEST_F(CPUTest, ldaZeroPageXNegative)
{
    cpu.setX(1);
	memory->addMemoryBlock(0x8000, { 0xB5, 0x41 });
    memory->addMemoryBlock(0x42, { 0x82 });
	auto numCycles = cpu.step();

	EXPECT_EQ(4, numCycles);
    EXPECT_EQ(0x82, cpu.getA());
	EXPECT_FALSE(cpu.getStatusFlag(CPU::StatusFlag::Z));
	EXPECT_TRUE(cpu.getStatusFlag(CPU::StatusFlag::N));
}

TEST_F(CPUTest, ldaZeroPageXZero)
{
	cpu.setX(1);
	memory->addMemoryBlock(0x8000, { 0xB5, 0x41 });
    memory->addMemoryBlock(0x42, { 0x00 });
	auto numCycles = cpu.step();

	EXPECT_EQ(4, numCycles);
    EXPECT_EQ(0x00, cpu.getA());
	EXPECT_TRUE(cpu.getStatusFlag(CPU::StatusFlag::Z));
	EXPECT_FALSE(cpu.getStatusFlag(CPU::StatusFlag::N));
}

TEST_F(CPUTest, ldaAbsoluteNegative)
{
	memory->addMemoryBlock(0x8000, { 0xAD, 0x03, 0x80, 0x82 });
	auto numCycles = cpu.step();

	EXPECT_EQ(4, numCycles);
    EXPECT_EQ(0x82, cpu.getA());
	EXPECT_FALSE(cpu.getStatusFlag(CPU::StatusFlag::Z));
	EXPECT_TRUE(cpu.getStatusFlag(CPU::StatusFlag::N));
}

TEST_F(CPUTest, ldaAbsoluteZero)
{
	memory->addMemoryBlock(0x8000, { 0xAD, 0x03, 0x80, 0x00 });
	auto numCycles = cpu.step();

	EXPECT_EQ(4, numCycles);
    EXPECT_EQ(0x00, cpu.getA());
	EXPECT_TRUE(cpu.getStatusFlag(CPU::StatusFlag::Z));
	EXPECT_FALSE(cpu.getStatusFlag(CPU::StatusFlag::N));
}

TEST_F(CPUTest, ldaAbsoluteXNegative)
{
    cpu.setX(1);
	memory->addMemoryBlock(0x8000, { 0xBD, 0x02, 0x80, 0x82 });
	auto numCycles = cpu.step();

	EXPECT_EQ(4, numCycles);
    EXPECT_EQ(0x82, cpu.getA());
	EXPECT_FALSE(cpu.getStatusFlag(CPU::StatusFlag::Z));
	EXPECT_TRUE(cpu.getStatusFlag(CPU::StatusFlag::N));
}

TEST_F(CPUTest, ldaAbsoluteXZero)
{
    cpu.setX(1);
    memory->addMemoryBlock(0x8000, { 0xBD, 0x02, 0x80, 0x00 });
	auto numCycles = cpu.step();

	EXPECT_EQ(4, numCycles);
    EXPECT_EQ(0x00, cpu.getA());
	EXPECT_TRUE(cpu.getStatusFlag(CPU::StatusFlag::Z));
	EXPECT_FALSE(cpu.getStatusFlag(CPU::StatusFlag::N));
}

TEST_F(CPUTest, ldaAbsoluteXPageCrossing)
{
    cpu.setX(1);
    memory->addMemoryBlock(0x8000, { 0xBD, 0xFF, 0x80 });
    memory->addMemoryBlock(0x8100, { 0x82 });
	auto numCycles = cpu.step();

	EXPECT_EQ(5, numCycles);
    EXPECT_EQ(0x82, cpu.getA());
	EXPECT_FALSE(cpu.getStatusFlag(CPU::StatusFlag::Z));
	EXPECT_TRUE(cpu.getStatusFlag(CPU::StatusFlag::N));
}

TEST_F(CPUTest, ldaAbsoluteYNegative)
{
    cpu.setY(1);
	memory->addMemoryBlock(0x8000, { 0xB9, 0x02, 0x80, 0x82 });
	auto numCycles = cpu.step();

	EXPECT_EQ(4, numCycles);
    EXPECT_EQ(0x82, cpu.getA());
	EXPECT_FALSE(cpu.getStatusFlag(CPU::StatusFlag::Z));
	EXPECT_TRUE(cpu.getStatusFlag(CPU::StatusFlag::N));
}

TEST_F(CPUTest, ldaAbsoluteYZero)
{
    cpu.setY(1);
    memory->addMemoryBlock(0x8000, { 0xB9, 0x02, 0x80, 0x00 });
	auto numCycles = cpu.step();

	EXPECT_EQ(4, numCycles);
    EXPECT_EQ(0x00, cpu.getA());
	EXPECT_TRUE(cpu.getStatusFlag(CPU::StatusFlag::Z));
	EXPECT_FALSE(cpu.getStatusFlag(CPU::StatusFlag::N));
}

TEST_F(CPUTest, ldaAbsoluteYPageCrossing)
{
    cpu.setY(1);
    memory->addMemoryBlock(0x8000, { 0xB9, 0xFF, 0x80 });
    memory->addMemoryBlock(0x8100, { 0x42 });
	auto numCycles = cpu.step();

	EXPECT_EQ(5, numCycles);
    EXPECT_EQ(0x42, cpu.getA());
	EXPECT_FALSE(cpu.getStatusFlag(CPU::StatusFlag::Z));
	EXPECT_FALSE(cpu.getStatusFlag(CPU::StatusFlag::N));
}

TEST_F(CPUTest, ldaIndirectXNegative)
{
    cpu.setX(1);
	memory->addMemoryBlock(0x8000, { 0xA1, 0x00 });
	memory->addMemoryBlock(0x0001, { 0x03, 0x00, 0x82 });
	auto numCycles = cpu.step();

	EXPECT_EQ(6, numCycles);
    EXPECT_EQ(0x82, cpu.getA());
	EXPECT_FALSE(cpu.getStatusFlag(CPU::StatusFlag::Z));
	EXPECT_TRUE(cpu.getStatusFlag(CPU::StatusFlag::N));
}

TEST_F(CPUTest, ldaIndirectXZero)
{
    cpu.setX(1);
    memory->addMemoryBlock(0x8000, { 0xA1, 0x00, 0x00 });
	memory->addMemoryBlock(0x0001, { 0x02, 0x80});
	auto numCycles = cpu.step();

	EXPECT_EQ(6, numCycles);
    EXPECT_EQ(0x00, cpu.getA());
	EXPECT_TRUE(cpu.getStatusFlag(CPU::StatusFlag::Z));
	EXPECT_FALSE(cpu.getStatusFlag(CPU::StatusFlag::N));
}

TEST_F(CPUTest, ldaIndirectYNegative)
{
    cpu.setY(1);
	memory->addMemoryBlock(0x8000, { 0xB1, 0x42, 0x82 });
	memory->addMemoryBlock(0x0042, { 0x01, 0x80 });
	auto numCycles = cpu.step();

	EXPECT_EQ(5, numCycles);
    EXPECT_EQ(0x82, cpu.getA());
	EXPECT_FALSE(cpu.getStatusFlag(CPU::StatusFlag::Z));
	EXPECT_TRUE(cpu.getStatusFlag(CPU::StatusFlag::N));
}

TEST_F(CPUTest, ldaIndirectYZero)
{
    cpu.setY(1);
    memory->addMemoryBlock(0x8000, { 0xB1, 0x42 });
	memory->addMemoryBlock(0x0042, { 0x43, 0x00, 0x00 });
	auto numCycles = cpu.step();

	EXPECT_EQ(5, numCycles);
    EXPECT_EQ(0x00, cpu.getA());
	EXPECT_TRUE(cpu.getStatusFlag(CPU::StatusFlag::Z));
	EXPECT_FALSE(cpu.getStatusFlag(CPU::StatusFlag::N));
}

TEST_F(CPUTest, ldaIndirectYPageCrossing)
{
    cpu.setY(1);
	memory->addMemoryBlock(0x8000, { 0xB1, 0x42 });
	memory->addMemoryBlock(0x0042, { 0xFF, 0x80 });
	memory->addMemoryBlock(0x8100, { 0x42 });
	auto numCycles = cpu.step();

	EXPECT_EQ(6, numCycles);
    EXPECT_EQ(0x42, cpu.getA());
	EXPECT_FALSE(cpu.getStatusFlag(CPU::StatusFlag::Z));
	EXPECT_FALSE(cpu.getStatusFlag(CPU::StatusFlag::N));
}

TEST_F(CPUTest, ldxImmediateNegative)
{
	memory->addMemoryBlock(0x8000, { 0xA2, 0x82 });
	auto numCycles = cpu.step();

	EXPECT_EQ(2, numCycles);
    EXPECT_EQ(0x82, cpu.getX());
	EXPECT_FALSE(cpu.getStatusFlag(CPU::StatusFlag::Z));
	EXPECT_TRUE(cpu.getStatusFlag(CPU::StatusFlag::N));
}

TEST_F(CPUTest, ldxImmediateZero)
{
	memory->addMemoryBlock(0x8000, { 0xA2, 0x00 });
	auto numCycles = cpu.step();

	EXPECT_EQ(2, numCycles);
    EXPECT_EQ(0x00, cpu.getX());
	EXPECT_TRUE(cpu.getStatusFlag(CPU::StatusFlag::Z));
	EXPECT_FALSE(cpu.getStatusFlag(CPU::StatusFlag::N));
}

TEST_F(CPUTest, ldxZeroPageNegative)
{
	memory->addMemoryBlock(0x8000, { 0xA6, 0x42 });
    memory->addMemoryBlock(0x42, { 0x82 });
	auto numCycles = cpu.step();

	EXPECT_EQ(3, numCycles);
    EXPECT_EQ(0x82, cpu.getX());
	EXPECT_FALSE(cpu.getStatusFlag(CPU::StatusFlag::Z));
	EXPECT_TRUE(cpu.getStatusFlag(CPU::StatusFlag::N));
}

TEST_F(CPUTest, ldxZeroPageZero)
{
	memory->addMemoryBlock(0x8000, { 0xA6, 0x42 });
    memory->addMemoryBlock(0x42, { 0x00 });
	auto numCycles = cpu.step();

	EXPECT_EQ(3, numCycles);
    EXPECT_EQ(0x00, cpu.getX());
	EXPECT_TRUE(cpu.getStatusFlag(CPU::StatusFlag::Z));
	EXPECT_FALSE(cpu.getStatusFlag(CPU::StatusFlag::N));
}

TEST_F(CPUTest, ldxZeroPageYNegative)
{
    cpu.setY(1);
	memory->addMemoryBlock(0x8000, { 0xB6, 0x41 });
    memory->addMemoryBlock(0x42, { 0x82 });
	auto numCycles = cpu.step();

	EXPECT_EQ(4, numCycles);
    EXPECT_EQ(0x82, cpu.getX());
	EXPECT_FALSE(cpu.getStatusFlag(CPU::StatusFlag::Z));
	EXPECT_TRUE(cpu.getStatusFlag(CPU::StatusFlag::N));
}

TEST_F(CPUTest, ldxZeroPageYZero)
{
	cpu.setY(1);
	memory->addMemoryBlock(0x8000, { 0xB6, 0x41 });
    memory->addMemoryBlock(0x42, { 0x00 });
	auto numCycles = cpu.step();

	EXPECT_EQ(4, numCycles);
    EXPECT_EQ(0x00, cpu.getX());
	EXPECT_TRUE(cpu.getStatusFlag(CPU::StatusFlag::Z));
	EXPECT_FALSE(cpu.getStatusFlag(CPU::StatusFlag::N));
}

TEST_F(CPUTest, ldxAbsoluteNegative)
{
	memory->addMemoryBlock(0x8000, { 0xAE, 0x03, 0x80, 0x82 });
	auto numCycles = cpu.step();

	EXPECT_EQ(4, numCycles);
    EXPECT_EQ(0x82, cpu.getX());
	EXPECT_FALSE(cpu.getStatusFlag(CPU::StatusFlag::Z));
	EXPECT_TRUE(cpu.getStatusFlag(CPU::StatusFlag::N));
}

TEST_F(CPUTest, ldxAbsoluteZero)
{
	memory->addMemoryBlock(0x8000, { 0xAE, 0x03, 0x80, 0x00 });
	auto numCycles = cpu.step();

	EXPECT_EQ(4, numCycles);
    EXPECT_EQ(0x00, cpu.getX());
	EXPECT_TRUE(cpu.getStatusFlag(CPU::StatusFlag::Z));
	EXPECT_FALSE(cpu.getStatusFlag(CPU::StatusFlag::N));
}

TEST_F(CPUTest, ldxAbsoluteYNegative)
{
    cpu.setY(1);
	memory->addMemoryBlock(0x8000, { 0xBE, 0x02, 0x80, 0x82 });
	auto numCycles = cpu.step();

	EXPECT_EQ(4, numCycles);
    EXPECT_EQ(0x82, cpu.getX());
	EXPECT_FALSE(cpu.getStatusFlag(CPU::StatusFlag::Z));
	EXPECT_TRUE(cpu.getStatusFlag(CPU::StatusFlag::N));
}

TEST_F(CPUTest, ldxAbsoluteYZero)
{
    cpu.setY(1);
    memory->addMemoryBlock(0x8000, { 0xBE, 0x02, 0x80, 0x00 });
	auto numCycles = cpu.step();

	EXPECT_EQ(4, numCycles);
    EXPECT_EQ(0x00, cpu.getX());
	EXPECT_TRUE(cpu.getStatusFlag(CPU::StatusFlag::Z));
	EXPECT_FALSE(cpu.getStatusFlag(CPU::StatusFlag::N));
}

TEST_F(CPUTest, ldxAbsoluteYPageCrossing)
{
    cpu.setY(1);
    memory->addMemoryBlock(0x8000, { 0xBE, 0xFF, 0x80 });
    memory->addMemoryBlock(0x8100, { 0x82 });
	auto numCycles = cpu.step();

	EXPECT_EQ(5, numCycles);
    EXPECT_EQ(0x82, cpu.getX());
	EXPECT_FALSE(cpu.getStatusFlag(CPU::StatusFlag::Z));
	EXPECT_TRUE(cpu.getStatusFlag(CPU::StatusFlag::N));
}

TEST_F(CPUTest, ldyImmediateNegative)
{
	memory->addMemoryBlock(0x8000, { 0xA0, 0x82 });
	auto numCycles = cpu.step();

	EXPECT_EQ(2, numCycles);
    EXPECT_EQ(0x82, cpu.getY());
	EXPECT_FALSE(cpu.getStatusFlag(CPU::StatusFlag::Z));
	EXPECT_TRUE(cpu.getStatusFlag(CPU::StatusFlag::N));
}

TEST_F(CPUTest, ldyImmediateZero)
{
	memory->addMemoryBlock(0x8000, { 0xA0, 0x00 });
	auto numCycles = cpu.step();

	EXPECT_EQ(2, numCycles);
    EXPECT_EQ(0x00, cpu.getY());
	EXPECT_TRUE(cpu.getStatusFlag(CPU::StatusFlag::Z));
	EXPECT_FALSE(cpu.getStatusFlag(CPU::StatusFlag::N));
}

TEST_F(CPUTest, ldyZeroPageNegative)
{
	memory->addMemoryBlock(0x8000, { 0xA4, 0x42 });
    memory->addMemoryBlock(0x42, { 0x82 });
	auto numCycles = cpu.step();

	EXPECT_EQ(3, numCycles);
    EXPECT_EQ(0x82, cpu.getY());
	EXPECT_FALSE(cpu.getStatusFlag(CPU::StatusFlag::Z));
	EXPECT_TRUE(cpu.getStatusFlag(CPU::StatusFlag::N));
}

TEST_F(CPUTest, ldyZeroPageZero)
{
	memory->addMemoryBlock(0x8000, { 0xA4, 0x42 });
    memory->addMemoryBlock(0x42, { 0x00 });
	auto numCycles = cpu.step();

	EXPECT_EQ(3, numCycles);
    EXPECT_EQ(0x00, cpu.getY());
	EXPECT_TRUE(cpu.getStatusFlag(CPU::StatusFlag::Z));
	EXPECT_FALSE(cpu.getStatusFlag(CPU::StatusFlag::N));
}

TEST_F(CPUTest, ldyZeroPageXNegative)
{
    cpu.setX(1);
	memory->addMemoryBlock(0x8000, { 0xB4, 0x41 });
    memory->addMemoryBlock(0x42, { 0x82 });
	auto numCycles = cpu.step();

	EXPECT_EQ(4, numCycles);
    EXPECT_EQ(0x82, cpu.getY());
	EXPECT_FALSE(cpu.getStatusFlag(CPU::StatusFlag::Z));
	EXPECT_TRUE(cpu.getStatusFlag(CPU::StatusFlag::N));
}

TEST_F(CPUTest, ldyZeroPageXZero)
{
	cpu.setX(1);
	memory->addMemoryBlock(0x8000, { 0xB4, 0x41 });
    memory->addMemoryBlock(0x42, { 0x00 });
	auto numCycles = cpu.step();

	EXPECT_EQ(4, numCycles);
    EXPECT_EQ(0x00, cpu.getY());
	EXPECT_TRUE(cpu.getStatusFlag(CPU::StatusFlag::Z));
	EXPECT_FALSE(cpu.getStatusFlag(CPU::StatusFlag::N));
}

TEST_F(CPUTest, ldyAbsoluteNegative)
{
	memory->addMemoryBlock(0x8000, { 0xAC, 0x03, 0x80, 0x82 });
	auto numCycles = cpu.step();

	EXPECT_EQ(4, numCycles);
    EXPECT_EQ(0x82, cpu.getY());
	EXPECT_FALSE(cpu.getStatusFlag(CPU::StatusFlag::Z));
	EXPECT_TRUE(cpu.getStatusFlag(CPU::StatusFlag::N));
}

TEST_F(CPUTest, ldyAbsoluteZero)
{
	memory->addMemoryBlock(0x8000, { 0xAC, 0x03, 0x80, 0x00 });
	auto numCycles = cpu.step();

	EXPECT_EQ(4, numCycles);
    EXPECT_EQ(0x00, cpu.getY());
	EXPECT_TRUE(cpu.getStatusFlag(CPU::StatusFlag::Z));
	EXPECT_FALSE(cpu.getStatusFlag(CPU::StatusFlag::N));
}

TEST_F(CPUTest, ldyAbsoluteXNegative)
{
    cpu.setX(1);
	memory->addMemoryBlock(0x8000, { 0xBC, 0x02, 0x80, 0x82 });
	auto numCycles = cpu.step();

	EXPECT_EQ(4, numCycles);
    EXPECT_EQ(0x82, cpu.getY());
	EXPECT_FALSE(cpu.getStatusFlag(CPU::StatusFlag::Z));
	EXPECT_TRUE(cpu.getStatusFlag(CPU::StatusFlag::N));
}

TEST_F(CPUTest, ldyAbsoluteXZero)
{
    cpu.setX(1);
    memory->addMemoryBlock(0x8000, { 0xBC, 0x02, 0x80, 0x00 });
	auto numCycles = cpu.step();

	EXPECT_EQ(4, numCycles);
    EXPECT_EQ(0x00, cpu.getY());
	EXPECT_TRUE(cpu.getStatusFlag(CPU::StatusFlag::Z));
	EXPECT_FALSE(cpu.getStatusFlag(CPU::StatusFlag::N));
}

TEST_F(CPUTest, ldyAbsoluteXPageCrossing)
{
    cpu.setX(1);
    memory->addMemoryBlock(0x8000, { 0xBC, 0xFF, 0x80 });
    memory->addMemoryBlock(0x8100, { 0x82 });
	auto numCycles = cpu.step();

	EXPECT_EQ(5, numCycles);
    EXPECT_EQ(0x82, cpu.getY());
	EXPECT_FALSE(cpu.getStatusFlag(CPU::StatusFlag::Z));
	EXPECT_TRUE(cpu.getStatusFlag(CPU::StatusFlag::N));
}

TEST_F(CPUTest, staZeroPage)
{
	cpu.setA(0x42);
	memory->addMemoryBlock(0x8000, { 0x85, 0x21 });
	auto numCycles = cpu.step();

	EXPECT_EQ(3, numCycles);
	EXPECT_EQ(0x42, memory->read(0x0021));
}

TEST_F(CPUTest, staZeroPageX)
{
	cpu.setA(0x42);
	cpu.setX(1);
	memory->addMemoryBlock(0x8000, { 0x95, 0x21 });
	auto numCycles = cpu.step();

	EXPECT_EQ(4, numCycles);
	EXPECT_EQ(0x42, memory->read(0x0022));
}

TEST_F(CPUTest, staAbsolute)
{
	cpu.setA(0x42);
	memory->addMemoryBlock(0x8000, { 0x8D, 0x03, 0x80 });
	auto numCycles = cpu.step();

	EXPECT_EQ(4, numCycles);
	EXPECT_EQ(0x42, memory->read(0x8003));
}

TEST_F(CPUTest, staAbsoluteX)
{
	cpu.setA(0x42);
	cpu.setX(1);
	memory->addMemoryBlock(0x8000, { 0x9D, 0x03, 0x80 });
	auto numCycles = cpu.step();

	EXPECT_EQ(5, numCycles);
	EXPECT_EQ(0x42, memory->read(0x8004));
}

TEST_F(CPUTest, staAbsoluteY)
{
	cpu.setA(0x42);
	cpu.setY(1);
	memory->addMemoryBlock(0x8000, { 0x99, 0x03, 0x80 });
	auto numCycles = cpu.step();

	EXPECT_EQ(5, numCycles);
	EXPECT_EQ(0x42, memory->read(0x8004));
}

TEST_F(CPUTest, staIndirectX)
{
	cpu.setA(0x42);
	cpu.setX(1);
	memory->addMemoryBlock(0x8000, { 0x81, 0x20 });
	memory->addMemoryBlock(0x0021, { 0x02, 0x80 });
	auto numCycles = cpu.step();

	EXPECT_EQ(6, numCycles);
	EXPECT_EQ(0x42, memory->read(0x8002));
}

TEST_F(CPUTest, staIndirectY)
{
	cpu.setA(0x42);
	cpu.setY(1);
	memory->addMemoryBlock(0x8000, { 0x91, 0x20 });
	memory->addMemoryBlock(0x0020, { 0x01, 0x80 });
	auto numCycles = cpu.step();

	EXPECT_EQ(6, numCycles);
	EXPECT_EQ(0x42, memory->read(0x8002));
}

TEST_F(CPUTest, stxZeroPage)
{
	cpu.setX(0x42);
	memory->addMemoryBlock(0x8000, { 0x86, 0x21 });
	auto numCycles = cpu.step();

	EXPECT_EQ(3, numCycles);
	EXPECT_EQ(0x42, memory->read(0x0021));
}

TEST_F(CPUTest, stxZeroPageY)
{
	cpu.setX(0x42);
	cpu.setY(1);
	memory->addMemoryBlock(0x8000, { 0x96, 0x21 });
	auto numCycles = cpu.step();

	EXPECT_EQ(4, numCycles);
	EXPECT_EQ(0x42, memory->read(0x0022));
}

TEST_F(CPUTest, stxAbsolute)
{
	cpu.setX(0x42);
	memory->addMemoryBlock(0x8000, { 0x8E, 0x03, 0x80 });
	auto numCycles = cpu.step();

	EXPECT_EQ(4, numCycles);
	EXPECT_EQ(0x42, memory->read(0x8003));
}

TEST_F(CPUTest, styZeroPage)
{
	cpu.setY(0x42);
	memory->addMemoryBlock(0x8000, { 0x84, 0x21 });
	auto numCycles = cpu.step();

	EXPECT_EQ(3, numCycles);
	EXPECT_EQ(0x42, memory->read(0x0021));
}

TEST_F(CPUTest, styZeroPageX)
{
	cpu.setY(0x42);
	cpu.setX(1);
	memory->addMemoryBlock(0x8000, { 0x94, 0x21 });
	auto numCycles = cpu.step();

	EXPECT_EQ(4, numCycles);
	EXPECT_EQ(0x42, memory->read(0x0022));
}

TEST_F(CPUTest, styAbsolute)
{
	cpu.setY(0x42);
	memory->addMemoryBlock(0x8000, { 0x8C, 0x03, 0x80 });
	auto numCycles = cpu.step();

	EXPECT_EQ(4, numCycles);
	EXPECT_EQ(0x42, memory->read(0x8003));
}
#include "CPUTest.h"

using namespace nescore;

TEST_F(CPUTest, nop)
{
    cpu.setStatusFlag(CPU::StatusFlag::Z, true);
    cpu.setStatusFlag(CPU::StatusFlag::N, true);
    cpu.setStatusFlag(CPU::StatusFlag::C, true);
    cpu.setStatusFlag(CPU::StatusFlag::V, true);
    cpu.setA(0x42);
    cpu.setX(0x42);
    cpu.setY(0x42);

	memory.addMemoryBlock(0x8000, { 0xEA });
	auto numCycles = cpu.executeSingleInstruction();

	EXPECT_EQ(2, numCycles);
	EXPECT_TRUE(cpu.getStatusFlag(CPU::StatusFlag::Z));
    EXPECT_TRUE(cpu.getStatusFlag(CPU::StatusFlag::N));
    EXPECT_TRUE(cpu.getStatusFlag(CPU::StatusFlag::C));
    EXPECT_TRUE(cpu.getStatusFlag(CPU::StatusFlag::V));
    EXPECT_EQ(0x42, cpu.getA());
    EXPECT_EQ(0x42, cpu.getX());
    EXPECT_EQ(0x42, cpu.getY());
}
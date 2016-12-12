#include "gtest/gtest.h"
#include "CPU.h"
#include "IMemory.h"

using namespace nescore;

// Memory test is a simple IMemory implementation where
// you can write whatever you want in it, without using
// kilobytes of RAM.
class MemoryTest : public IMemory
{
public:

	// Remove all blocks
	void clear()
	{
		m_blocks.clear();
	}

	// Add a memory block starting at the specified address.
	// Note that if two blocks overlap, the latest one is used.
	void addMemoryBlock(WORD address, const std::vector<BYTE>& data)
	{
		m_blocks.push_back(SMemoryBlock({
			address,
			data
		}));
	}

	virtual BYTE read(WORD address)
	{
		auto pMemoryBlock = getMemoryBlock(address);
		if (pMemoryBlock)
		{
			return pMemoryBlock->data[address - pMemoryBlock->address];
		}

		return 0x00;
	}

	virtual void write(WORD address, BYTE value)
	{
		auto pMemoryBlock = getMemoryBlock(address);
		if (pMemoryBlock)
		{
			pMemoryBlock->data[address - pMemoryBlock->address] = value;
		}
		else
		{
			addMemoryBlock(address, { value });
		}
	}

private:
	struct SMemoryBlock
	{
		WORD address;
		std::vector<BYTE> data;

		WORD getSize() const
		{
			return (WORD)data.size();
		}
	};

	// Returns the memory block for the address, or nullptr if no memory block exists.
	SMemoryBlock* getMemoryBlock(WORD address)
	{
		// We use a reverse iterator in order to get the latest block.
		for (auto it = m_blocks.rbegin(); it != m_blocks.rend(); it++)
		{
			if ((address >= (*it).address) && (address < (*it).address + (*it).getSize()))
			{
				return &(*it);
			}
		}

		return nullptr;
	}

	std::vector<SMemoryBlock> m_blocks;
};

class CPUTest : public ::testing::Test
{
public:
	CPUTest()
	:cpu(memory)
	{
	}

	CPU cpu;
	MemoryTest memory;
};

TEST_F(CPUTest, reset)
{
	cpu.setA(0x42);
	cpu.setX(0x42);
	cpu.setY(0x42);
	cpu.setPC(0x42);
}

TEST_F(CPUTest, setGetAndPopPC)
{
	// Set and get on random value
	cpu.setPC(0x0042);
	EXPECT_EQ(0x0042, cpu.getPC());

	// Pop operation
	EXPECT_EQ(0x0042, cpu.popPC());
	EXPECT_EQ(0x0043, cpu.getPC());

	// Set to extremums
	cpu.setPC(0x0000);
	EXPECT_EQ(0x0000, cpu.getPC());

	cpu.setPC(0xFFFF);
	EXPECT_EQ(0xFFFF, cpu.getPC());

	// Pop wraparound
	EXPECT_EQ(0xFFFF, cpu.popPC());
	EXPECT_EQ(0x0000, cpu.getPC());
}

TEST_F(CPUTest, setAndGetA)
{
	// Set and get on random value
	cpu.setA(0x41);
	EXPECT_EQ(0x42, cpu.getA());

	// Set to extremums
	cpu.setA(0x00);
	EXPECT_EQ(0x00, cpu.getA());

	cpu.setA(0xFF);
	EXPECT_EQ(0xFF, cpu.getA());
}

TEST_F(CPUTest, setAndGetX)
{
	// Set and get on random value
	cpu.setX(0x42);
	EXPECT_EQ(0x42, cpu.getX());

	// Set to extremums
	cpu.setX(0x00);
	EXPECT_EQ(0x00, cpu.getX());

	cpu.setX(0xFF);
	EXPECT_EQ(0xFF, cpu.getX());
}

TEST_F(CPUTest, setAndGetY)
{
	// Set and get on random value
	cpu.setY(0x42);
	EXPECT_EQ(0x42, cpu.getY());

	// Set to extremums
	cpu.setY(0x00);
	EXPECT_EQ(0x00, cpu.getY());

	cpu.setY(0xFF);
	EXPECT_EQ(0xFF, cpu.getY());
}

TEST_F(CPUTest, adc)
{
	// Examples from "MCS6500 Microcomputer Family
	// Programming Manual, Revision A", published in
	// January 1976.

	// Example 2.1 with immediate addressing.
	cpu.setStatusFlag(CPU::FLAG_C, true);
	cpu.setStatusFlag(CPU::FLAG_V, false);
	cpu.setA(0x0D /* 13 */);

	memory.addMemoryBlock(0x8000, { 0x69, 0xD3 /* 211 */ });
	auto numCycles = cpu.executeCycles(1) + 1;

	EXPECT_EQ(2, numCycles);
	EXPECT_EQ(0xE1 /* 225 */, cpu.getA());
	EXPECT_FALSE(cpu.getStatusFlag(CPU::FLAG_Z));
	EXPECT_TRUE(cpu.getStatusFlag(CPU::FLAG_N));
	EXPECT_FALSE(cpu.getStatusFlag(CPU::FLAG_C));
	EXPECT_FALSE(cpu.getStatusFlag(CPU::FLAG_V));

	// Example 2.2 with zero page addressing.
	cpu.reset();
	memory.clear();
	cpu.setStatusFlag(CPU::FLAG_C, true);
	cpu.setStatusFlag(CPU::FLAG_V, false);
	cpu.setA(0xFE /* 254 */);

	memory.addMemoryBlock(0x8000, { 0x65, 0x00 });
	memory.addMemoryBlock(0x0000, { 0x06 });
	numCycles = cpu.executeCycles(1) + 1;

	EXPECT_EQ(3, numCycles);
	EXPECT_EQ(0x05, cpu.getA());
	EXPECT_FALSE(cpu.getStatusFlag(CPU::FLAG_Z));
	EXPECT_FALSE(cpu.getStatusFlag(CPU::FLAG_N));
	EXPECT_TRUE(cpu.getStatusFlag(CPU::FLAG_C));
	EXPECT_FALSE(cpu.getStatusFlag(CPU::FLAG_V));

	// Example 2.7 with zero page,x addressing
	cpu.reset();
	memory.clear();
	cpu.setStatusFlag(CPU::FLAG_C, false);
	cpu.setStatusFlag(CPU::FLAG_V, false);
	cpu.setA(0x7F /* 127 */);
	cpu.setX(1);

	memory.addMemoryBlock(0x8000, { 0x75, 0x00 });
	memory.addMemoryBlock(0x0001, { 2 });
	numCycles = cpu.executeCycles(1) + 1;

	EXPECT_EQ(4, numCycles);
	EXPECT_EQ(0x81, cpu.getA());
	EXPECT_FALSE(cpu.getStatusFlag(CPU::FLAG_Z));
	EXPECT_TRUE(cpu.getStatusFlag(CPU::FLAG_N));
	EXPECT_FALSE(cpu.getStatusFlag(CPU::FLAG_C));
	EXPECT_TRUE(cpu.getStatusFlag(CPU::FLAG_V));

	// Example 2.8 with absolute addressing
	cpu.reset();
	memory.clear();
	cpu.setStatusFlag(CPU::FLAG_C, false);
	cpu.setStatusFlag(CPU::FLAG_V, false);
	cpu.setA(0x05);

	memory.addMemoryBlock(0x8000, { 0x6D, 0x03, 0x80, 0xFD /*= -3*/ });
	numCycles = cpu.executeCycles(1) + 1;

	EXPECT_EQ(4, numCycles);
	EXPECT_EQ(0x02, cpu.getA());
	EXPECT_FALSE(cpu.getStatusFlag(CPU::FLAG_Z));
	EXPECT_FALSE(cpu.getStatusFlag(CPU::FLAG_N));
	EXPECT_TRUE(cpu.getStatusFlag(CPU::FLAG_C));
	EXPECT_FALSE(cpu.getStatusFlag(CPU::FLAG_V));

	// Example 2.9 with absolute,x addressing
	cpu.reset();
	memory.clear();
	cpu.setStatusFlag(CPU::FLAG_C, false);
	cpu.setStatusFlag(CPU::FLAG_V, false);
	cpu.setA(0x05);
	cpu.setX(0x01);

	memory.addMemoryBlock(0x8000, { 0x7D, 0x02, 0x80, 0xF9 /*= -7*/ });
	numCycles = cpu.executeCycles(1) + 1;

	EXPECT_EQ(4, numCycles);
	EXPECT_EQ(0xFE /* -2 */, cpu.getA());
	EXPECT_FALSE(cpu.getStatusFlag(CPU::FLAG_Z));
	EXPECT_TRUE(cpu.getStatusFlag(CPU::FLAG_N));
	EXPECT_FALSE(cpu.getStatusFlag(CPU::FLAG_C));
	EXPECT_FALSE(cpu.getStatusFlag(CPU::FLAG_V));
}

TEST_F(CPUTest, and)
{
	// Resetting a bit, immediate addressing mode.
	cpu.setA(0b11001111);

	memory.addMemoryBlock(0x8000, { 0x29, 0b11110111 });
	auto numCycles = cpu.executeCycles(1) + 1;

	EXPECT_EQ(2, numCycles);
	EXPECT_EQ(0b11000111, cpu.getA());
	EXPECT_FALSE(cpu.getStatusFlag(CPU::FLAG_Z));
	EXPECT_TRUE(cpu.getStatusFlag(CPU::FLAG_N));

	// Resetting all bits, zero page addressing mode.
	cpu.reset();
	memory.clear();

	cpu.setA(0b11001111);

	memory.addMemoryBlock(0x8000, { 0x25, 0x01 });
	memory.addMemoryBlock(0x0001, { 0b00000000 });
	numCycles = cpu.executeCycles(1) + 1;

	EXPECT_EQ(3, numCycles);
	EXPECT_EQ(0b00000000, cpu.getA());
	EXPECT_TRUE(cpu.getStatusFlag(CPU::FLAG_Z));
	EXPECT_FALSE(cpu.getStatusFlag(CPU::FLAG_N));
}

TEST_F(CPUTest, asl)
{
	// Accumulator addressing mode, no carry, negative
	cpu.setA(0b01110011);
	memory.addMemoryBlock(0x8000, { 0x0A });
	auto numCycles = cpu.executeCycles(1) + 1;

	EXPECT_EQ(2, numCycles);
	EXPECT_EQ(0b11100110, cpu.getA());
	EXPECT_FALSE(cpu.getStatusFlag(CPU::FLAG_C));
	EXPECT_FALSE(cpu.getStatusFlag(CPU::FLAG_Z));
	EXPECT_TRUE(cpu.getStatusFlag(CPU::FLAG_N));

	// Accumulator addressing mode, with carry, zero
	cpu.reset();
	memory.clear();

	cpu.setA(0b10000000);
	memory.addMemoryBlock(0x8000, { 0x0A });
	numCycles = cpu.executeCycles(1) + 1;

	EXPECT_EQ(2, numCycles);
	EXPECT_EQ(0b00000000, cpu.getA());
	EXPECT_TRUE(cpu.getStatusFlag(CPU::FLAG_C));
	EXPECT_TRUE(cpu.getStatusFlag(CPU::FLAG_Z));
	EXPECT_FALSE(cpu.getStatusFlag(CPU::FLAG_N));

	// Zero page addressing mode, no carry, zero.
	cpu.reset();
	memory.clear();

	memory.addMemoryBlock(0x8000, { 0x06 });
	memory.addMemoryBlock(0x0000, { 0b00000000 });
	numCycles = cpu.executeCycles(1) + 1;

	EXPECT_EQ(5, numCycles);
	EXPECT_EQ(0b00000000, memory.read(0x0000));
	EXPECT_FALSE(cpu.getStatusFlag(CPU::FLAG_C));
	EXPECT_TRUE(cpu.getStatusFlag(CPU::FLAG_Z));
	EXPECT_FALSE(cpu.getStatusFlag(CPU::FLAG_N));

	// Absolute addressing mode, with carry, negative.
	cpu.reset();
	memory.clear();

	memory.addMemoryBlock(0x8000, { 0x0E, 0x42, 0x00 });
	memory.addMemoryBlock(0x0042, { 0b11000000 });
	numCycles = cpu.executeCycles(1) + 1;

	EXPECT_EQ(6, numCycles);
	EXPECT_EQ(0b10000000, memory.read(0x0042));
	EXPECT_TRUE(cpu.getStatusFlag(CPU::FLAG_C));
	EXPECT_FALSE(cpu.getStatusFlag(CPU::FLAG_Z));
	EXPECT_TRUE(cpu.getStatusFlag(CPU::FLAG_N));
}

TEST_F(CPUTest, bcc)
{
	// Flag clear, positive offset, no page crossing
	cpu.setStatusFlag(CPU::FLAG_C, false);
	memory.addMemoryBlock(0x8000, { 0x90, 0x12 });
	auto numCycles = cpu.executeCycles(1) + 1;

	EXPECT_EQ(3, numCycles);
	EXPECT_EQ(0x8014, cpu.getPC());

	// Flag clear, negative offset, with page crossing
	cpu.reset();
	memory.clear();

	cpu.setStatusFlag(CPU::FLAG_C, false);
	memory.addMemoryBlock(0x8000, { 0x90, 0xF9 /*= -7*/ });
	numCycles = cpu.executeCycles(1) + 1;

	EXPECT_EQ(4, numCycles);
	EXPECT_EQ(0x7FFB, cpu.getPC());

	// Flag set
	cpu.reset();
	memory.clear();

	cpu.setStatusFlag(CPU::FLAG_C, true);
	memory.addMemoryBlock(0x8000, { 0x90, 0xF9 /*= -7*/ });
	numCycles = cpu.executeCycles(1) + 1;

	EXPECT_EQ(2, numCycles);
	EXPECT_EQ(0x8002, cpu.getPC());
}

TEST_F(CPUTest, bcs)
{
	// Flag set, positive offset, no page crossing
	cpu.setStatusFlag(CPU::FLAG_C, true);
	memory.addMemoryBlock(0x8000, { 0xB0, 0x12 });
	auto numCycles = cpu.executeCycles(1) + 1;

	EXPECT_EQ(3, numCycles);
	EXPECT_EQ(0x8014, cpu.getPC());

	// Flag set, negative offset, with page crossing
	cpu.reset();
	memory.clear();

	cpu.setStatusFlag(CPU::FLAG_C, true);
	memory.addMemoryBlock(0x8000, { 0xB0, 0xF9 /*= -7*/ });
	numCycles = cpu.executeCycles(1) + 1;

	EXPECT_EQ(4, numCycles);
	EXPECT_EQ(0x7FFB, cpu.getPC());

	// Flag clear
	cpu.reset();
	memory.clear();

	cpu.setStatusFlag(CPU::FLAG_C, false);
	memory.addMemoryBlock(0x8000, { 0xB0, 0xF9 /*= -7*/ });
	numCycles = cpu.executeCycles(1) + 1;

	EXPECT_EQ(2, numCycles);
	EXPECT_EQ(0x8002, cpu.getPC());
}

TEST_F(CPUTest, beq)
{
	// Flag set, positive offset, no page crossing
	cpu.setStatusFlag(CPU::FLAG_Z, true);
	memory.addMemoryBlock(0x8000, { 0xF0, 0x12 });
	auto numCycles = cpu.executeCycles(1) + 1;

	EXPECT_EQ(3, numCycles);
	EXPECT_EQ(0x8014, cpu.getPC());

	// Flag set, negative offset, with page crossing
	cpu.reset();
	memory.clear();

	cpu.setStatusFlag(CPU::FLAG_Z, true);
	memory.addMemoryBlock(0x8000, { 0xF0, 0xF9 /*= -7*/ });
	numCycles = cpu.executeCycles(1) + 1;

	EXPECT_EQ(4, numCycles);
	EXPECT_EQ(0x7FFB, cpu.getPC());

	// Flag clear
	cpu.reset();
	memory.clear();

	cpu.setStatusFlag(CPU::FLAG_Z, false);
	memory.addMemoryBlock(0x8000, { 0xF0, 0xF9 /*= -7*/ });
	numCycles = cpu.executeCycles(1) + 1;

	EXPECT_EQ(2, numCycles);
	EXPECT_EQ(0x8002, cpu.getPC());
}

TEST_F(CPUTest, bit)
{
	// Zero page, result is 0, bit 6 and 7 are set.
	cpu.setA(0b00111111);
	memory.addMemoryBlock(0x8000, { 0x24, 0x00 });
	memory.addMemoryBlock(0x0000, { 0b11000000 });
	auto numCycles = cpu.executeCycles(1) + 1;

	EXPECT_EQ(3, numCycles);
	EXPECT_TRUE(cpu.getStatusFlag(CPU::FLAG_Z));
	EXPECT_TRUE(cpu.getStatusFlag(CPU::FLAG_N));
	EXPECT_TRUE(cpu.getStatusFlag(CPU::FLAG_V));

	// Absolute, result is different from 0, bit 6 and 7 are not set.
	cpu.reset();
	memory.clear();

	cpu.setA(0b00001000);
	memory.addMemoryBlock(0x8000, { 0x2C, 0x00, 0x00 });
	memory.addMemoryBlock(0x0000, { 0b00001000 });
	numCycles = cpu.executeCycles(1) + 1;

	EXPECT_EQ(4, numCycles);
	EXPECT_FALSE(cpu.getStatusFlag(CPU::FLAG_Z));
	EXPECT_FALSE(cpu.getStatusFlag(CPU::FLAG_N));
	EXPECT_FALSE(cpu.getStatusFlag(CPU::FLAG_V));
}

TEST_F(CPUTest, bmi)
{
	// Flag set, positive offset, no page crossing
	cpu.setStatusFlag(CPU::FLAG_N, true);
	memory.addMemoryBlock(0x8000, { 0x30, 0x12 });
	auto numCycles = cpu.executeCycles(1) + 1;

	EXPECT_EQ(3, numCycles);
	EXPECT_EQ(0x8014, cpu.getPC());

	// Flag set, negative offset, with page crossing
	cpu.reset();
	memory.clear();

	cpu.setStatusFlag(CPU::FLAG_N, true);
	memory.addMemoryBlock(0x8000, { 0x30, 0xF9 /*= -7*/ });
	numCycles = cpu.executeCycles(1) + 1;

	EXPECT_EQ(4, numCycles);
	EXPECT_EQ(0x7FFB, cpu.getPC());

	// Flag clear
	cpu.reset();
	memory.clear();

	cpu.setStatusFlag(CPU::FLAG_N, false);
	memory.addMemoryBlock(0x8000, { 0x30, 0xF9 /*= -7*/ });
	numCycles = cpu.executeCycles(1) + 1;

	EXPECT_EQ(2, numCycles);
	EXPECT_EQ(0x8002, cpu.getPC());
}

TEST_F(CPUTest, bne)
{
	// Flag clear, positive offset, no page crossing
	cpu.setStatusFlag(CPU::FLAG_Z, false);
	memory.addMemoryBlock(0x8000, { 0xD0, 0x12 });
	auto numCycles = cpu.executeCycles(1) + 1;

	EXPECT_EQ(3, numCycles);
	EXPECT_EQ(0x8014, cpu.getPC());

	// Flag clear, negative offset, with page crossing
	cpu.reset();
	memory.clear();

	cpu.setStatusFlag(CPU::FLAG_Z, false);
	memory.addMemoryBlock(0x8000, { 0xD0, 0xF9 /*= -7*/ });
	numCycles = cpu.executeCycles(1) + 1;

	EXPECT_EQ(4, numCycles);
	EXPECT_EQ(0x7FFB, cpu.getPC());

	// Flag set
	cpu.reset();
	memory.clear();

	cpu.setStatusFlag(CPU::FLAG_Z, true);
	memory.addMemoryBlock(0x8000, { 0xD0, 0xF9 /*= -7*/ });
	numCycles = cpu.executeCycles(1) + 1;

	EXPECT_EQ(2, numCycles);
	EXPECT_EQ(0x8002, cpu.getPC());
}

TEST_F(CPUTest, bpl)
{
	// Flag clear, positive offset, no page crossing
	cpu.setStatusFlag(CPU::FLAG_N, false);
	memory.addMemoryBlock(0x8000, { 0x10, 0x12 });
	auto numCycles = cpu.executeCycles(1) + 1;

	EXPECT_EQ(3, numCycles);
	EXPECT_EQ(0x8014, cpu.getPC());

	// Flag clear, negative offset, with page crossing
	cpu.reset();
	memory.clear();

	cpu.setStatusFlag(CPU::FLAG_N, false);
	memory.addMemoryBlock(0x8000, { 0x10, 0xF9 /*= -7*/ });
	numCycles = cpu.executeCycles(1) + 1;

	EXPECT_EQ(4, numCycles);
	EXPECT_EQ(0x7FFB, cpu.getPC());

	// Flag set
	cpu.reset();
	memory.clear();

	cpu.setStatusFlag(CPU::FLAG_N, true);
	memory.addMemoryBlock(0x8000, { 0x10, 0xF9 /*= -7*/ });
	numCycles = cpu.executeCycles(1) + 1;

	EXPECT_EQ(2, numCycles);
	EXPECT_EQ(0x8002, cpu.getPC());
}

// TODO: BRK

TEST_F(CPUTest, bvc)
{
	// Flag clear, positive offset, no page crossing
	cpu.setStatusFlag(CPU::FLAG_V, false);
	memory.addMemoryBlock(0x8000, { 0x50, 0x12 });
	auto numCycles = cpu.executeCycles(1) + 1;

	EXPECT_EQ(3, numCycles);
	EXPECT_EQ(0x8014, cpu.getPC());

	// Flag clear, negative offset, with page crossing
	cpu.reset();
	memory.clear();

	cpu.setStatusFlag(CPU::FLAG_V, false);
	memory.addMemoryBlock(0x8000, { 0x50, 0xF9 /*= -7*/ });
	numCycles = cpu.executeCycles(1) + 1;

	EXPECT_EQ(4, numCycles);
	EXPECT_EQ(0x7FFB, cpu.getPC());

	// Flag set
	cpu.reset();
	memory.clear();

	cpu.setStatusFlag(CPU::FLAG_V, true);
	memory.addMemoryBlock(0x8000, { 0x50, 0xF9 /*= -7*/ });
	numCycles = cpu.executeCycles(1) + 1;

	EXPECT_EQ(2, numCycles);
	EXPECT_EQ(0x8002, cpu.getPC());
}

TEST_F(CPUTest, bvs)
{
	// Flag set, positive offset, no page crossing
	cpu.setStatusFlag(CPU::FLAG_V, true);
	memory.addMemoryBlock(0x8000, { 0x70, 0x12 });
	auto numCycles = cpu.executeCycles(1) + 1;

	EXPECT_EQ(3, numCycles);
	EXPECT_EQ(0x8014, cpu.getPC());

	// Flag set, negative offset, with page crossing
	cpu.reset();
	memory.clear();

	cpu.setStatusFlag(CPU::FLAG_V, true);
	memory.addMemoryBlock(0x8000, { 0x70, 0xF9 /*= -7*/ });
	numCycles = cpu.executeCycles(1) + 1;

	EXPECT_EQ(4, numCycles);
	EXPECT_EQ(0x7FFB, cpu.getPC());

	// Flag clear
	cpu.reset();
	memory.clear();

	cpu.setStatusFlag(CPU::FLAG_V, false);
	memory.addMemoryBlock(0x8000, { 0x70, 0xF9 /*= -7*/ });
	numCycles = cpu.executeCycles(1) + 1;

	EXPECT_EQ(2, numCycles);
	EXPECT_EQ(0x8002, cpu.getPC());
}

TEST_F(CPUTest, clc)
{
	// Flag should stay false.
	cpu.setStatusFlag(CPU::FLAG_C, false);

	memory.addMemoryBlock(0x8000, { 0x18 });
	auto numCycles = cpu.executeCycles(1) + 1;

	EXPECT_EQ(2, numCycles);
	EXPECT_FALSE(cpu.getStatusFlag(CPU::FLAG_C));

	// Flag should change to false.
	cpu.reset();
	cpu.setStatusFlag(CPU::FLAG_C, true);

	numCycles = cpu.executeCycles(1) + 1;

	EXPECT_EQ(2, numCycles);
	EXPECT_FALSE(cpu.getStatusFlag(CPU::FLAG_C));
}

TEST_F(CPUTest, cli)
{
	// Flag should stay false.
	cpu.setStatusFlag(CPU::FLAG_I, false);

	memory.addMemoryBlock(0x8000, { 0x58 });
	auto numCycles = cpu.executeCycles(1) + 1;

	EXPECT_EQ(2, numCycles);
	EXPECT_FALSE(cpu.getStatusFlag(CPU::FLAG_I));

	// Flag should change to false.
	cpu.reset();
	cpu.setStatusFlag(CPU::FLAG_I, true);

	numCycles = cpu.executeCycles(1) + 1;

	EXPECT_EQ(2, numCycles);
	EXPECT_FALSE(cpu.getStatusFlag(CPU::FLAG_I));
}

TEST_F(CPUTest, clv)
{
	// Flag should stay false.
	cpu.setStatusFlag(CPU::FLAG_V, false);

	memory.addMemoryBlock(0x8000, { 0xB8 });
	auto numCycles = cpu.executeCycles(1) + 1;

	EXPECT_EQ(2, numCycles);
	EXPECT_FALSE(cpu.getStatusFlag(CPU::FLAG_V));

	// Flag should change to false.
	cpu.reset();
	cpu.setStatusFlag(CPU::FLAG_V, true);

	numCycles = cpu.executeCycles(1) + 1;

	EXPECT_EQ(2, numCycles);
	EXPECT_FALSE(cpu.getStatusFlag(CPU::FLAG_V));
}

TEST_F(CPUTest, sec)
{
	// Flag should change to true.
	cpu.setStatusFlag(CPU::FLAG_C, false);

	memory.addMemoryBlock(0x8000, { 0x38 });
	auto numCycles = cpu.executeCycles(1) + 1;

	EXPECT_EQ(2, numCycles);
	EXPECT_TRUE(cpu.getStatusFlag(CPU::FLAG_C));

	// Flag should stay true.
	cpu.reset();
	cpu.setStatusFlag(CPU::FLAG_C, true);

	numCycles = cpu.executeCycles(1) + 1;

	EXPECT_EQ(2, numCycles);
	EXPECT_TRUE(cpu.getStatusFlag(CPU::FLAG_C));
}

TEST_F(CPUTest, sei)
{
	// Flag should change to true.
	cpu.setStatusFlag(CPU::FLAG_I, false);

	memory.addMemoryBlock(0x8000, { 0x78 });
	auto numCycles = cpu.executeCycles(1) + 1;

	EXPECT_EQ(2, numCycles);
	EXPECT_TRUE(cpu.getStatusFlag(CPU::FLAG_I));

	// Flag should stay true.
	cpu.reset();
	cpu.setStatusFlag(CPU::FLAG_I, true);

	numCycles = cpu.executeCycles(1) + 1;

	EXPECT_EQ(2, numCycles);
	EXPECT_TRUE(cpu.getStatusFlag(CPU::FLAG_I));
}
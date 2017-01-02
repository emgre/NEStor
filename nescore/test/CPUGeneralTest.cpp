#include "CPUTest.h"

using namespace nescore;

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
	cpu.setA(0x42);
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

TEST_F(CPUTest, setAndGetSP)
{
	// Set and get on random value
	cpu.setSP(0x42);
	EXPECT_EQ(0x42, cpu.getSP());

	// Set to extremums
	cpu.setSP(0x00);
	EXPECT_EQ(0x00, cpu.getSP());

	cpu.setSP(0xFF);
	EXPECT_EQ(0xFF, cpu.getSP());
}
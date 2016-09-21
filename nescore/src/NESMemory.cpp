#include "NESMemory.h"

namespace nescore
{
BYTE NESMemory::read(WORD address)
{
	BYTE result = 0x00;

	if (address < 0x2000)
	{
		result = m_ram[mirror(address, 0x0000, 0x2000, 4)];
	}

	else if (address < 0x4020)
	{
		// I/O Registers
	}

	else if (address < 0x6000)
	{
		// Expansion ROM
	}

	else if (address < 0x8000)
	{
		// SRAM
	}

	else
	{
		result = m_rom[address - 0x8000];
	}

	return result;
}

void NESMemory::write(WORD address, BYTE value)
{
	if (address < 0x2000)
	{
		m_ram[mirror(address, 0x0000, 0x2000, 4)] = value;
	}

	else if (address < 0x4020)
	{
		// I/O Registers
	}

	else if (address < 0x6000)
	{
		// Expansion ROM
	}

	else if (address < 0x8000)
	{
		// SRAM
	}

	else
	{
		m_rom[address - 0x8000] = value;
	}
}

WORD NESMemory::mirror(WORD address, WORD min, WORD max, unsigned int numMirrors)
{
	auto delta = max - min;
	auto blockSize = delta / numMirrors;
	auto blockId = (address - min) / blockSize;
	auto blockOffset = (address - min) % blockSize;
	return blockId * blockSize + blockOffset + min;
}
}
#include "NESMemory.h"
#include "ICartridge.h"

namespace nescore
{
NESMemory::NESMemory(ICartridge* cartridge)
:m_cartridge(cartridge)
{

}

BYTE NESMemory::read(WORD address)
{
	BYTE result = 0x00;

	if (address < 0x2000)
	{
		result = m_ram[address & 0x7FF];
	}

	else if (address < 0x4000)
	{
		// PPU Control Registers
	}

	else if (address < 0x4020)
	{
		// Other registers
	}

	else if (address < 0x6000)
	{
		// Expansion ROM
	}

	else if (address < 0x8000)
	{
		if(m_cartridge)
		{
			result = m_cartridge->sramRead(address & 0x5FFF);
		}
	}

	else
	{
		if(m_cartridge)
		{
			result = m_cartridge->prgRead(address & 0x7FFF);
		}
	}

	return result;
}

void NESMemory::write(WORD address, BYTE value)
{
	if (address < 0x2000)
	{
		m_ram[address & 0x7FF] = value;
	}

	else if (address < 0x4000)
	{
		// PPU Control Registers
	}

	else if (address < 0x4020)
	{
		// Other registers
	}

	else if (address < 0x6000)
	{
		// Expansion ROM
	}

	else if (address < 0x8000)
	{
		if(m_cartridge)
		{
			m_cartridge->sramWrite(address & 0x5FFF, value);
		}
	}

	else
	{
		if(m_cartridge)
		{
			m_cartridge->prgWrite(address & 0x7FFF, value);
		}
	}
}

void NESMemory::setCartridge(ICartridge* cartridge)
{
	m_cartridge = cartridge;
}
}
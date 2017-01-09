#ifndef NESMEMORY_H
#define NESMEMORY_H

#include "IMemory.h"
#include <array>

namespace nescore
{
class ICartridge;

class NESMemory : public IMemory
{
public:
	NESMemory(ICartridge* cartridge = nullptr);
	NESMemory(const NESMemory&) = delete;
	NESMemory& operator=(const NESMemory&) = delete;

	virtual BYTE read(WORD address);
	virtual void write(WORD address, BYTE value);

	void setCartridge(ICartridge* cartridge);

private:
	std::array<BYTE, 2048> m_ram;
	ICartridge* m_cartridge;
};
}

#endif // NESMEMORY_H
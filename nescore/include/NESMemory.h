#ifndef NESMEMORY_H
#define NESMEMORY_H

#include "IMemory.h"
#include <array>

namespace nescore
{
class NESMemory : public IMemory
{
public:
	NESMemory(const NESMemory&) = delete;
	NESMemory& operator=(const NESMemory&) = delete;

	virtual BYTE read(WORD address);
	virtual void write(WORD address, BYTE value);

private:
	WORD mirror(WORD address, WORD min, WORD max, unsigned int numMirrors);

	std::array<BYTE, 2048> m_ram;
	std::array<BYTE, 32768> m_rom;
};
}

#endif // NESMEMORY_H
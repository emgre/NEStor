#ifndef NESMEMORY_H
#define NESMEMORY_H

#include "IMemory.h"
#include <array>
#include <memory>

namespace nescore
{
class ICartridge;

class NESMemory : public IMemory
{
public:
	NESMemory(std::shared_ptr<ICartridge> cartridge = nullptr);

	virtual BYTE read(WORD address);
	virtual void write(WORD address, BYTE value);

	void setCartridge(std::shared_ptr<ICartridge> cartridge);

private:
	std::array<BYTE, 2048> m_ram;
	std::shared_ptr<ICartridge> m_cartridge;
};
}

#endif // NESMEMORY_H
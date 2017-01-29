#ifndef NROMCARTRIDGE_H
#define NROMCARTRIDGE_H

#include "ICartridge.h"
#include "ROMFile.h"
#include <memory>
#include <array>

namespace nescore
{
	class NROMCartridge : public ICartridge
	{
	public:
        NROMCartridge(const ROMFile& romFile);

		BYTE prgRead(WORD address) final;
		void prgWrite(WORD address, BYTE value) final;
        BYTE ppuRead(WORD address)  override final;
		void ppuWrite(WORD address, BYTE value) final;
        BYTE sramRead(WORD address) final;
		void sramWrite(WORD address, BYTE value) final;

    private:
        std::array<BYTE, 0x8000> m_rom;
		std::array<BYTE, 0x2000> m_vrom;
	};
}

#endif // NROMCARTRIDGE_H
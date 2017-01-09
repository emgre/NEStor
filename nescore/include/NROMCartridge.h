#ifndef NROMCARTRIDGE_H
#define NROMCARTRIDGE_H

#include "ICartridge.h"
#include <memory>

namespace nescore
{
    class ROMFile;

	class NROMCartridge : public ICartridge
	{
	public:
        NROMCartridge(std::unique_ptr<ROMFile> romFile);

		virtual BYTE prgRead(WORD address);
		virtual void prgWrite(WORD address, BYTE value);
        virtual BYTE ppuRead(WORD address);
		virtual void ppuWrite(WORD address, BYTE value);
        virtual BYTE sramRead(WORD address);
		virtual void sramWrite(WORD address, BYTE value);

    private:
        std::unique_ptr<ROMFile> m_romFile;
	};
}

#endif // NROMCARTRIDGE_H
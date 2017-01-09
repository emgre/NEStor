#ifndef ICARTRIDGE_H
#define ICARTRIDGE_H

#include "basic_types.h"

namespace nescore
{
	class ICartridge
	{
	public:
		virtual BYTE prgRead(WORD address) = 0;
		virtual void prgWrite(WORD address, BYTE value) = 0;
        virtual BYTE ppuRead(WORD address) = 0;
		virtual void ppuWrite(WORD address, BYTE value) = 0;
        virtual BYTE sramRead(WORD address) = 0;
		virtual void sramWrite(WORD address, BYTE value) = 0;
	};
}

#endif // ICARTRIDGE_H
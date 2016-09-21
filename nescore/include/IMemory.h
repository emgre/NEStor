#ifndef IMEMORY_H
#define IMEMORY_H

#include "basic_types.h"

namespace nescore
{
	class IMemory
	{
	public:
		virtual BYTE read(WORD address) = 0;
		virtual void write(WORD address, BYTE value) = 0;
	};
}

#endif // IMEMORY_H
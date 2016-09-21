#ifndef BASIC_TYPES_H
#define BASIC_TYPES_H

#include <cstdint>

namespace nescore
{
	typedef uint8_t BYTE;
	typedef int8_t SBYTE; // Signed byte
	typedef uint16_t WORD;

	constexpr BYTE FULLBYTE = 0xFF;
	constexpr WORD FULLWORD = 0xFFFF;
}

#endif // BASIC_TYPES_H
#include "NROMCartridge.h"
#include "NESCoreException.h"
#include "ROMFile.h"
#include <algorithm>

namespace nescore
{
NROMCartridge::NROMCartridge(const ROMFile& romFile)
{
    if(romFile.getMapperID() != 0x00)
    {
        throw InvalidROMFile("ROM file mapper ID does not fit with a NROM cartridge.");
    }

    if(!romFile.isNTSC())
    {
        throw InvalidROMFile("ROM file is not for an NTSC NES. This emulator only supports NTSC rom files.");
    }

    if(romFile.getNumROMBanks() > 2)
    {
        throw InvalidROMFile("NROM cartridge cannot contain more than 2 banks of 16K of ROM memory.");
    }

    if(romFile.getNumVROMBanks() > 1)
    {
        throw InvalidROMFile("NROM cartridge cannot contain more than 1 bank of 8K of VROM memory.");
    }

    std::copy(romFile.getROMBank(0).begin(), romFile.getROMBank(0).end(), m_rom.begin());
    std::copy(romFile.getROMBank(romFile.getNumROMBanks() - 1).begin(), romFile.getROMBank(romFile.getNumROMBanks() - 1).end(), m_rom.begin() + 0x4000);

    std::copy(romFile.getVROMBank(0).begin(), romFile.getVROMBank(0).end(), m_vrom.begin());
}

BYTE NROMCartridge::prgRead(WORD address)
{
    return m_rom[address];
}

void NROMCartridge::prgWrite(WORD address, BYTE value)
{
    // Writes are not supported on NROM
}

BYTE NROMCartridge::ppuRead(WORD address)
{
    return m_vrom[address];
}

void NROMCartridge::ppuWrite(WORD address, BYTE value)
{
    // Writes are not supported on NROM
}

BYTE NROMCartridge::sramRead(WORD address)
{
    // SRAM is currently not supported
    return 0x00;
}

void NROMCartridge::sramWrite(WORD address, BYTE value)
{
    // SRAM is currently not supported
}
}
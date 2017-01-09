#include "NROMCartridge.h"
#include "NESCoreException.h"
#include "ROMFile.h"

namespace nescore
{
NROMCartridge::NROMCartridge(std::unique_ptr<ROMFile> romFile)
:m_romFile(std::move(romFile))
{
    if(!m_romFile)
    {
        throw InvalidROMFile("No ROM file was associated with the cartridge.");
    }

    if(m_romFile->getMapperID() != 0x00)
    {
        throw InvalidROMFile("ROM file mapper ID does not fit with a NROM cartridge.");
    }

    if(!m_romFile->isNTSC())
    {
        throw InvalidROMFile("ROM file is not for an NTSC NES. This emulator only supports NTSC rom files.");
    }

    if(m_romFile->getNumROMBanks() > 2)
    {
        throw InvalidROMFile("NROM cartridge cannot contain more than 2 banks of 16K of ROM memory.");
    }

    if(m_romFile->getNumVROMBanks() > 1)
    {
        throw InvalidROMFile("NROM cartridge cannot contain more than 1 bank of 8K of VROM memory.");
    }
}

BYTE NROMCartridge::prgRead(WORD address)
{
    unsigned int bank = 0;
    if(m_romFile->getNumROMBanks() > 1 && address > 0x4000)
    {
        bank = 1;
    }

    return m_romFile->readROM(bank, address & 0x3FFF);
}

void NROMCartridge::prgWrite(WORD address, BYTE value)
{
    // Writes are not supported on NROM
}

BYTE NROMCartridge::ppuRead(WORD address)
{
    return m_romFile->readVROM(0, address);
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
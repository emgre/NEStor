#include "ROMFile.h"
#include "NESCoreException.h"

namespace nescore
{
void ROMFile::loadROM(ROMFile& romFile, std::istream &file)
{
    if (!file)
    {
        throw InvalidROMFile("File stream is invalid.");
    }

    std::streampos size = 0;
    size = file.tellg();
    file.seekg(0, std::ios::end);
    size = file.tellg() - size;
    file.seekg(0, std::ios::beg);

    if (size < 16)
    {
        throw InvalidROMFile("File is too small to contain the header.");
    }

    if (!(file.get() == 'N' && file.get() == 'E' && file.get() == 'S' && file.get() == 0x1A))
    {
        throw InvalidROMFile("File magic number is invalid.");
    }

    romFile.m_numROMBanks = file.get();
    romFile.m_numVROMBanks = file.get();

    if (size != std::streampos(16 + romFile.getNumROMBanks() * 0x4000 + romFile.getNumVROMBanks() * 0x2000))
    {
        throw InvalidROMFile("File size does not fit with the header specifications.");
    }

    unsigned int flag6 = file.get();
    romFile.m_mirroringType = (MirroringType)(flag6 & 0x01);
    romFile.m_hasSRAM = (flag6 & 0x02) != 0;
    romFile.m_hasTrainer = (flag6 & 0x04) != 0;
    romFile.m_isFourScreenLayout = (flag6 & 0x08) != 0;

    unsigned int flag7 = file.get();
    romFile.m_isVSSystem = flag7 & 0x01;

    romFile.m_mapperID = (flag6 >> 4) | (flag7 & 0xF0);

    romFile.m_numRAMBanks = file.get();
    if(romFile.m_numRAMBanks == 0)
    {
        romFile.m_numRAMBanks = 1;
    }

    unsigned int flag9 = file.get();
    romFile.m_isPAL = flag9 & 0x01;

    file.seekg(16);

    romFile.m_romBanks.resize(romFile.getNumROMBanks());
    for(unsigned int i = 0; i < romFile.getNumROMBanks(); ++i)
    {
        file.read((char*)romFile.m_romBanks[i].data(), 0x4000);
    }

    romFile.m_vromBanks.resize(romFile.getNumVROMBanks());
    for(unsigned int i = 0; i < romFile.getNumVROMBanks(); ++i)
    {
        file.read((char*)romFile.m_vromBanks[i].data(), 0x2000);
    }
}

unsigned int ROMFile::getNumROMBanks() const
{
    return m_numROMBanks;
}

BYTE ROMFile::readROM(unsigned int bankNumber, WORD address) const
{
    BYTE result = 0x00;

    if (bankNumber < getNumROMBanks())
    {
        result = m_romBanks[bankNumber][address];
    }

    return result;
}

unsigned int ROMFile::getNumVROMBanks() const
{
    return m_numVROMBanks;
}

BYTE ROMFile::readVROM(unsigned int bankNumber, WORD address) const
{
    BYTE result = 0x00;

    if (bankNumber < getNumVROMBanks())
    {
        result = m_vromBanks[bankNumber][address];
    }

    return result;
}

unsigned int ROMFile::getNumRAMBanks() const
{
    return m_numRAMBanks;
}

unsigned int ROMFile::getMapperID() const
{
    return m_mapperID;
}

ROMFile::MirroringType ROMFile::getMirroringType() const
{
    return m_mirroringType;
}

bool ROMFile::hasSRAM() const
{
    return m_hasSRAM;
}

bool ROMFile::hasTrainer() const
{
    return m_hasTrainer;
}

bool ROMFile::isFourSreenLayout() const
{
    return m_isFourScreenLayout;
}

bool ROMFile::isVSSystem() const
{
    return m_isVSSystem;
}

bool ROMFile::isNTSC() const
{
    return !m_isPAL;
}

bool ROMFile::isPAL() const
{
    return m_isPAL;
}
}
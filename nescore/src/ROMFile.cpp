#include "ROMFile.h"
#include "NESCoreException.h"

namespace nescore
{
void ROMFile::loadROM(std::istream &file)
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

    setNumROMBanks(file.get());
    setNumVROMBanks(file.get());

    // Decode flag 6
    unsigned int flag6 = file.get();
    if(flag6 & 0x01)
    {
        setMirroringVertical();
    }
    else
    {
        setMirroringHorizontal();
    }
    setHasSRAM((flag6 & 0x02) != 0);
    if(flag6 & 0x04)
    {
        m_trainer = std::unique_ptr<std::array<BYTE, TRAINER_SIZE>>();
    }
    else
    {
        removeTrainer();
    }
    if(flag6 & 0x08)
    {
        setFourScreenLayout();
    }

    // Decode flag 7
    unsigned int flag7 = file.get();
    setIsVSSystem(flag7 & 0x01);
    setMapperID((flag6 >> 4) | (flag7 & 0xF0));

    setNumRAMBanks(file.get());

    // Decode flag 9
    unsigned int flag9 = file.get();
    if(flag9 & 0x01)
    {
        setPAL();
    }
    else
    {
        setNTSC();
    }

    // Check file size
    std::size_t correctFileSize = 16 + getNumROMBanks() * ROM_SIZE + getNumVROMBanks() * VROM_SIZE;
    if(hasTrainer())
    {
        correctFileSize += TRAINER_SIZE;
    }

    if (size != (std::streampos)correctFileSize)
    {
        throw InvalidROMFile("File size does not fit with the header specifications.");
    }

    file.seekg(16);

    if(hasTrainer())
    {
        file.read((char*)getTrainer().data(), TRAINER_SIZE);
    }

    for(unsigned int i = 0; i < getNumROMBanks(); ++i)
    {
        file.read((char*)getROMBank(i).data(), ROM_SIZE);
    }

    for(unsigned int i = 0; i < getNumVROMBanks(); ++i)
    {
        file.read((char*)getVROMBank(i).data(), VROM_SIZE);
    }
}

unsigned int ROMFile::getNumROMBanks() const
{
    return m_romBanks.size();
}

void ROMFile::setNumROMBanks(unsigned int numROMBanks)
{
    if(numROMBanks > 0xFF)
    {
        throw std::length_error("Number of ROM banks must fit in one byte");
    }

    m_romBanks.resize(numROMBanks);
}

std::array<BYTE, ROMFile::ROM_SIZE>& ROMFile::getROMBank(unsigned int bankNumber)
{
    if(bankNumber >= getNumROMBanks())
    {
        throw std::out_of_range("ROM bank out of range");
    }

    return m_romBanks[bankNumber];
}

const std::array<BYTE, ROMFile::ROM_SIZE>& ROMFile::getROMBank(unsigned int bankNumber) const
{
    if(bankNumber >= getNumROMBanks())
    {
        throw std::out_of_range("ROM bank out of range");
    }

    return m_romBanks[bankNumber];
}

unsigned int ROMFile::getNumVROMBanks() const
{
    return m_vromBanks.size();
}

void ROMFile::setNumVROMBanks(unsigned int numVROMBanks)
{
    if(numVROMBanks > 0xFF)
    {
        throw std::length_error("Number of ROM banks must fit in one byte");
    }

    m_vromBanks.resize(numVROMBanks);
}

std::array<BYTE, ROMFile::VROM_SIZE>& ROMFile::getVROMBank(unsigned int bankNumber)
{
    if(bankNumber >= getNumVROMBanks())
    {
        throw std::out_of_range("ROM bank out of range");
    }

    return m_vromBanks[bankNumber];
}

const std::array<BYTE, ROMFile::VROM_SIZE>& ROMFile::getVROMBank(unsigned int bankNumber) const
{
    if(bankNumber >= getNumVROMBanks())
    {
        throw std::out_of_range("ROM bank out of range");
    }

    return m_vromBanks[bankNumber];
}


unsigned int ROMFile::getNumRAMBanks() const
{
    return m_numRAMBanks;
}

void ROMFile::setNumRAMBanks(unsigned int numRAMBanks)
{
    if(numRAMBanks > 0xFF)
    {
        throw std::length_error("Number of RAM banks must fit in one byte");
    }

    m_numRAMBanks = numRAMBanks;
    if(m_numRAMBanks == 0)
    {
        m_numRAMBanks = 1;
    }
}

unsigned int ROMFile::getMapperID() const
{
    return m_mapperID;
}

void ROMFile::setMapperID(unsigned int mapperID)
{
    if(mapperID > 0xFF)
    {
        throw std::length_error("Mapper ID must fit in one byte");
    }

    m_mapperID = mapperID;
}

bool ROMFile::isMirroringHorizontal() const
{
    return !m_isMirroringVertical && !m_isFourScreenLayout;
}

bool ROMFile::isMirroringVertical() const
{
    return m_isMirroringVertical && !m_isFourScreenLayout;
}

bool ROMFile::isFourSreenLayout() const
{
    return m_isFourScreenLayout;
}

void ROMFile::setMirroringHorizontal()
{
    m_isMirroringVertical = false;
    m_isFourScreenLayout = false;
}

void ROMFile::setMirroringVertical()
{
    m_isMirroringVertical = true;
    m_isFourScreenLayout = false;
}

void ROMFile::setFourScreenLayout()
{
    m_isFourScreenLayout = true;
}

bool ROMFile::hasSRAM() const
{
    return m_hasSRAM;
}

void ROMFile::setHasSRAM(bool hasSRAM)
{
    m_hasSRAM = hasSRAM;
}

bool ROMFile::hasTrainer() const
{
    return (bool)m_trainer;
}

std::array<BYTE, ROMFile::TRAINER_SIZE>& ROMFile::getTrainer()
{
    if(!m_trainer)
    {
        throw std::domain_error("No trainer on this ROM file.");
    }
    return *m_trainer;
}

void ROMFile::removeTrainer()
{
    m_trainer.reset();
}

bool ROMFile::isVSSystem() const
{
    return m_isVSSystem;
}

void ROMFile::setIsVSSystem(bool isVSSystem)
{
    m_isVSSystem = isVSSystem;
}

bool ROMFile::isNTSC() const
{
    return !m_isPAL;
}

bool ROMFile::isPAL() const
{
    return m_isPAL;
}

void ROMFile::setNTSC()
{
    m_isPAL = false;
}

void ROMFile::setPAL()
{
    m_isPAL = true;
}
}
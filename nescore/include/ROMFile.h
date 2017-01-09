#ifndef ROMFILE_H
#define ROMFILE_H

#include "basic_types.h"
#include <istream>
#include <vector>
#include <array>

namespace nescore
{
class ROMFile
{
public:
    enum class MirroringType
    {
        HORIZONTAL,
        VERTICAL
    };

    ROMFile() = default;
	ROMFile(const ROMFile&) = delete;
    ROMFile(ROMFile&&) = default;
	ROMFile& operator=(const ROMFile&) = delete;

    unsigned int getNumROMBanks() const;
    BYTE readROM(unsigned int bankNumber, WORD address) const;

    unsigned int getNumVROMBanks() const;
    BYTE readVROM(unsigned int bankNumber, WORD address) const;

    unsigned int getNumRAMBanks() const;
    unsigned int getMapperID() const;
    MirroringType getMirroringType() const;
    bool hasSRAM() const;
    bool hasTrainer() const;
    bool isFourSreenLayout() const;
    bool isVSSystem() const;
    bool isNTSC() const;
    bool isPAL() const;

    static void loadROM(ROMFile& romFile, std::istream& file);

private:
    unsigned int m_numROMBanks;
    unsigned int m_numVROMBanks;
    unsigned int m_numRAMBanks;
    unsigned int m_mapperID;
    MirroringType m_mirroringType;
    bool m_hasSRAM;
    bool m_hasTrainer;
    bool m_isFourScreenLayout;
    bool m_isVSSystem;
    bool m_isPAL;

	std::vector<std::array<BYTE, 0x4000>> m_romBanks;
	std::vector<std::array<BYTE, 0x2000>> m_vromBanks;
};
}

#endif // ROMFILE_H
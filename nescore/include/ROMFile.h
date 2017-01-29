#ifndef ROMFILE_H
#define ROMFILE_H

#include "basic_types.h"
#include <istream>
#include <ostream>
#include <memory>
#include <vector>
#include <array>

namespace nescore
{
class ROMFile
{
public:
    static constexpr unsigned int ROM_SIZE = 0x4000;
    static constexpr unsigned int VROM_SIZE = 0x2000;
    static constexpr unsigned int TRAINER_SIZE = 0x200;

    void loadROM(std::istream& file);
    //void saveROM(std::ostream& file);

    unsigned int getNumROMBanks() const;
    void setNumROMBanks(unsigned int numROMBanks);
    std::array<BYTE, ROM_SIZE>& getROMBank(unsigned int bankNumber);
    const std::array<BYTE, ROM_SIZE>& getROMBank(unsigned int bankNumber) const;

    unsigned int getNumVROMBanks() const;
    void setNumVROMBanks(unsigned int numVROMBanks);
    std::array<BYTE, VROM_SIZE>& getVROMBank(unsigned int bankNumber);
    const std::array<BYTE, VROM_SIZE>& getVROMBank(unsigned int bankNumber) const;

    unsigned int getNumRAMBanks() const;
    void setNumRAMBanks(unsigned int numRAMBanks);

    unsigned int getMapperID() const;
    void setMapperID(unsigned int mapperID);

    bool isMirroringHorizontal() const;
    bool isMirroringVertical() const;
    bool isFourSreenLayout() const;
    void setMirroringHorizontal();
    void setMirroringVertical();
    void setFourScreenLayout();

    bool hasSRAM() const;
    void setHasSRAM(bool hasSRAM);

    bool hasTrainer() const;
    std::array<BYTE, TRAINER_SIZE>& getTrainer();
    void removeTrainer();

    bool isVSSystem() const;
    void setIsVSSystem(bool isVSSystem);

    bool isNTSC() const;
    bool isPAL() const;
    void setNTSC();
    void setPAL();

private:
    unsigned int m_numRAMBanks;
    unsigned int m_mapperID;

    bool m_isMirroringVertical;
    bool m_hasSRAM;
    bool m_isFourScreenLayout;
    bool m_isVSSystem;
    bool m_isPAL;

	std::vector<std::array<BYTE, ROM_SIZE>> m_romBanks;
	std::vector<std::array<BYTE, VROM_SIZE>> m_vromBanks;
    std::unique_ptr<std::array<BYTE, TRAINER_SIZE>> m_trainer;
};
}

#endif // ROMFILE_H
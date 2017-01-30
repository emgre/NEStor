#include "gtest/gtest.h"
#include "basic_types.h"
#include "ROMFile.h"

using namespace nescore;

class ROMFileTest: public ::testing::Test
{
public:
	ROMFile rom;
};

TEST_F(ROMFileTest, ROMBanks)
{
    ASSERT_EQ(0, rom.getNumROMBanks());

    // Check access to wrong bank number
    ASSERT_THROW(rom.getROMBank(0), std::out_of_range);
    const ROMFile& constRom = static_cast<const ROMFile&>(rom);
    ASSERT_THROW(constRom.getROMBank(0), std::out_of_range);

    // Change number of banks
    rom.setNumROMBanks(2);
    ASSERT_EQ(2, rom.getNumROMBanks());
    ASSERT_NE(&rom.getROMBank(0), &rom.getROMBank(1)); // Check that arrays are different
    ASSERT_EQ(0x4000, rom.getROMBank(0).size());

    // Check exception throw
    ASSERT_NO_THROW(rom.setNumROMBanks(255));
    ASSERT_THROW(rom.setNumROMBanks(256), std::length_error);

    // Check resizing
    rom.getROMBank(0)[0] = 0x42;
    rom.getROMBank(1)[0] = 0x76;
    rom.setNumROMBanks(2);
    ASSERT_NO_THROW(rom.getROMBank(1));
    ASSERT_NO_THROW(constRom.getROMBank(1));
    ASSERT_THROW(rom.getROMBank(2), std::out_of_range);
    ASSERT_THROW(constRom.getROMBank(2), std::out_of_range);
    ASSERT_EQ(0x42, rom.getROMBank(0)[0]);
    ASSERT_EQ(0x76, rom.getROMBank(1)[0]);
}

TEST_F(ROMFileTest, VROMBanks)
{
    ASSERT_EQ(0, rom.getNumVROMBanks());

    // Check access to wrong bank number
    ASSERT_THROW(rom.getVROMBank(0), std::out_of_range);
    const ROMFile& constRom = static_cast<const ROMFile&>(rom);
    ASSERT_THROW(constRom.getVROMBank(0), std::out_of_range);

    // Change number of banks
    rom.setNumVROMBanks(2);
    ASSERT_EQ(2, rom.getNumVROMBanks());
    ASSERT_NE(&rom.getVROMBank(0), &rom.getVROMBank(1)); // Check that arrays are different
    ASSERT_EQ(0x2000, rom.getVROMBank(0).size());

    // Check exception throw
    ASSERT_NO_THROW(rom.setNumVROMBanks(255));
    ASSERT_THROW(rom.setNumVROMBanks(256), std::length_error);

    // Check resizing
    rom.getVROMBank(0)[0] = 0x42;
    rom.getVROMBank(1)[0] = 0x76;
    rom.setNumVROMBanks(2);
    ASSERT_NO_THROW(rom.getVROMBank(1));
    ASSERT_NO_THROW(constRom.getVROMBank(1));
    ASSERT_THROW(rom.getVROMBank(2), std::out_of_range);
    ASSERT_THROW(constRom.getVROMBank(2), std::out_of_range);
    ASSERT_EQ(0x42, rom.getVROMBank(0)[0]);
    ASSERT_EQ(0x76, rom.getVROMBank(1)[0]);
}

TEST_F(ROMFileTest, RAMBanks)
{
    ASSERT_EQ(0, rom.getNumRAMBanks());

    rom.setNumRAMBanks(2);
    ASSERT_EQ(2, rom.getNumRAMBanks());

    ASSERT_NO_THROW(rom.setNumRAMBanks(255));
    ASSERT_THROW(rom.setNumRAMBanks(256), std::length_error);
}

TEST_F(ROMFileTest, mapperID)
{
    ASSERT_EQ(0, rom.getMapperID());

    // Change number of banks
    rom.setMapperID(2);
    ASSERT_EQ(2, rom.getMapperID());

    // Check exception throw
    ASSERT_NO_THROW(rom.setMapperID(255));
    ASSERT_THROW(rom.setMapperID(256), std::length_error);
}

TEST_F(ROMFileTest, mirroring)
{
    ASSERT_TRUE(rom.isMirroringHorizontal());
    ASSERT_FALSE(rom.isMirroringVertical());
    ASSERT_FALSE(rom.isFourScreenLayout());

    rom.setMirroringVertical();
    ASSERT_FALSE(rom.isMirroringHorizontal());
    ASSERT_TRUE(rom.isMirroringVertical());
    ASSERT_FALSE(rom.isFourScreenLayout());

    rom.setFourScreenLayout();
    ASSERT_FALSE(rom.isMirroringHorizontal());
    ASSERT_FALSE(rom.isMirroringVertical());
    ASSERT_TRUE(rom.isFourScreenLayout());

    rom.setMirroringHorizontal();
    ASSERT_TRUE(rom.isMirroringHorizontal());
    ASSERT_FALSE(rom.isMirroringVertical());
    ASSERT_FALSE(rom.isFourScreenLayout());
}

TEST_F(ROMFileTest, sram)
{
    ASSERT_FALSE(rom.hasSRAM());

    rom.setHasSRAM(true);
    ASSERT_TRUE(rom.hasSRAM());

    rom.setHasSRAM(false);
    ASSERT_FALSE(rom.hasSRAM());
}

TEST_F(ROMFileTest, trainer)
{
    ASSERT_FALSE(rom.hasTrainer());
    ASSERT_THROW(rom.getTrainer(), std::domain_error);

    rom.addTrainer();
    ASSERT_TRUE(rom.hasTrainer());
    ASSERT_NO_THROW(rom.getTrainer());

    // Check that ROMFile::addTrainer() is not destructive
    rom.getTrainer()[0] = 0x42;
    rom.addTrainer();
    ASSERT_EQ(0x42, rom.getTrainer()[0]);

    rom.removeTrainer();
    ASSERT_FALSE(rom.hasTrainer());
    ASSERT_THROW(rom.getTrainer(), std::domain_error);
}

TEST_F(ROMFileTest, VSSystem)
{
    ASSERT_FALSE(rom.isVSSystem());

    rom.setIsVSSystem(true);
    ASSERT_TRUE(rom.isVSSystem());

    rom.setIsVSSystem(false);
    ASSERT_FALSE(rom.isVSSystem());
}

TEST_F(ROMFileTest, tvFormat)
{
    ASSERT_TRUE(rom.isNTSC());
    ASSERT_FALSE(rom.isPAL());

    rom.setPAL();
    ASSERT_FALSE(rom.isNTSC());
    ASSERT_TRUE(rom.isPAL());

    rom.setNTSC();
    ASSERT_TRUE(rom.isNTSC());
    ASSERT_FALSE(rom.isPAL());
}
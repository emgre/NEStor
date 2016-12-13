#include "TestMemory.h"

using namespace nescore;

// Remove all blocks
void TestMemory::clear()
{
    m_blocks.clear();
}

// Add a memory block starting at the specified address.
// Note that if two blocks overlap, the latest one is used.
void TestMemory::addMemoryBlock(WORD address, const std::vector<BYTE>& data)
{
    m_blocks.push_back(SMemoryBlock({
        address,
        data
    }));
}

BYTE TestMemory::read(WORD address)
{
    auto pMemoryBlock = getMemoryBlock(address);
    if (pMemoryBlock)
    {
        return pMemoryBlock->data[address - pMemoryBlock->address];
    }

    return 0x00;
}

void TestMemory::write(WORD address, BYTE value)
{
    auto pMemoryBlock = getMemoryBlock(address);
    if (pMemoryBlock)
    {
        pMemoryBlock->data[address - pMemoryBlock->address] = value;
    }
    else
    {
        addMemoryBlock(address, { value });
    }
}

// Returns the memory block for the address, or nullptr if no memory block exists.
TestMemory::SMemoryBlock* TestMemory::getMemoryBlock(WORD address)
{
    // We use a reverse iterator in order to get the latest block.
    for (auto it = m_blocks.rbegin(); it != m_blocks.rend(); it++)
    {
        if ((address >= (*it).address) && (address < (*it).address + (*it).getSize()))
        {
            return &(*it);
        }
    }

    return nullptr;
}
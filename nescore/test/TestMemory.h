#include "IMemory.h"
#include "basic_types.h"
#include <vector>

// Memory test is a simple IMemory implementation where
// you can write whatever you want in it, without using
// kilobytes of RAM.
class TestMemory : public nescore::IMemory
{
public:
	void clear();

	void addMemoryBlock(nescore::WORD address, const std::vector<nescore::BYTE>& data);

	virtual nescore::BYTE read(nescore::WORD address);
	virtual void write(nescore::WORD address, nescore::BYTE value);

private:
	struct SMemoryBlock
	{
		nescore::WORD address;
		std::vector<nescore::BYTE> data;

		nescore::WORD getSize() const
		{
			return (nescore::WORD)data.size();
		}
	};

	SMemoryBlock* getMemoryBlock(nescore::WORD address);

	std::vector<SMemoryBlock> m_blocks;
};
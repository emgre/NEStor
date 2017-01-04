#include "CPU.h"
#include "IMemory.h"
#include "NESCoreException.h"
#include <sstream>
#include <iomanip>

namespace nescore
{
	const std::array<CPU::Opcode, 256> CPU::s_opcodes =
	{{
		{ &CPU::BRK, nullptr, 7, false },
		{ &CPU::ORA, &CPU::indirectX, 6, false },
		{ nullptr, nullptr, 0, false },
		{ nullptr, nullptr, 0, false },
		{ nullptr, nullptr, 0, false },
		{ &CPU::ORA, &CPU::zeroPage, 3, false },
		{ &CPU::ASL, &CPU::zeroPage, 5, false },
		{ nullptr, nullptr, 0, false },
		{ &CPU::PHP, nullptr, 3, false },
		{ &CPU::ORA, &CPU::immediate, 2, false },
		{ &CPU::ASLAcc, nullptr, 2, false },
		{ nullptr, nullptr, 0, false },
		{ nullptr, nullptr, 0, false },
		{ &CPU::ORA, &CPU::absolute, 4, false },
		{ &CPU::ASL, &CPU::absolute, 6, false },
		{ nullptr, nullptr, 0, false },
		{ &CPU::BPL, &CPU::relative, 2, false },
		{ &CPU::ORA, &CPU::indirectY, 5, false },
		{ nullptr, nullptr, 0, false },
		{ nullptr, nullptr, 0, false },
		{ nullptr, nullptr, 0, false },
		{ &CPU::ORA, &CPU::zeroPageX, 4, false },
		{ &CPU::ASL, &CPU::zeroPageX, 6, false },
		{ nullptr, nullptr, 0, false },
		{ &CPU::CLC, nullptr, 2, false },
		{ &CPU::ORA, &CPU::absoluteY, 4, true },
		{ nullptr, nullptr, 0, false },
		{ nullptr, nullptr, 0, false },
		{ nullptr, nullptr, 0, false },
		{ &CPU::ORA, &CPU::absoluteX, 4, true },
		{ &CPU::ASL, &CPU::absoluteX, 7, false },
		{ nullptr, nullptr, 0, false },
		{ &CPU::JSR, &CPU::absolute, 6, false },
		{ &CPU::AND, &CPU::indirectX, 6, false },
		{ nullptr, nullptr, 0, false },
		{ nullptr, nullptr, 0, false },
		{ &CPU::BIT, &CPU::zeroPage, 3, false },
		{ &CPU::AND, &CPU::zeroPage, 3, false },
		{ &CPU::ROL, &CPU::zeroPage, 5, false },
		{ nullptr, nullptr, 0, false },
		{ &CPU::PLP, nullptr, 4, false },
		{ &CPU::AND, &CPU::immediate, 2, false },
		{ &CPU::ROLAcc, nullptr, 2, false },
		{ nullptr, nullptr, 0, false },
		{ &CPU::BIT, &CPU::absolute, 4, false },
		{ &CPU::AND, &CPU::absolute, 4, false },
		{ &CPU::ROL, &CPU::absolute, 6, false },
		{ nullptr, nullptr, 0, false },
		{ &CPU::BMI, &CPU::relative, 2, false },
		{ &CPU::AND, &CPU::indirectY, 5, false },
		{ nullptr, nullptr, 0, false },
		{ nullptr, nullptr, 0, false },
		{ nullptr, nullptr, 0, false },
		{ &CPU::AND, &CPU::zeroPageX, 4, false },
		{ &CPU::ROL, &CPU::zeroPageX, 6, false },
		{ nullptr, nullptr, 0, false },
		{ &CPU::SEC, nullptr, 2, false },
		{ &CPU::AND, &CPU::absoluteY, 4, true },
		{ nullptr, nullptr, 0, false },
		{ nullptr, nullptr, 0, false },
		{ nullptr, nullptr, 0, false },
		{ &CPU::AND, &CPU::absoluteX, 4, true },
		{ &CPU::ROL, &CPU::absoluteX, 7, false },
		{ nullptr, nullptr, 0, false },
		{ &CPU::RTI, nullptr, 6, false },
		{ &CPU::EOR, &CPU::indirectX, 6, false },
		{ nullptr, nullptr, 0, false },
		{ nullptr, nullptr, 0, false },
		{ nullptr, nullptr, 0, false },
		{ &CPU::EOR, &CPU::zeroPage, 3, false },
		{ &CPU::LSR, &CPU::zeroPage, 5, false },
		{ nullptr, nullptr, 0, false },
		{ &CPU::PHA, nullptr, 3, false },
		{ &CPU::EOR, &CPU::immediate, 2, false },
		{ &CPU::LSRAcc, nullptr, 2, false },
		{ nullptr, nullptr, 0, false },
		{ &CPU::JMP, &CPU::absolute, 3, false },
		{ &CPU::EOR, &CPU::absolute, 4, false },
		{ &CPU::LSR, &CPU::absolute, 6, false },
		{ nullptr, nullptr, 0, false },
		{ &CPU::BVC, &CPU::relative, 2, false },
		{ &CPU::EOR, &CPU::indirectY, 5, true },
		{ nullptr, nullptr, 0, false },
		{ nullptr, nullptr, 0, false },
		{ nullptr, nullptr, 0, false },
		{ &CPU::EOR, &CPU::zeroPageX, 4, false },
		{ &CPU::LSR, &CPU::zeroPageX, 6, false },
		{ nullptr, nullptr, 0, false },
		{ &CPU::CLI, nullptr, 2, false },
		{ &CPU::EOR, &CPU::absoluteY, 4, true },
		{ nullptr, nullptr, 0, false },
		{ nullptr, nullptr, 0, false },
		{ nullptr, nullptr, 0, false },
		{ &CPU::EOR, &CPU::absoluteX, 4, true },
		{ &CPU::LSR, &CPU::absoluteX, 7, false },
		{ nullptr, nullptr, 0, false },
		{ &CPU::RTS, nullptr, 6, false },
		{ &CPU::ADC, &CPU::indirectX, 6, false },
		{ nullptr, nullptr, 0, false },
		{ nullptr, nullptr, 0, false },
		{ nullptr, nullptr, 0, false },
		{ &CPU::ADC, &CPU::zeroPage, 3, false },
		{ &CPU::ROR, &CPU::zeroPage, 5, false },
		{ nullptr, nullptr, 0, false },
		{ &CPU::PLA, nullptr, 4, false },
		{ &CPU::ADC, &CPU::immediate, 2, false },
		{ &CPU::RORAcc, nullptr, 2, false },
		{ nullptr, nullptr, 0, false },
		{ &CPU::JMP, &CPU::indirect, 5, false },
		{ &CPU::ADC, &CPU::absolute, 4, false },
		{ &CPU::ROR, &CPU::absolute, 6, false },
		{ nullptr, nullptr, 0, false },
		{ &CPU::BVS, &CPU::relative, 2, false },
		{ &CPU::ADC, &CPU::indirectY, 5, true },
		{ nullptr, nullptr, 0, false },
		{ nullptr, nullptr, 0, false },
		{ nullptr, nullptr, 0, false },
		{ &CPU::ADC, &CPU::zeroPageX, 4, false },
		{ &CPU::ROR, &CPU::zeroPageX, 6, false },
		{ nullptr, nullptr, 0, false },
		{ &CPU::SEI, nullptr, 2, false },
		{ &CPU::ADC, &CPU::absoluteY, 4, true },
		{ nullptr, nullptr, 0, false },
		{ nullptr, nullptr, 0, false },
		{ nullptr, nullptr, 0, false },
		{ &CPU::ADC, &CPU::absoluteX, 4, true },
		{ &CPU::ROR, &CPU::absoluteX, 7, false },
		{ nullptr, nullptr, 0, false },
		{ nullptr, nullptr, 0, false },
		{ &CPU::STA, &CPU::indirectX, 6, false },
		{ nullptr, nullptr, 0, false },
		{ nullptr, nullptr, 0, false },
		{ &CPU::STY, &CPU::zeroPage, 3, false },
		{ &CPU::STA, &CPU::zeroPage, 3, false },
		{ &CPU::STX, &CPU::zeroPage, 3, false },
		{ nullptr, nullptr, 0, false },
		{ &CPU::DEY, nullptr, 2, false },
		{ nullptr, nullptr, 0, false },
		{ &CPU::TXA, nullptr, 2, false },
		{ nullptr, nullptr, 0, false },
		{ &CPU::STY, &CPU::absolute, 4, false },
		{ &CPU::STA, &CPU::absolute, 4, false },
		{ &CPU::STX, &CPU::absolute, 4, false },
		{ nullptr, nullptr, 0, false },
		{ &CPU::BCC, &CPU::relative, 2, false },
		{ &CPU::STA, &CPU::indirectY, 6, false },
		{ nullptr, nullptr, 0, false },
		{ nullptr, nullptr, 0, false },
		{ &CPU::STY, &CPU::zeroPageX, 4, false },
		{ &CPU::STA, &CPU::zeroPageX, 4, false },
		{ &CPU::STX, &CPU::zeroPageY, 4, false },
		{ nullptr, nullptr, 0, false },
		{ &CPU::TYA, nullptr, 2, false },
		{ &CPU::STA, &CPU::absoluteY, 5, false },
		{ &CPU::TXS, nullptr, 2, false },
		{ nullptr, nullptr, 0, false },
		{ nullptr, nullptr, 0, false },
		{ &CPU::STA, &CPU::absoluteX, 5, false },
		{ nullptr, nullptr, 0, false },
		{ nullptr, nullptr, 0, false },
		{ &CPU::LDY, &CPU::immediate, 2, false },
		{ &CPU::LDA, &CPU::indirectX, 6, false },
		{ &CPU::LDX, &CPU::immediate, 2, false },
		{ nullptr, nullptr, 0, false },
		{ &CPU::LDY, &CPU::zeroPage, 3, false },
		{ &CPU::LDA, &CPU::zeroPage, 3, false },
		{ &CPU::LDX, &CPU::zeroPage, 3, false },
		{ nullptr, nullptr, 0, false },
		{ &CPU::TAY, nullptr, 2, false },
		{ &CPU::LDA, &CPU::immediate, 2, false },
		{ &CPU::TAX, nullptr, 2, false },
		{ nullptr, nullptr, 0, false },
		{ &CPU::LDY, &CPU::absolute, 4, false },
		{ &CPU::LDA, &CPU::absolute, 4, false },
		{ &CPU::LDX, &CPU::absolute, 4, false },
		{ nullptr, nullptr, 0, false },
		{ &CPU::BCS, &CPU::relative, 2, false },
		{ &CPU::LDA, &CPU::indirectY, 5, true },
		{ nullptr, nullptr, 0, false },
		{ nullptr, nullptr, 0, false },
		{ &CPU::LDY, &CPU::zeroPageX, 4, false },
		{ &CPU::LDA, &CPU::zeroPageX, 4, false },
		{ &CPU::LDX, &CPU::zeroPageY, 4, false },
		{ nullptr, nullptr, 0, false },
		{ &CPU::CLV, nullptr, 2, false },
		{ &CPU::LDA, &CPU::absoluteY, 4, true },
		{ &CPU::TSX, nullptr, 2, false },
		{ nullptr, nullptr, 0, false },
		{ &CPU::LDY, &CPU::absoluteX, 4, true },
		{ &CPU::LDA, &CPU::absoluteX, 4, true },
		{ &CPU::LDX, &CPU::absoluteY, 4, true },
		{ nullptr, nullptr, 0, false },
		{ &CPU::CPY, &CPU::immediate, 2, false },
		{ &CPU::CMP, &CPU::indirectX, 6, false },
		{ nullptr, nullptr, 0, false },
		{ nullptr, nullptr, 0, false },
		{ &CPU::CPY, &CPU::zeroPage, 3, false },
		{ &CPU::CMP, &CPU::zeroPage, 3, false },
		{ &CPU::DEC, &CPU::zeroPage, 5, false },
		{ nullptr, nullptr, 0, false },
		{ &CPU::INY, nullptr, 2, false },
		{ &CPU::CMP, &CPU::immediate, 2, false },
		{ &CPU::DEX, nullptr, 2, false },
		{ nullptr, nullptr, 0, false },
		{ &CPU::CPY, &CPU::absolute, 4, false },
		{ &CPU::CMP, &CPU::absolute, 4, false },
		{ &CPU::DEC, &CPU::absolute, 6, false },
		{ nullptr, nullptr, 0, false },
		{ &CPU::BNE, &CPU::relative, 2, false },
		{ &CPU::CMP, &CPU::indirectY, 6, true },
		{ nullptr, nullptr, 0, false },
		{ nullptr, nullptr, 0, false },
		{ nullptr, nullptr, 0, false },
		{ &CPU::CMP, &CPU::zeroPageX, 4, false },
		{ &CPU::DEC, &CPU::zeroPageX, 6, false },
		{ nullptr, nullptr, 0, false },
		{ nullptr, nullptr, 0, false }, // CLD not implemented
		{ &CPU::CMP, &CPU::absoluteY, 4, true },
		{ nullptr, nullptr, 0, false },
		{ nullptr, nullptr, 0, false },
		{ nullptr, nullptr, 0, false },
		{ &CPU::CMP, &CPU::absoluteX, 4, true },
		{ &CPU::DEC, &CPU::absoluteX, 7, false },
		{ nullptr, nullptr, 0, false },
		{ &CPU::CPX, &CPU::immediate, 2, false },
		{ &CPU::SBC, &CPU::indirectX, 6, false },
		{ nullptr, nullptr, 0, false },
		{ nullptr, nullptr, 0, false },
		{ &CPU::CPX, &CPU::zeroPage, 3, false },
		{ &CPU::SBC, &CPU::zeroPage, 3, false },
		{ &CPU::INC, &CPU::zeroPage, 5, false },
		{ nullptr, nullptr, 0, false },
		{ &CPU::INX, nullptr, 2, false },
		{ &CPU::SBC, &CPU::immediate, 2, false },
		{ &CPU::NOP, nullptr, 2, false },
		{ nullptr, nullptr, 0, false },
		{ &CPU::CPX, &CPU::absolute, 4, false },
		{ &CPU::SBC, &CPU::absolute, 4, false },
		{ &CPU::INC, &CPU::absolute, 6, false },
		{ nullptr, nullptr, 0, false },
		{ &CPU::BEQ, &CPU::relative, 2, false },
		{ &CPU::SBC, &CPU::indirectY, 5, true },
		{ nullptr, nullptr, 0, false },
		{ nullptr, nullptr, 0, false },
		{ nullptr, nullptr, 0, false },
		{ &CPU::SBC, &CPU::zeroPageX, 4, false },
		{ &CPU::INC, &CPU::zeroPageX, 6, false },
		{ nullptr, nullptr, 0, false },
		{ nullptr, nullptr, 0, false }, // SED not implemented
		{ &CPU::SBC, &CPU::absoluteY, 4, true },
		{ nullptr, nullptr, 0, false },
		{ nullptr, nullptr, 0, false },
		{ nullptr, nullptr, 0, false },
		{ &CPU::SBC, &CPU::absoluteX, 4, true },
		{ &CPU::INC, &CPU::absoluteX, 7, false },
		{ nullptr, nullptr, 0, false }
	}};

	CPU::CPU(IMemory& memory)
	:m_memory(memory)
	{
		reset();
	}

	void CPU::reset()
	{
		m_a = 0x00;
		m_x = 0x00;
		m_y = 0x00;
		m_sp = 0xFF;
		m_pc = 0x8000;
		m_p.reset();
	}

	unsigned int CPU::executeCycles(unsigned int numCycles)
	{
		unsigned int cycleCount = 0;

		while (cycleCount < numCycles)
		{
			cycleCount += executeSingleInstruction();
		}

		return cycleCount - numCycles;
	}

	unsigned int CPU::executeSingleInstruction()
	{
		unsigned int cycleCount = 0;
		auto value = m_memory.read(popPC());
		auto opcode = s_opcodes[value];

		WORD address = 0x0000;

		if (opcode.addressingFunction)
		{
			bool pageCrossed = opcode.addressingFunction(*this, address);
			if (pageCrossed && opcode.pageCrossingExtraCycle)
			{
				++cycleCount;
			}
		}

		if (!opcode.instruction)
		{
			std::stringstream ss;
			ss << "Opcode ";
			ss << "0x" << std::uppercase << std::setfill('0') << std::setw(2) << std::hex << (unsigned int)value;
			ss << " is undefined.";
			throw UndefinedOpcode(ss.str());
		}

		cycleCount += opcode.numCycles;
		cycleCount += opcode.instruction(*this, address);

		return cycleCount;
	}

	IMemory& CPU::getMemory() const
	{
		return m_memory;
	}

	WORD CPU::popPC()
	{
		return m_pc++ & FULLWORD;
	}

	void CPU::setPC(WORD pc)
	{
		m_pc = pc;
	}

	WORD CPU::getPC() const
	{
		return m_pc;
	}

	void CPU::setA(BYTE a)
	{
		m_a = a;
	}

	BYTE CPU::getA() const
	{
		return m_a;
	}

	void CPU::setX(BYTE x)
	{
		m_x = x;
	}

	BYTE CPU::getX() const
	{
		return m_x;
	}

	void CPU::setY(BYTE y)
	{
		m_y = y;
	}

	BYTE CPU::getY() const
	{
		return m_y;
	}

	void CPU::setSP(BYTE sp)
	{
		m_sp = sp;
	}

	BYTE CPU::getSP() const
	{
		return m_sp;
	}

	BYTE CPU::getP() const
	{
		return (BYTE)(m_p.to_ulong());
	}

	void CPU::setStatusFlag(StatusFlag flag, bool value)
	{
		m_p.set((size_t)flag, value);
	}

	bool CPU::getStatusFlag(StatusFlag flag) const
	{
		return m_p[(size_t)flag];
	}

	void CPU::updateCommonFlags(BYTE value)
	{
		setStatusFlag(StatusFlag::Z, (value == 0));
		setStatusFlag(StatusFlag::N, (value >= 0x80));
	}

	void CPU::pushStack(BYTE value)
	{
		getMemory().write(0x0100 + getSP(), value);
		setSP((getSP() - 1) & FULLBYTE);
	}

	BYTE CPU::pullStack()
	{
		setSP((getSP() + 1) & FULLBYTE);
		return getMemory().read(0x0100 + getSP());
	}

	// ===================
	// Adressing functions
	// ===================

	bool CPU::immediate(WORD& address)
	{
		address = popPC();
		return false;
	}

	bool CPU::absolute(WORD& address)
	{
		address = getMemory().read(popPC());
		address |= getMemory().read(popPC()) << 8;
		return false;
	}

	bool CPU::absoluteX(WORD& address)
	{
		address = getMemory().read(popPC());
		address |= getMemory().read(popPC()) << 8;
		auto newAddress = address + getX();
		bool pageCrossed = ((newAddress & 0xFF00) != (address & 0xFF00));
		address = newAddress;
		return pageCrossed;
	}

	bool CPU::absoluteY(WORD& address)
	{
		address = getMemory().read(popPC());
		address |= getMemory().read(popPC()) << 8;
		auto newAddress = address + getY();
		bool pageCrossed = ((newAddress & 0xFF00) != (address & 0xFF00));
		address = newAddress;
		return pageCrossed;
	}

	bool CPU::zeroPage(WORD& address)
	{
		address = getMemory().read(popPC());
		return false;
	}

	bool CPU::zeroPageX(WORD& address)
	{
		address = (getMemory().read(popPC()) + getX()) & FULLBYTE;
		return false;
	}

	bool CPU::zeroPageY(WORD& address)
	{
		address = (getMemory().read(popPC()) + getY()) & FULLBYTE;
		return false;
	}

	bool CPU::indirect(WORD& address)
	{
		WORD indirectAddress = getMemory().read(popPC());
		indirectAddress |= getMemory().read(popPC()) << 8;

		address = getMemory().read(indirectAddress);
		address |= getMemory().read((indirectAddress & 0xFF00) | ((indirectAddress + 1) & 0x00FF)) << 8;
		// The weird memory address decoding for the high byte is used to recreate the indirect JMP bug.
		// For example, doing a JMP ($30FF) will jump to the address with the low byte $30FF and the
		// the high byte at $3000.

		return false;
	}

	bool CPU::indirectX(WORD& address)
	{
		BYTE indirectAddress = getMemory().read(popPC()) + getX() & FULLBYTE;
		address = getMemory().read(indirectAddress);
		address |= getMemory().read((indirectAddress + 1) & FULLBYTE) << 8;
		
		return false;
	}

	bool CPU::indirectY(WORD& address)
	{
		BYTE indirectAddress = getMemory().read(popPC());
		address = getMemory().read(indirectAddress);
		address |= getMemory().read((indirectAddress + 1) & FULLBYTE) << 8;
		auto newAddress = (address + getY()) & FULLWORD;
		bool pageCrossed = ((newAddress & 0xFF00) != (address & 0xFF00));
		address = newAddress;
		return pageCrossed;
	}

	bool CPU::relative(WORD& address)
	{
		SBYTE offset = getMemory().read(popPC());
		address = (getPC() + offset);

		return ((address & 0xFF00) != (getPC() & 0xFF00));
	}

	// =======
	// Opcodes
	// =======

	unsigned int CPU::ADC(WORD address)
	{
		auto value = m_memory.read(address);
		int result = (int)getA() + (int)value;
		if (getStatusFlag(StatusFlag::C))
		{
			result++;
		}

		updateCommonFlags(result);
		setStatusFlag(StatusFlag::C, result >= FULLBYTE);
		setStatusFlag(StatusFlag::V, ((~(value ^ getA()) & (value ^ result)) & 0x80) > 0);
		// To set the overflow flag, we do this:
		// 1. The first nxor determines if the 8th bits of the initial values are the same (a mask is applied later)
		// 2. The second xor checks if the result's 8th bit is different from the initial value's 8th bit
		//    (I used the value, but I could use the accumulator, since they should have the same 8th bit)
		// 3. Apply a mask to only check the 8th bit
		// 4. The > 0 converts to a boolean value

		setA(result & FULLBYTE);

		return 0;
	}

	unsigned int CPU::AND(WORD address)
	{
		auto value = m_memory.read(address);
		auto result = value & getA();

		updateCommonFlags(result);
		setA(result);
		
		return 0;
	}

	unsigned int CPU::ASL(WORD address)
	{
		auto value = m_memory.read(address);
		BYTE result = value << 1;

		setStatusFlag(StatusFlag::C, (value & 0x80) != 0);
		updateCommonFlags(result);

		m_memory.write(address, result);

		return 0;
	}

	unsigned int CPU::ASLAcc(WORD address)
	{
		auto value = getA();
		BYTE result = value << 1;

		setStatusFlag(StatusFlag::C, (value & 0x80) != 0);
		updateCommonFlags(result);

		setA(result);

		return 0;
	}

	unsigned int CPU::BCC(WORD address)
	{
		unsigned int cycleCount = 0;

		if (!getStatusFlag(StatusFlag::C))
		{
			++cycleCount;
			if ((getPC() & 0xFF00) != (address & 0xFF00))
			{
				++cycleCount;
			}
			setPC(address);
		}

		return cycleCount;
	}

	unsigned int CPU::BCS(WORD address)
	{
		unsigned int cycleCount = 0;

		if (getStatusFlag(StatusFlag::C))
		{
			++cycleCount;
			if ((getPC() & 0xFF00) != (address & 0xFF00))
			{
				++cycleCount;
			}
			setPC(address);
		}

		return cycleCount;
	}

	unsigned int CPU::BEQ(WORD address)
	{
		unsigned int cycleCount = 0;

		if (getStatusFlag(StatusFlag::Z))
		{
			++cycleCount;
			if ((getPC() & 0xFF00) != (address & 0xFF00))
			{
				++cycleCount;
			}
			setPC(address);
		}

		return cycleCount;
	}

	unsigned int CPU::BIT(WORD address)
	{
		auto value = m_memory.read(address);
		setStatusFlag(StatusFlag::Z, (value & getA()) == 0);
		setStatusFlag(StatusFlag::N, (value & 0x80) != 0);
		setStatusFlag(StatusFlag::V, (value & 0x40) != 0);

		return 0;
	}

	unsigned int CPU::BMI(WORD address)
	{
		unsigned int cycleCount = 0;

		if (getStatusFlag(StatusFlag::N))
		{
			++cycleCount;
			if ((getPC() & 0xFF00) != (address & 0xFF00))
			{
				++cycleCount;
			}
			setPC(address);
		}

		return cycleCount;
	}

	unsigned int CPU::BNE(WORD address)
	{
		unsigned int cycleCount = 0;

		if (!getStatusFlag(StatusFlag::Z))
		{
			++cycleCount;
			if ((getPC() & 0xFF00) != (address & 0xFF00))
			{
				++cycleCount;
			}
			setPC(address);
		}

		return cycleCount;
	}

	unsigned int CPU::BPL(WORD address)
	{
		unsigned int cycleCount = 0;

		if (!getStatusFlag(StatusFlag::N))
		{
			++cycleCount;
			if ((getPC() & 0xFF00) != (address & 0xFF00))
			{
				++cycleCount;
			}
			setPC(address);
		}

		return cycleCount;
	}

	unsigned int CPU::BRK(WORD address)
	{
		throw NotImplementedException("BRK opcode not implemented yet.");
	}

	unsigned int CPU::BVC(WORD address)
	{
		unsigned int cycleCount = 0;

		if (!getStatusFlag(StatusFlag::V))
		{
			++cycleCount;
			if ((getPC() & 0xFF00) != (address & 0xFF00))
			{
				++cycleCount;
			}
			setPC(address);
		}

		return cycleCount;
	}

	unsigned int CPU::BVS(WORD address)
	{
		unsigned int cycleCount = 0;

		if (getStatusFlag(StatusFlag::V))
		{
			++cycleCount;
			if ((getPC() & 0xFF00) != (address & 0xFF00))
			{
				++cycleCount;
			}
			setPC(address);
		}

		return cycleCount;
	}
	
	unsigned int CPU::CLC(WORD address)
	{
		setStatusFlag(StatusFlag::C, false);
		return 0;
	}
	
	unsigned int CPU::CLI(WORD address)
	{
		setStatusFlag(StatusFlag::I, false);
		return 0;
	}
	
	unsigned int CPU::CLV(WORD address)
	{
		setStatusFlag(StatusFlag::V, false);
		return 0;
	}
	
	unsigned int CPU::CMP(WORD address)
	{
		auto value = m_memory.read(address);
		auto result = getA() - value;

		setStatusFlag(StatusFlag::C, value >= getA());
		setStatusFlag(StatusFlag::Z, value == getA());
		setStatusFlag(StatusFlag::N, (result & 0x80) != 0);

		return 0;
	}
	
	unsigned int CPU::CPX(WORD address)
	{
		auto value = m_memory.read(address);
		auto result = getX() - value;

		setStatusFlag(StatusFlag::C, value >= getX());
		setStatusFlag(StatusFlag::Z, value == getX());
		setStatusFlag(StatusFlag::N, (result & 0x80) != 0);

		return 0;
	}
	
	unsigned int CPU::CPY(WORD address)
	{
		auto value = m_memory.read(address);
		auto result = getY() - value;

		setStatusFlag(StatusFlag::C, value >= getY());
		setStatusFlag(StatusFlag::Z, value == getY());
		setStatusFlag(StatusFlag::N, (result & 0x80) != 0);

		return 0;
	}
	
	unsigned int CPU::DEC(WORD address)
	{
		auto value = m_memory.read(address);
		value = (value - 1) & 0xFF;
		updateCommonFlags(value);
		m_memory.write(address, value);

		return 0;
	}
	
	unsigned int CPU::DEX(WORD address)
	{
		setX((getX() - 1) & 0xFF);
		updateCommonFlags(getX());
		return 0;
	}
	
	unsigned int CPU::DEY(WORD address)
	{
		setY((getY() - 1) & 0xFF);
		updateCommonFlags(getY());
		return 0;
	}
	
	unsigned int CPU::EOR(WORD address)
	{
		auto value = m_memory.read(address);
		auto result = value ^ getA();

		updateCommonFlags(result);
		setA(result);
		
		return 0;
	}
	
	unsigned int CPU::INC(WORD address)
	{
		auto value = m_memory.read(address);
		value = (value + 1) & 0xFF;
		updateCommonFlags(value);
		m_memory.write(address, value);

		return 0;
	}
	
	unsigned int CPU::INX(WORD address)
	{
		setX((getX() + 1) & 0xFF);
		updateCommonFlags(getX());
		return 0;
	}
	
	unsigned int CPU::INY(WORD address)
	{
		setY((getY() + 1) & 0xFF);
		updateCommonFlags(getY());
		return 0;
	}
	
	unsigned int CPU::JMP(WORD address)
	{
		setPC(address);
		return 0;
	}
	
	unsigned int CPU::JSR(WORD address)
	{
		WORD stackValue = (getPC() - 1) & FULLWORD;
		pushStack(stackValue >> 8);
		pushStack(stackValue & FULLBYTE);

		setPC(address);
		return 0;
	}
	
	unsigned int CPU::LDA(WORD address)
	{
		auto value = m_memory.read(address);
		setA(value);
		updateCommonFlags(value);
		
		return 0;
	}
	
	unsigned int CPU::LDX(WORD address)
	{
		auto value = m_memory.read(address);
		setX(value);
		updateCommonFlags(value);
		
		return 0;
	}
	
	unsigned int CPU::LDY(WORD address)
	{
		auto value = m_memory.read(address);
		setY(value);
		updateCommonFlags(value);
		
		return 0;
	}
	
	unsigned int CPU::LSR(WORD address)
	{
		auto value = m_memory.read(address);
		setStatusFlag(StatusFlag::C, (value & 0x01) != 0);
		BYTE result = value >> 1;

		updateCommonFlags(result);

		m_memory.write(address, result);

		return 0;
	}

	unsigned int CPU::LSRAcc(WORD address)
	{
		auto value = getA();
		setStatusFlag(StatusFlag::C, (value & 0x01) != 0);
		BYTE result = value >> 1;

		updateCommonFlags(result);

		setA(result);

		return 0;
	}
	
	unsigned int CPU::NOP(WORD address)
	{
		return 0;
	}
	
	unsigned int CPU::ORA(WORD address)
	{
		auto value = m_memory.read(address);
		auto result = value | getA();

		updateCommonFlags(result);
		setA(result);
		
		return 0;
	}
	
	unsigned int CPU::PHA(WORD address)
	{
		pushStack(getA());
		return 0;
	}
	
	unsigned int CPU::PHP(WORD address)
	{
		pushStack(getP());
		return 0;
	}
	
	unsigned int CPU::PLA(WORD address)
	{
		setA(pullStack());
		updateCommonFlags(getA());
		return 0;
	}
	
	unsigned int CPU::PLP(WORD address)
	{
		std::bitset<8> newP(pullStack());
		m_p = newP;
		return 0;
	}
	
	unsigned int CPU::ROL(WORD address)
	{
		auto value = m_memory.read(address);
		BYTE result = value << 1;
		if(getStatusFlag(StatusFlag::C))
		{
			result |= 0x01;
		}

		setStatusFlag(StatusFlag::C, (value & 0x80) != 0);
		updateCommonFlags(result);

		m_memory.write(address, result);

		return 0;
	}

	unsigned int CPU::ROLAcc(WORD address)
	{
		auto value = getA();
		BYTE result = value << 1;
		if(getStatusFlag(StatusFlag::C))
		{
			result |= 0x01;
		}

		setStatusFlag(StatusFlag::C, (value & 0x80) != 0);
		updateCommonFlags(result);

		setA(result);

		return 0;
	}
	
	unsigned int CPU::ROR(WORD address)
	{
		auto value = m_memory.read(address);
		BYTE result = value >> 1;
		if(getStatusFlag(StatusFlag::C))
		{
			result |= 0x80;
		}

		setStatusFlag(StatusFlag::C, (value & 0x01) != 0);
		updateCommonFlags(result);

		m_memory.write(address, result);

		return 0;
	}

	unsigned int CPU::RORAcc(WORD address)
	{
		auto value = getA();
		BYTE result = value >> 1;
		if(getStatusFlag(StatusFlag::C))
		{
			result |= 0x80;
		}

		setStatusFlag(StatusFlag::C, (value & 0x01) != 0);
		updateCommonFlags(result);

		setA(result);

		return 0;
	}
	
	unsigned int CPU::RTI(WORD address)
	{
		throw NotImplementedException("RTI opcode not implemented yet.");
	}
	
	unsigned int CPU::RTS(WORD address)
	{
		WORD newAddress = pullStack();
		newAddress |= pullStack() << 8;
		setPC((newAddress + 1) & FULLWORD);
		return 0;
	}
	
	unsigned int CPU::SBC(WORD address)
	{
		auto value = m_memory.read(address);
		int result = (int)getA() - (int)value;
		if (!getStatusFlag(StatusFlag::C))
		{
			result++;
		}

		updateCommonFlags(result);
		setStatusFlag(StatusFlag::C, result >= 0);
		setStatusFlag(StatusFlag::V, (((value ^ getA()) & (value ^ result)) & 0x80) > 0);
		// To set the overflow flag, we do this:
		// 1. The first xor determines if the 8th bits of the initial values are different (a mask is applied later)
		//    Note: In ADC, we use a nxor, but here the sign of "value" must be reversed (because we're dealing with a subtraction)
		// 2. The second xor checks if the result's 8th bit is different from the initial value's 8th bit
		//    (I used the value, but I could use the accumulator, since they should have the same 8th bit)
		// 3. Apply a mask to only check the 8th bit
		// 4. The > 0 converts to a boolean value

		setA(result & FULLBYTE);

		return 0;
	}
	
	unsigned int CPU::SEC(WORD address)
	{
		setStatusFlag(StatusFlag::C, true);
		return 0;
	}
	
	unsigned int CPU::SEI(WORD address)
	{
		setStatusFlag(StatusFlag::I, true);
		return 0;
	}
	
	unsigned int CPU::STA(WORD address)
	{
		m_memory.write(address, getA());
		return 0;
	}
	
	unsigned int CPU::STX(WORD address)
	{
		m_memory.write(address, getX());
		return 0;
	}
	
	unsigned int CPU::STY(WORD address)
	{
		m_memory.write(address, getY());
		return 0;
	}
	
	unsigned int CPU::TAX(WORD address)
	{
		setX(getA());
		updateCommonFlags(getX());
		return 0;
	}
	
	unsigned int CPU::TAY(WORD address)
	{
		setY(getA());
		updateCommonFlags(getY());
		return 0;
	}
	
	unsigned int CPU::TSX(WORD address)
	{
		setX(getSP());
		updateCommonFlags(getX());
		return 0;
	}
	
	unsigned int CPU::TXA(WORD address)
	{
		setA(getX());
		updateCommonFlags(getA());
		return 0;
	}
	
	unsigned int CPU::TXS(WORD address)
	{
		setSP(getX());
		return 0;
	}
	
	unsigned int CPU::TYA(WORD address)
	{
		setA(getY());
		updateCommonFlags(getA());
		return 0;
	}
}
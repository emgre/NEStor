#include "CPU.h"
#include "IMemory.h"
#include "NESCoreException.h"
#include <sstream>

namespace nescore
{
	const std::array<CPU::Opcode, 256> CPU::s_opcodes =
	{{
		{ &CPU::BRK, nullptr, 7, false },
		{ &CPU::ORA, &CPU::indirectX, 6, false },
		{ &CPU::NOT, nullptr, 0, false },
		{ &CPU::NOT, nullptr, 0, false },
		{ &CPU::NOT, nullptr, 0, false },
		{ &CPU::ORA, &CPU::zeroPage, 3, false },
		{ &CPU::ASL, &CPU::zeroPage, 5, false },
		{ &CPU::NOT, nullptr, 0, false },
		{ &CPU::PHP, nullptr, 3, false },
		{ &CPU::ORA, &CPU::immediate, 2, false },
		{ &CPU::ASLAcc, nullptr, 2, false },
		{ &CPU::NOT, nullptr, 0, false },
		{ &CPU::NOT, nullptr, 0, false },
		{ &CPU::ORA, &CPU::absolute, 4, false },
		{ &CPU::ASL, &CPU::absolute, 6, false },
		{ &CPU::NOT, nullptr, 0, false },
		{ &CPU::BPL, &CPU::relative, 2, false },
		{ &CPU::ORA, &CPU::indirectY, 5, false },
		{ &CPU::NOT, nullptr, 0, false },
		{ &CPU::NOT, nullptr, 0, false },
		{ &CPU::NOT, nullptr, 0, false },
		{ &CPU::ORA, &CPU::zeroPageX, 4, false },
		{ &CPU::ASL, &CPU::zeroPageX, 6, false },
		{ &CPU::NOT, nullptr, 0, false },
		{ &CPU::CLC, nullptr, 2, false },
		{ &CPU::ORA, &CPU::absoluteY, 4, true },
		{ &CPU::NOT, nullptr, 0, false },
		{ &CPU::NOT, nullptr, 0, false },
		{ &CPU::NOT, nullptr, 0, false },
		{ &CPU::ORA, &CPU::absoluteX, 4, true },
		{ &CPU::ASL, &CPU::absoluteX, 7, false },
		{ &CPU::NOT, nullptr, 0, false },
		{ &CPU::JSR, &CPU::absolute, 6, false },
		{ &CPU::AND, &CPU::indirectX, 6, false },
		{ &CPU::NOT, nullptr, 0, false },
		{ &CPU::NOT, nullptr, 0, false },
		{ &CPU::BIT, &CPU::zeroPage, 3, false },
		{ &CPU::AND, &CPU::zeroPage, 3, false },
		{ &CPU::ROL, &CPU::zeroPage, 5, false },
		{ &CPU::NOT, nullptr, 0, false },
		{ &CPU::PLP, nullptr, 4, false },
		{ &CPU::AND, &CPU::immediate, 2, false },
		{ &CPU::ROLAcc, nullptr, 2, false },
		{ &CPU::NOT, nullptr, 0, false },
		{ &CPU::BIT, &CPU::absolute, 4, false },
		{ &CPU::AND, &CPU::absolute, 4, false },
		{ &CPU::ROL, &CPU::absolute, 6, false },
		{ &CPU::NOT, nullptr, 0, false },
		{ &CPU::BMI, &CPU::relative, 2, false },
		{ &CPU::AND, &CPU::indirectY, 5, false },
		{ &CPU::NOT, nullptr, 0, false },
		{ &CPU::NOT, nullptr, 0, false },
		{ &CPU::NOT, nullptr, 0, false },
		{ &CPU::AND, &CPU::zeroPageX, 4, false },
		{ &CPU::ROL, &CPU::zeroPageX, 6, false },
		{ &CPU::NOT, nullptr, 0, false },
		{ &CPU::SEC, nullptr, 2, false },
		{ &CPU::AND, &CPU::absoluteY, 4, true },
		{ &CPU::NOT, nullptr, 0, false },
		{ &CPU::NOT, nullptr, 0, false },
		{ &CPU::NOT, nullptr, 0, false },
		{ &CPU::AND, &CPU::absoluteX, 4, true },
		{ &CPU::ROL, &CPU::absoluteX, 7, false },
		{ &CPU::NOT, nullptr, 0, false },
		{ &CPU::RTI, nullptr, 6, false },
		{ &CPU::EOR, &CPU::indirectX, 6, false },
		{ &CPU::NOT, nullptr, 0, false },
		{ &CPU::NOT, nullptr, 0, false },
		{ &CPU::NOT, nullptr, 0, false },
		{ &CPU::EOR, &CPU::zeroPage, 3, false },
		{ &CPU::LSR, &CPU::zeroPage, 5, false },
		{ &CPU::NOT, nullptr, 0, false },
		{ &CPU::PHA, nullptr, 3, false },
		{ &CPU::EOR, &CPU::immediate, 2, false },
		{ &CPU::LSRAcc, nullptr, 2, false },
		{ &CPU::NOT, nullptr, 0, false },
		{ &CPU::JMP, &CPU::absolute, 3, false },
		{ &CPU::EOR, &CPU::absolute, 4, false },
		{ &CPU::LSR, &CPU::absolute, 6, false },
		{ &CPU::NOT, nullptr, 0, false },
		{ &CPU::BVC, &CPU::relative, 2, false },
		{ &CPU::EOR, &CPU::indirectY, 5, true },
		{ &CPU::NOT, nullptr, 0, false },
		{ &CPU::NOT, nullptr, 0, false },
		{ &CPU::NOT, nullptr, 0, false },
		{ &CPU::EOR, &CPU::zeroPageX, 4, false },
		{ &CPU::LSR, &CPU::zeroPageX, 6, false },
		{ &CPU::NOT, nullptr, 0, false },
		{ &CPU::CLI, nullptr, 2, false },
		{ &CPU::EOR, &CPU::absoluteY, 4, true },
		{ &CPU::NOT, nullptr, 0, false },
		{ &CPU::NOT, nullptr, 0, false },
		{ &CPU::NOT, nullptr, 0, false },
		{ &CPU::EOR, &CPU::absoluteX, 4, true },
		{ &CPU::LSR, &CPU::absoluteX, 7, false },
		{ &CPU::NOT, nullptr, 0, false },
		{ &CPU::RTS, nullptr, 6, false },
		{ &CPU::ADC, &CPU::indirectX, 6, false },
		{ &CPU::NOT, nullptr, 0, false },
		{ &CPU::NOT, nullptr, 0, false },
		{ &CPU::NOT, nullptr, 0, false },
		{ &CPU::ADC, &CPU::zeroPage, 3, false },
		{ &CPU::ROR, &CPU::zeroPage, 5, false },
		{ &CPU::NOT, nullptr, 0, false },
		{ &CPU::PLA, nullptr, 4, false },
		{ &CPU::ADC, &CPU::immediate, 2, false },
		{ &CPU::RORAcc, nullptr, 2, false },
		{ &CPU::NOT, nullptr, 0, false },
		{ &CPU::JMP, &CPU::indirect, 5 },
		{ &CPU::ADC, &CPU::absolute, 4, false },
		{ &CPU::ROR, &CPU::absolute, 6, false },
		{ &CPU::NOT, nullptr, 0, false },
		{ &CPU::BVS, &CPU::relative, 2, false },
		{ &CPU::ADC, &CPU::indirectY, 5, true },
		{ &CPU::NOT, nullptr, 0, false },
		{ &CPU::NOT, nullptr, 0, false },
		{ &CPU::NOT, nullptr, 0, false },
		{ &CPU::ADC, &CPU::zeroPageX, 4, false },
		{ &CPU::ROR, &CPU::zeroPageX, 6, false },
		{ &CPU::NOT, nullptr, 0, false },
		{ &CPU::SEI, nullptr, 2, false },
		{ &CPU::ADC, &CPU::absoluteY, 4, true },
		{ &CPU::NOT, nullptr, 0, false },
		{ &CPU::NOT, nullptr, 0, false },
		{ &CPU::NOT, nullptr, 0, false },
		{ &CPU::ADC, &CPU::absoluteX, 4, true },
		{ &CPU::ROR, &CPU::absoluteX, 7, false },
		{ &CPU::NOT, nullptr, 0, false },
		{ &CPU::NOT, nullptr, 0, false },
		{ &CPU::STA, &CPU::indirectX, 6, false },
		{ &CPU::NOT, nullptr, 0, false },
		{ &CPU::NOT, nullptr, 0, false },
		{ &CPU::STY, &CPU::zeroPage, 3, false },
		{ &CPU::STA, &CPU::zeroPage, 3, false },
		{ &CPU::STX, &CPU::zeroPage, 3, false },
		{ &CPU::NOT, nullptr, 0, false },
		{ &CPU::DEY, nullptr, 2, false },
		{ &CPU::NOT, nullptr, 0, false },
		{ &CPU::TXA, nullptr, 2, false },
		{ &CPU::NOT, nullptr, 0, false },
		{ &CPU::STY, &CPU::absolute, 4, false },
		{ &CPU::STA, &CPU::absolute, 4, false },
		{ &CPU::STX, &CPU::absolute, 4, false },
		{ &CPU::NOT, nullptr, 0, false },
		{ &CPU::BCC, &CPU::relative, 2, false },
		{ &CPU::STA, &CPU::indirectY, 6, false },
		{ &CPU::NOT, nullptr, 0, false },
		{ &CPU::NOT, nullptr, 0, false },
		{ &CPU::STY, &CPU::zeroPageX, 4, false },
		{ &CPU::STA, &CPU::zeroPageX, 4, false },
		{ &CPU::STX, &CPU::zeroPageY, 4, false },
		{ &CPU::NOT, nullptr, 0, false },
		{ &CPU::TYA, nullptr, 2, false },
		{ &CPU::STA, &CPU::absoluteY, 5, false },
		{ &CPU::TXS, nullptr, 2, false },
		{ &CPU::NOT, nullptr, 0, false },
		{ &CPU::NOT, nullptr, 0, false },
		{ &CPU::STA, &CPU::absoluteX, 5, false },
		{ &CPU::NOT, nullptr, 0, false },
		{ &CPU::NOT, nullptr, 0, false },
		{ &CPU::LDY, &CPU::immediate, 2, false },
		{ &CPU::LDA, &CPU::indirectX, 6, false },
		{ &CPU::LDX, &CPU::immediate, 2, false },
		{ &CPU::NOT, nullptr, 0, false },
		{ &CPU::LDY, &CPU::zeroPage, 3, false },
		{ &CPU::LDA, &CPU::zeroPage, 3, false },
		{ &CPU::LDX, &CPU::zeroPage, 3, false },
		{ &CPU::NOT, nullptr, 0, false },
		{ &CPU::TAY, nullptr, 2, false },
		{ &CPU::LDA, &CPU::immediate, 2, false },
		{ &CPU::TAX, nullptr, 2, false },
		{ &CPU::NOT, nullptr, 0, false },
		{ &CPU::LDY, &CPU::absolute, 4, false },
		{ &CPU::LDA, &CPU::absolute, 4, false },
		{ &CPU::LDX, &CPU::absolute, 4, false },
		{ &CPU::NOT, nullptr, 0, false },
		{ &CPU::BCS, &CPU::relative, 2, false },
		{ &CPU::LDA, &CPU::indirectY, 5, true },
		{ &CPU::NOT, nullptr, 0, false },
		{ &CPU::NOT, nullptr, 0, false },
		{ &CPU::LDY, &CPU::zeroPageX, 4, false },
		{ &CPU::LDA, &CPU::zeroPageX, 4, false },
		{ &CPU::LDX, &CPU::zeroPageY, 4, false },
		{ &CPU::NOT, nullptr, 0, false },
		{ &CPU::CLV, nullptr, 2, false },
		{ &CPU::LDA, &CPU::absoluteY, 4, true },
		{ &CPU::TSX, nullptr, 2, false },
		{ &CPU::NOT, nullptr, 0, false },
		{ &CPU::LDY, &CPU::absoluteX, 4 },
		{ &CPU::LDA, &CPU::absoluteX, 4, true },
		{ &CPU::LDX, &CPU::absoluteY, 4 },
		{ &CPU::NOT, nullptr, 0, false },
		{ &CPU::CPY, &CPU::immediate, 2, false },
		{ &CPU::CMP, &CPU::indirectX, 6, false },
		{ &CPU::NOT, nullptr, 0, false },
		{ &CPU::NOT, nullptr, 0, false },
		{ &CPU::CPY, &CPU::zeroPage, 3, false },
		{ &CPU::CMP, &CPU::zeroPage, 3, false },
		{ &CPU::DEC, &CPU::zeroPage, 5, false },
		{ &CPU::NOT, nullptr, 0, false },
		{ &CPU::INY, nullptr, 2, false },
		{ &CPU::CMP, &CPU::immediate, 2, false },
		{ &CPU::DEX, nullptr, 2, false },
		{ &CPU::NOT, nullptr, 0, false },
		{ &CPU::CPY, &CPU::absolute, 4, false },
		{ &CPU::CMP, &CPU::absolute, 4, false },
		{ &CPU::DEC, &CPU::absolute, 6, false },
		{ &CPU::NOT, nullptr, 0, false },
		{ &CPU::BNE, &CPU::relative, 2, false },
		{ &CPU::CMP, &CPU::indirectY, 6, true },
		{ &CPU::NOT, nullptr, 0, false },
		{ &CPU::NOT, nullptr, 0, false },
		{ &CPU::NOT, nullptr, 0, false },
		{ &CPU::CMP, &CPU::zeroPageX, 4, false },
		{ &CPU::DEC, &CPU::zeroPageX, 6, false },
		{ &CPU::NOT, nullptr, 0, false },
		{ &CPU::NOT, nullptr, 0, false }, // CLD not implemented
		{ &CPU::CMP, &CPU::absoluteY, 4, true },
		{ &CPU::NOT, nullptr, 0, false },
		{ &CPU::NOT, nullptr, 0, false },
		{ &CPU::NOT, nullptr, 0, false },
		{ &CPU::CMP, &CPU::absoluteX, 4, true },
		{ &CPU::DEC, &CPU::absoluteX, 7, false },
		{ &CPU::NOT, nullptr, 0, false },
		{ &CPU::CPX, &CPU::immediate, 2, false },
		{ &CPU::SBC, &CPU::indirectX, 6, false },
		{ &CPU::NOT, nullptr, 0, false },
		{ &CPU::NOT, nullptr, 0, false },
		{ &CPU::CPX, &CPU::zeroPage, 3, false },
		{ &CPU::SBC, &CPU::zeroPage, 3, false },
		{ &CPU::INC, &CPU::zeroPage, 5, false },
		{ &CPU::NOT, nullptr, 0, false },
		{ &CPU::INX, nullptr, 2, false },
		{ &CPU::SBC, &CPU::immediate, 2, false },
		{ &CPU::NOP, nullptr, 2, false },
		{ &CPU::NOT, nullptr, 0, false },
		{ &CPU::CPX, &CPU::absolute, 4, false },
		{ &CPU::SBC, &CPU::absolute, 4, false },
		{ &CPU::INC, &CPU::absolute, 6, false },
		{ &CPU::NOT, nullptr, 0, false },
		{ &CPU::BEQ, &CPU::relative, 2, false },
		{ &CPU::SBC, &CPU::indirectY, 5, true },
		{ &CPU::NOT, nullptr, 0, false },
		{ &CPU::NOT, nullptr, 0, false },
		{ &CPU::NOT, nullptr, 0, false },
		{ &CPU::SBC, &CPU::zeroPageX, 4, false },
		{ &CPU::INC, &CPU::zeroPageX, 6, false },
		{ &CPU::NOT, nullptr, 0, false },
		{ &CPU::NOT, nullptr, 0, false }, // SED not implemented
		{ &CPU::SBC, &CPU::absoluteY, 4, true },
		{ &CPU::NOT, nullptr, 0, false },
		{ &CPU::NOT, nullptr, 0, false },
		{ &CPU::NOT, nullptr, 0, false },
		{ &CPU::SBC, &CPU::absoluteX, 4, true },
		{ &CPU::INC, &CPU::absoluteX, 7, false },
		{ &CPU::NOT, nullptr, 0, false }
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
		m_cycleCount = 0;

		while (m_cycleCount < numCycles)
		{
			auto value = m_memory.read(popPC());
			auto opcode = s_opcodes[value];

			WORD address = 0x0000;

			if (opcode.addressingFunction)
			{
				bool pageCrossed = opcode.addressingFunction(*this, address);
				if (pageCrossed && opcode.pageCrossingExtraCycle)
				{
					m_cycleCount++;
				}
			}

			if (!opcode.instruction)
			{
				std::stringstream ss;
				ss << "Opcode " << value << " is undefined.";
				throw UndefinedOpcode(ss.str());
			}

			opcode.instruction(*this, address);

			m_cycleCount += opcode.numCycles;
		}

		return m_cycleCount - numCycles;
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

	void CPU::setStatusFlag(STATUS_BIT bit, bool value)
	{
		m_p.set(bit, value);
	}

	bool CPU::getStatusFlag(STATUS_BIT bit) const
	{
		return m_p[bit];
	}

	void CPU::updateCommonFlags(BYTE value)
	{
		setStatusFlag(STATUS_BIT::FLAG_Z, (value == 0));
		setStatusFlag(STATUS_BIT::FLAG_N, (value >= 0x80));
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
		address += getX();
		return ((address & 0xF0) != (address & 0xF0));
	}

	bool CPU::absoluteY(WORD& address)
	{
		address = getMemory().read(popPC());
		address |= getMemory().read(popPC()) << 8;
		address += getY();
		return ((address & 0xF0) != (address & 0xF0));
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
		throw NotImplementedException("Indirect addressing mode not implemented yet.");
	}

	bool CPU::indirectX(WORD& address)
	{
		throw NotImplementedException("Indirect addressing mode X not implemented yet.");
	}

	bool CPU::indirectY(WORD& address)
	{
		throw NotImplementedException("Indirect addressing mode Y not implemented yet.");
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

	void CPU::ADC(WORD address)
	{
		auto value = m_memory.read(address);
		int result = (int)getA() + (int)value;
		if (getStatusFlag(STATUS_BIT::FLAG_C))
		{
			result++;
		}

		updateCommonFlags(result);
		setStatusFlag(STATUS_BIT::FLAG_C, result >= FULLBYTE);
		setStatusFlag(STATUS_BIT::FLAG_V, ((~(value ^ getA()) & (value ^ result)) & 0x80) > 0);
		// To set the overflow flag, we do this:
		// 1. The first nxor determines if the 8th bits of the initial values are the same (a mask is applied later)
		// 2. The second xor checks if the result's 8th bit is different from the initial value's 8th bit
		//    (I used the value, but I could use the accumulator, since they should have the same 8th bit)
		// 3. Apply a mask to only check the 8th bit
		// 4. The > 0 converts to a boolean value

		setA(result & FULLBYTE);
	}

	void CPU::AND(WORD address)
	{
		auto value = m_memory.read(address);
		auto result = value & getA();

		updateCommonFlags(result);
		setA(result);
	}

	void CPU::ASL(WORD address)
	{
		auto value = m_memory.read(address);
		BYTE result = value << 1;

		setStatusFlag(STATUS_BIT::FLAG_C, (value & 0x80) != 0);
		updateCommonFlags(result);

		m_memory.write(address, result);
	}

	void CPU::ASLAcc(WORD address)
	{
		auto value = getA();
		BYTE result = value << 1;

		setStatusFlag(STATUS_BIT::FLAG_C, (value & 0x80) != 0);
		updateCommonFlags(result);

		setA(result);
	}

	void CPU::BCC(WORD address)
	{
		if (!getStatusFlag(STATUS_BIT::FLAG_C))
		{
			m_cycleCount++;
			if ((getPC() & 0xFF00) != (address & 0xFF00))
			{
				m_cycleCount++;
			}
			setPC(address);
		}
	}

	void CPU::BCS(WORD address)
	{
		if (getStatusFlag(STATUS_BIT::FLAG_C))
		{
			m_cycleCount++;
			if ((getPC() & 0xFF00) != (address & 0xFF00))
			{
				m_cycleCount++;
			}
			setPC(address);
		}
	}

	void CPU::BEQ(WORD address)
	{
		if (getStatusFlag(STATUS_BIT::FLAG_Z))
		{
			m_cycleCount++;
			if ((getPC() & 0xFF00) != (address & 0xFF00))
			{
				m_cycleCount++;
			}
			setPC(address);
		}
	}

	void CPU::BIT(WORD address)
	{
		auto value = m_memory.read(address);
		setStatusFlag(STATUS_BIT::FLAG_Z, (value & getA()) == 0);
		setStatusFlag(STATUS_BIT::FLAG_N, (value & 0x80) != 0);
		setStatusFlag(STATUS_BIT::FLAG_V, (value & 0x40) != 0);
	}

	void CPU::BMI(WORD address)
	{
		if (getStatusFlag(STATUS_BIT::FLAG_N))
		{
			m_cycleCount++;
			if ((getPC() & 0xFF00) != (address & 0xFF00))
			{
				m_cycleCount++;
			}
			setPC(address);
		}
	}

	void CPU::BNE(WORD address)
	{
		if (!getStatusFlag(STATUS_BIT::FLAG_Z))
		{
			m_cycleCount++;
			if ((getPC() & 0xFF00) != (address & 0xFF00))
			{
				m_cycleCount++;
			}
			setPC(address);
		}
	}

	void CPU::BPL(WORD address)
	{
		if (!getStatusFlag(STATUS_BIT::FLAG_N))
		{
			m_cycleCount++;
			if ((getPC() & 0xFF00) != (address & 0xFF00))
			{
				m_cycleCount++;
			}
			setPC(address);
		}
	}

	void CPU::BRK(WORD address)
	{
		throw NotImplementedException("BRK opcode not implemented yet.");
	}

	void CPU::BVC(WORD address)
	{
		if (!getStatusFlag(STATUS_BIT::FLAG_V))
		{
			m_cycleCount++;
			if ((getPC() & 0xFF00) != (address & 0xFF00))
			{
				m_cycleCount++;
			}
			setPC(address);
		}
	}

	void CPU::BVS(WORD address)
	{
		if (getStatusFlag(STATUS_BIT::FLAG_V))
		{
			m_cycleCount++;
			if ((getPC() & 0xFF00) != (address & 0xFF00))
			{
				m_cycleCount++;
			}
			setPC(address);
		}
	}
	
	void CPU::CLC(WORD address)
	{
		setStatusFlag(STATUS_BIT::FLAG_C, false);
	}
	
	void CPU::CLI(WORD address)
	{
		setStatusFlag(STATUS_BIT::FLAG_I, false);
	}
	
	void CPU::CLV(WORD address)
	{
		setStatusFlag(STATUS_BIT::FLAG_V, false);
	}
	
	void CPU::CMP(WORD address)
	{
		throw NotImplementedException("CMP opcode not implemented yet.");
	}
	
	void CPU::CPX(WORD address)
	{
		throw NotImplementedException("CPX opcode not implemented yet.");
	}
	
	void CPU::CPY(WORD address)
	{
		throw NotImplementedException("CPY opcode not implemented yet.");
	}
	
	void CPU::DEC(WORD address)
	{
		throw NotImplementedException("DEC opcode not implemented yet.");
	}
	
	void CPU::DEX(WORD address)
	{
		throw NotImplementedException("DEX opcode not implemented yet.");
	}
	
	void CPU::DEY(WORD address)
	{
		throw NotImplementedException("DEY opcode not implemented yet.");
	}
	
	void CPU::EOR(WORD address)
	{
		throw NotImplementedException("EOR opcode not implemented yet.");
	}
	
	void CPU::INC(WORD address)
	{
		throw NotImplementedException("INC opcode not implemented yet.");
	}
	
	void CPU::INX(WORD address)
	{
		throw NotImplementedException("INX opcode not implemented yet.");
	}
	
	void CPU::INY(WORD address)
	{
		throw NotImplementedException("INY opcode not implemented yet.");
	}
	
	void CPU::JMP(WORD address)
	{
		throw NotImplementedException("JMP opcode not implemented yet.");
	}
	
	void CPU::JSR(WORD address)
	{
		throw NotImplementedException("JSR opcode not implemented yet.");
	}
	
	void CPU::LDA(WORD address)
	{
		throw NotImplementedException("LDA opcode not implemented yet.");
	}
	
	void CPU::LDX(WORD address)
	{
		throw NotImplementedException("LDX opcode not implemented yet.");
	}
	
	void CPU::LDY(WORD address)
	{
		throw NotImplementedException("LDY opcode not implemented yet.");
	}
	
	void CPU::LSR(WORD address)
	{
		throw NotImplementedException("LSR opcode not implemented yet.");
	}

	void CPU::LSRAcc(WORD address)
	{
		throw NotImplementedException("LSR opcode not implemented yet.");
	}
	
	void CPU::NOP(WORD address)
	{
		throw NotImplementedException("NOP opcode not implemented yet.");
	}
	
	void CPU::ORA(WORD address)
	{
		throw NotImplementedException("ORA opcode not implemented yet.");
	}
	
	void CPU::PHA(WORD address)
	{
		throw NotImplementedException("PHA opcode not implemented yet.");
	}
	
	void CPU::PHP(WORD address)
	{
		throw NotImplementedException("PHP opcode not implemented yet.");
	}
	
	void CPU::PLA(WORD address)
	{
		throw NotImplementedException("PLA opcode not implemented yet.");
	}
	
	void CPU::PLP(WORD address)
	{
		throw NotImplementedException("PLP opcode not implemented yet.");
	}
	
	void CPU::ROL(WORD address)
	{
		throw NotImplementedException("ROL opcode not implemented yet.");
	}

	void CPU::ROLAcc(WORD address)
	{
		throw NotImplementedException("ROL opcode not implemented yet.");
	}
	
	void CPU::ROR(WORD address)
	{
		throw NotImplementedException("ROR opcode not implemented yet.");
	}

	void CPU::RORAcc(WORD address)
	{
		throw NotImplementedException("ROR opcode not implemented yet.");
	}
	
	void CPU::RTI(WORD address)
	{
		throw NotImplementedException("RTI opcode not implemented yet.");
	}
	
	void CPU::RTS(WORD address)
	{
		throw NotImplementedException("RTS opcode not implemented yet.");
	}
	
	void CPU::SBC(WORD address)
	{
		throw NotImplementedException("SBC opcode not implemented yet.");
	}
	
	void CPU::SEC(WORD address)
	{
		setStatusFlag(STATUS_BIT::FLAG_C, true);
	}
	
	void CPU::SEI(WORD address)
	{
		setStatusFlag(STATUS_BIT::FLAG_I, true);
	}
	
	void CPU::STA(WORD address)
	{
		throw NotImplementedException("STA opcode not implemented yet.");
	}
	
	void CPU::STX(WORD address)
	{
		throw NotImplementedException("STX opcode not implemented yet.");
	}
	
	void CPU::STY(WORD address)
	{
		throw NotImplementedException("STY opcode not implemented yet.");
	}
	
	void CPU::TAX(WORD address)
	{
		throw NotImplementedException("TAX opcode not implemented yet.");
	}
	
	void CPU::TAY(WORD address)
	{
		throw NotImplementedException("TAY opcode not implemented yet.");
	}
	
	void CPU::TSX(WORD address)
	{
		throw NotImplementedException("TSX opcode not implemented yet.");
	}
	
	void CPU::TXA(WORD address)
	{
		throw NotImplementedException("TXA opcode not implemented yet.");
	}
	
	void CPU::TXS(WORD address)
	{
		throw NotImplementedException("TXS opcode not implemented yet.");
	}
	
	void CPU::TYA(WORD address)
	{
		throw NotImplementedException("TYA opcode not implemented yet.");
	}
	
	void CPU::NOT(WORD address)
	{
		throw UndefinedOpcode("Invalid opcode.");
	}
}
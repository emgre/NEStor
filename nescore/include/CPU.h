#ifndef CPU_H
#define CPU_H

#include "basic_types.h"
#include <functional>
#include <bitset>
#include <array>

namespace nescore
{
	class IMemory;

	class CPU
	{
	public:
		enum class StatusFlag
		{
			C = 0,
			Z,
			I,
			// Decimal flag not implemented
			B = 4,
			// Unused flag
			V = 6,
			N
		};

		CPU(IMemory& memory);
		CPU(const CPU&) = delete;
		CPU& operator=(const CPU&) = delete;

		void reset();
		unsigned int executeCycles(unsigned int numCycles);

		IMemory& getMemory() const;

		WORD popPC();
		void setPC(WORD pc);
		WORD getPC() const;

		void setA(BYTE a);
		BYTE getA() const;

		void setX(BYTE x);
		BYTE getX() const;

		void setY(BYTE y);
		BYTE getY() const;

		void setStatusFlag(StatusFlag flag, bool value);
		bool getStatusFlag(StatusFlag flag) const;
	
	private:
		IMemory& m_memory;
		unsigned int m_cycleCount;

		// Internal registers
		WORD m_pc;
		BYTE m_sp;
		BYTE m_a;
		BYTE m_x;
		BYTE m_y;
		std::bitset<8> m_p;

		// Utils
		void updateCommonFlags(BYTE value);

		// Adressing function
		bool immediate(WORD& address);
		bool absolute(WORD& address);
		bool absoluteX(WORD& address);
		bool absoluteY(WORD& address);
		bool zeroPage(WORD& address);
		bool zeroPageX(WORD& address);
		bool zeroPageY(WORD& address);
		bool indirect(WORD& address);
		bool indirectX(WORD& address);
		bool indirectY(WORD& address);
		bool relative(WORD& address);

		// Opcodes declaration
		void ADC(WORD address);
		void AND(WORD address);
		void ASL(WORD address);
		void ASLAcc(WORD address);
		void BCC(WORD address);
		void BCS(WORD address);
		void BEQ(WORD address);
		void BIT(WORD address);
		void BMI(WORD address);
		void BNE(WORD address);
		void BPL(WORD address);
		void BRK(WORD address);
		void BVC(WORD address);
		void BVS(WORD address);
		void CLC(WORD address);
		void CLI(WORD address);
		void CLV(WORD address);
		void CMP(WORD address);
		void CPX(WORD address);
		void CPY(WORD address);
		void DEC(WORD address);
		void DEX(WORD address);
		void DEY(WORD address);
		void EOR(WORD address);
		void INC(WORD address);
		void INX(WORD address);
		void INY(WORD address);
		void JMP(WORD address);
		void JSR(WORD address);
		void LDA(WORD address);
		void LDX(WORD address);
		void LDY(WORD address);
		void LSR(WORD address);
		void LSRAcc(WORD address);
		void NOP(WORD address);
		void ORA(WORD address);
		void PHA(WORD address);
		void PHP(WORD address);
		void PLA(WORD address);
		void PLP(WORD address);
		void ROL(WORD address);
		void ROLAcc(WORD address);
		void ROR(WORD address);
		void RORAcc(WORD address);
		void RTI(WORD address);
		void RTS(WORD address);
		void SBC(WORD address);
		void SEC(WORD address);
		void SEI(WORD address);
		void STA(WORD address);
		void STX(WORD address);
		void STY(WORD address);
		void TAX(WORD address);
		void TAY(WORD address);
		void TSX(WORD address);
		void TXA(WORD address);
		void TXS(WORD address);
		void TYA(WORD address);
		void NOT(WORD address);

		struct Opcode
		{
			std::function<void(CPU&, WORD)> instruction;
			std::function<bool(CPU&, WORD&)> addressingFunction;
			unsigned int numCycles;
			bool pageCrossingExtraCycle;
		};
		static const std::array<Opcode, 256> s_opcodes;
	};
}

#endif // CPU_H
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
		unsigned int executeSingleInstruction();

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

		void setSP(BYTE sp);
		BYTE getSP() const;

		void setStatusFlag(StatusFlag flag, bool value);
		bool getStatusFlag(StatusFlag flag) const;
	
	private:
		IMemory& m_memory;

		// Internal registers
		WORD m_pc;
		BYTE m_sp;
		BYTE m_a;
		BYTE m_x;
		BYTE m_y;
		std::bitset<8> m_p;

		// Utils
		void updateCommonFlags(BYTE value);
		void pushStack(BYTE value);
		BYTE pullStack();

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
		unsigned int ADC(WORD address);
		unsigned int AND(WORD address);
		unsigned int ASL(WORD address);
		unsigned int ASLAcc(WORD address);
		unsigned int BCC(WORD address);
		unsigned int BCS(WORD address);
		unsigned int BEQ(WORD address);
		unsigned int BIT(WORD address);
		unsigned int BMI(WORD address);
		unsigned int BNE(WORD address);
		unsigned int BPL(WORD address);
		unsigned int BRK(WORD address);
		unsigned int BVC(WORD address);
		unsigned int BVS(WORD address);
		unsigned int CLC(WORD address);
		unsigned int CLI(WORD address);
		unsigned int CLV(WORD address);
		unsigned int CMP(WORD address);
		unsigned int CPX(WORD address);
		unsigned int CPY(WORD address);
		unsigned int DEC(WORD address);
		unsigned int DEX(WORD address);
		unsigned int DEY(WORD address);
		unsigned int EOR(WORD address);
		unsigned int INC(WORD address);
		unsigned int INX(WORD address);
		unsigned int INY(WORD address);
		unsigned int JMP(WORD address);
		unsigned int JSR(WORD address);
		unsigned int LDA(WORD address);
		unsigned int LDX(WORD address);
		unsigned int LDY(WORD address);
		unsigned int LSR(WORD address);
		unsigned int LSRAcc(WORD address);
		unsigned int NOP(WORD address);
		unsigned int ORA(WORD address);
		unsigned int PHA(WORD address);
		unsigned int PHP(WORD address);
		unsigned int PLA(WORD address);
		unsigned int PLP(WORD address);
		unsigned int ROL(WORD address);
		unsigned int ROLAcc(WORD address);
		unsigned int ROR(WORD address);
		unsigned int RORAcc(WORD address);
		unsigned int RTI(WORD address);
		unsigned int RTS(WORD address);
		unsigned int SBC(WORD address);
		unsigned int SEC(WORD address);
		unsigned int SEI(WORD address);
		unsigned int STA(WORD address);
		unsigned int STX(WORD address);
		unsigned int STY(WORD address);
		unsigned int TAX(WORD address);
		unsigned int TAY(WORD address);
		unsigned int TSX(WORD address);
		unsigned int TXA(WORD address);
		unsigned int TXS(WORD address);
		unsigned int TYA(WORD address);
		unsigned int NOT(WORD address);

		struct Opcode
		{
			std::function<unsigned int(CPU&, WORD)> instruction;
			std::function<bool(CPU&, WORD&)> addressingFunction;
			unsigned int numCycles;
			bool pageCrossingExtraCycle;
		};
		static const std::array<Opcode, 256> s_opcodes;
	};
}

#endif // CPU_H
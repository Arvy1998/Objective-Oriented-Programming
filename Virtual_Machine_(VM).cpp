#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <iterator>
#include <algorithm>
#include <vector>
#include <bitset>

using namespace std;

bitset<4> temporaryRegIndex1, temporaryRegIndex2;
bitset<8> cop1inBinary, binaryDivider = 0b00001111;

typedef struct {
	char code;
	char cop1;
} VMCommand;

class VirtualMachine {
public:
	ifstream outputFileBinary;
	unsigned char regs[16]; // registrai
	char prog_mem[256]; // programos atmintis
	int ieof_flag; // flagas - veliavu registras
	int iReg1 = 0, iReg2 = 0;
	VMCommand* r_pc;
	bool stopExecution, JMPIsDone;

	void r_pcIncrementation() {
		r_pc++;
		iReg1 = r_pc->cop1 & 0x0F;
		iReg2 = r_pc->cop1 & 0x0F >> 4;
	}

	void instructionCases(const char pointerToVMCommandCharCode, ifstream &q1Encryption) {
		switch (pointerToVMCommandCharCode) {
		case 0x01: INC();			  break;
		case 0x02: DEC();			  break;
		case 0x03: MOV();			  break;
		case 0x04: MOVC();			  break;
		case 0x05: LSL();			  break;
		case 0x06: LSR();			  break;
		case 0x07: JMP();			  break;
		case 0x0A: JFE();			  break;
		case 0x0B: RET();			  break;
		case 0x0C: ADD();			  break;
		case 0x0D: SUB();			  break;
		case 0x0E: XOR();			  break;
		case 0x0F: OR();			  break;
		case 0x10: IN(q1Encryption);  break;
		case 0x11: OUT();			  break;
		default:					  break;
		}
	}

	void INC() {}
	void DEC() {}

	void MOV() {
		cop1inBinary = r_pc->cop1;
		temporaryRegIndex1 = (cop1inBinary & binaryDivider).to_ulong();
		temporaryRegIndex2 = ((cop1inBinary >> 4) & binaryDivider).to_ulong();
		regs[temporaryRegIndex1.to_ulong()] = regs[temporaryRegIndex2.to_ulong()];
	}

	void MOVC() {
		regs[0] = r_pc->cop1;
	}

	void LSL() {
		cop1inBinary = r_pc->cop1;
		temporaryRegIndex1 = (cop1inBinary & binaryDivider).to_ulong();
		regs[temporaryRegIndex1.to_ulong()] <<= 1;
	}

	void LSR() {
		cop1inBinary = r_pc->cop1;
		temporaryRegIndex1 = (cop1inBinary & binaryDivider).to_ulong();
		regs[temporaryRegIndex1.to_ulong()] >>= 1;
	}

	void JMP() {
		r_pc = (VMCommand*)((char*)r_pc + r_pc->cop1);
		iReg1 = r_pc->cop1 & 0x0F;
		iReg2 = r_pc->cop1 & 0x0F >> 4;
		JMPIsDone = true;
	}

	void JFE() {
		if (ieof_flag) {
			JMP();
		}
	}

	void RET() {
		stopExecution = true;
	}

	void ADD() {
		cop1inBinary = r_pc->cop1;
		temporaryRegIndex1 = (cop1inBinary & binaryDivider).to_ulong();
		temporaryRegIndex2 = ((cop1inBinary >> 4) & binaryDivider).to_ulong();
		regs[temporaryRegIndex1.to_ulong()] += regs[temporaryRegIndex2.to_ulong()];
	}

	void SUB() {
		cop1inBinary = r_pc->cop1;
		temporaryRegIndex1 = (cop1inBinary & binaryDivider).to_ulong();
		temporaryRegIndex2 = ((cop1inBinary >> 4) & binaryDivider).to_ulong();
		regs[temporaryRegIndex1.to_ulong()] -= regs[temporaryRegIndex2.to_ulong()];
	}

	void XOR() {
		cop1inBinary = r_pc->cop1;
		temporaryRegIndex1 = (cop1inBinary & binaryDivider).to_ulong();
		temporaryRegIndex2 = ((cop1inBinary >> 4) & binaryDivider).to_ulong();
		regs[temporaryRegIndex1.to_ulong()] ^= regs[temporaryRegIndex2.to_ulong()];
	}

	void OR() {
		cop1inBinary = r_pc->cop1;
		temporaryRegIndex1 = (cop1inBinary & binaryDivider).to_ulong();
		temporaryRegIndex2 = ((cop1inBinary >> 4) & binaryDivider).to_ulong();
		regs[temporaryRegIndex1.to_ulong()] |= regs[temporaryRegIndex2.to_ulong()];
	}

	void IN(ifstream &q1Encryption) {
		char temporaryCharacter;
		if (q1Encryption.eof()) {
			ieof_flag = 1;
		}
		else {
			q1Encryption.get(temporaryCharacter);
			*(regs + iReg1) = static_cast<unsigned char>(temporaryCharacter);
			ieof_flag = 0;
		}
	}

	void OUT() {
		if (ieof_flag == 0) {
			temporaryRegIndex1 = (cop1inBinary & binaryDivider).to_ulong();
			cout << regs[temporaryRegIndex1.to_ulong()];
		}
	}

	void machineExecution() {
		ifstream q1Encryption;
		q1Encryption.open("q1_encr.txt");
		r_pc = (VMCommand*)prog_mem;
		//r_pc = reinterpret_cast<VMCommand*>(prog_mem);
		iReg1 = r_pc->cop1 & 0x0F;
		iReg2 = r_pc->cop1 & 0x0F >> 4;
		while (stopExecution == false) {
			instructionCases(r_pc->code, q1Encryption);
			if (JMPIsDone == false) {
				r_pcIncrementation();
			}
			JMPIsDone = false;
		}
	}

	VirtualMachine() {
		stopExecution = false;
		ieof_flag = 0;
		JMPIsDone = false;
	}

	~VirtualMachine() {
		stopExecution = false;
		ieof_flag = 0;
		JMPIsDone = false;
	}
};

int main()
{
	VirtualMachine virtualMachine;
	virtualMachine.outputFileBinary.open("decryptor.bin", ios_base::binary);
	int iterator = 0;
	while (!virtualMachine.outputFileBinary.eof()) {
		virtualMachine.outputFileBinary.get(virtualMachine.prog_mem[iterator]);
		iterator++;
	}
	virtualMachine.outputFileBinary.close();
	virtualMachine.machineExecution();
	cout << endl << endl;
    return 0;
}

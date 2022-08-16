#include <stdio.h>		// IO
#include <stdint.h>		// uint16_t
#include <string.h>		// strcpy()
#include <stdlib.h>		// system()
#include <stdbool.h>	// bool

#include "../asm/libasm.h"	// disassemble()

#define clearscr() printf("\033[H\033[J")

int main(int argc, char const *argv[])
{
	char infilePath[50];

	// Command line arguments
	if (argc == 1) {
		printf("Not enough arguments given\n");
		return 0;
	}
	if (argc > 1) {
		strcpy(infilePath, argv[1]);
	}

	// Open the input file
	FILE *infile;
	infile = fopen(infilePath, "rb");
	if (infile == NULL) { printf("Couldn't open %s\n", infilePath); return 0; }
	int infileLen;
	fseek(infile, 0L, SEEK_END);
	infileLen = ftell(infile);
	rewind(infile);

	// TODO : Display mem, stack, stack pointer and return addr
	uint8_t mem[0xFFFF];		// 64 KiB of memory
	uint16_t reg[10];			// 10 Registers
	uint16_t pc = 0x0000;
	uint16_t retAddr = 0x0000;
	uint16_t stckPtr = 0xFDFF;	// Initialise the stack pointer at the base of the stack
	bool ltFlg = false;
	bool eqFlg = false;
	bool gtFlg = false;

	bool jumped = false;		// Used to make sure the pc isn't incremented when it shouldn't be

	// Initialise all of memory and the registers to zero
	int i;
	for (i=0;i<0xFFFF;i++) {
		mem[i] = 0;
	}
	for (i=0;i<10;i++) {
		reg[i] = 0;
	}

	// Load the program in to memory
	for (i=0;i<infileLen;i++) {
		if (fread(mem+i, 1, 1, infile) != 1) {
			printf("%s was unable to be read!\n", infilePath);
			return 0;
		}
	}

	do {
		jumped = false;

		// Clear the screen
		clearscr();

		// Use libasm to disassemble and print the current instruction
		Instruction inst;
		inst.opcode = mem[pc];
		inst.data1 = mem[pc+1];
		inst.data2 = mem[pc+2];
		inst.data3 = mem[pc+3];
		Mnemonic disasmed = disassemble(inst);
		printf("Instruction = %s", disasmed.inst);
		// Only print out arg1 or arg2 if needed
		if (strcmp(disasmed.arg1, "")) {
			printf(" %s", disasmed.arg1);
		}
		if (strcmp(disasmed.arg2, "")) {
			printf(" %s", disasmed.arg2);
		}
		printf("\n");

		// Run the program
		if (mem[pc] == 0x00) {}		// NOP
		else if (mem[pc] == 0x02) {	// LD REG REG
			reg[mem[pc+1]] = reg[mem[pc+2]];
		}
		else if (mem[pc] == 0x03) {	// LD REG REG
			reg[mem[pc+1]] = (mem[pc+2] << 8) + mem[pc+3];
		}
		else if (mem[pc] == 0x04) {	// LD REG ADDR
			reg[mem[pc+1]] = (mem[(mem[pc+2] << 8) + mem[pc+3]] << 8) + mem[(mem[pc+2] << 8) + mem[pc+3] + 1];	// Pure black magic, I don't understand this and I wrote it
		}
		else if (mem[pc] == 0x05) {	// LD ADDR REG
			mem[(mem[pc+1] << 8) + mem[pc+2]] = (reg[mem[pc+3]] & 0xFF00) >> 8;
			mem[(mem[pc+1] << 8) + mem[pc+2] + 1] = reg[mem[pc+3]] & 0x00FF;
		}
		else if (mem[pc] == 0x06) {	// ADD REG REG
			reg[mem[pc+1]] = reg[mem[pc+1]] + reg[mem[pc+2]];
		}
		else if (mem[pc] == 0x07) {	// SUB REG REG
			reg[mem[pc+1]] = reg[mem[pc+1]] - reg[mem[pc+2]];
		}
		else if (mem[pc] == 0x08) {	// MUL REG REG
			reg[mem[pc+1]] = reg[mem[pc+1]] * reg[mem[pc+2]];
		}
		else if (mem[pc] == 0x09) {	// DIV REG REG
			reg[mem[pc+1]] = reg[mem[pc+1]] / reg[mem[pc+2]];
		}

		// TODO
		//else if (mem[pc] == 0x0A) {	// PUSH REG
		//}
		//else if (mem[pc] == 0x0B) {	// POP REG
		//}

		// TODO : This should work but I can't even assemble jumps yet
		//else if (mem[pc] == 0x0C) {	// JMP ADDR
		//	retAddr = pc + 4;
		//	pc = (mem[pc+2] << 8) + mem[pc+3];
		//	jumped = true;
		//}
		//else if (mem[pc] == 0x0D) {	// JMPL ADDR
		//	if (ltFlg == true) {
		//		retAddr = pc + 4;
		//		pc = (mem[pc+2] << 8) + mem[pc+3];
		//		jumped = true;
		//	}
		//}
		//else if (mem[pc] == 0x0E) {	// JMPE ADDR
		//	if (eqFlg == true) {
		//		retAddr = pc + 4;
		//		pc = (mem[pc+2] << 8) + mem[pc+3];
		//		jumped = true;
		//	}
		//}
		//else if (mem[pc] == 0x0F) {	// JMPG ADDR
		//	if (gtFlg == true) {
		//		retAddr = pc + 4;
		//		pc = (mem[pc+2] << 8) + mem[pc+3];
		//		jumped = true;
		//	}
		//}
		else if (mem[pc] == 0x10) {	// RET
			pc = retAddr;
			jumped = true;
		}
		else if (mem[pc] == 0x11) {	// CMP REG REG
			if (reg[mem[pc+1]] < reg[mem[pc+2]]) { ltFlg = true; }
			if (reg[mem[pc+1]] == reg[mem[pc+2]]) { eqFlg = true; }
			if (reg[mem[pc+1]] > reg[mem[pc+2]]) { gtFlg = true; }
		}
		else if (mem[pc] == 0x12) {	// CLF
			ltFlg = false;
			eqFlg = false;
			gtFlg = false;
		}
		else if (mem[pc] == 0x13) {	// AND REG REG
			reg[mem[pc+1]] = reg[mem[pc+1]] & reg[mem[pc+2]];
		}
		else if (mem[pc] == 0x14) {	// OR REG REG
			reg[mem[pc+1]] = reg[mem[pc+1]] | reg[mem[pc+2]];
		}
		else if (mem[pc] == 0x15) {	// NOT REG
			reg[mem[pc+1]] = ~reg[mem[pc+1]];
		}
		else if (mem[pc] == 0x16) {	// XOR REG REG
			reg[mem[pc+1]] = reg[mem[pc+1]] ^ reg[mem[pc+2]];
		}
		else if (mem[pc] == 0x17) {	// LSHIFT REG VAL
			reg[mem[pc+1]] = reg[mem[pc+1]] << ((mem[(mem[pc+2] << 8) + mem[pc+3]] << 8) + mem[(mem[pc+2] << 8) + mem[pc+3] + 1]);	// The same black magic as before, still don't get it
		}
		else if (mem[pc] == 0x18) {	// RSHIFT REG VAL
			reg[mem[pc+1]] = reg[mem[pc+1]] >> ((mem[(mem[pc+2] << 8) + mem[pc+3]] << 8) + mem[(mem[pc+2] << 8) + mem[pc+3] + 1]);	// The same black magic as before, still don't get it
		}
		else if (mem[pc] == 0x19) {	// INC REG
			reg[mem[pc+1]]++;
		}
		else if (mem[pc] == 0x20) {	// DEC REG
			reg[mem[pc+1]]--;
		}
		else if (mem[pc] != 0x01) {
			printf("%X (Addr = %X) didn't match with anything\n", mem[pc], pc);
		}

		// Increment the program counter to the next instruction if the previous instruction wasn't any kind of jump
		if (jumped == false) {
			pc = pc + 4;
		}

		// Print out all the registers
		printf("\n");
		for (i=0;i<10;i++) {
			printf("R%d = %d   ", i, reg[i]);
		}
		printf("\n");
		
		// Print out the flags
		printf("LT = %d   EQ = %d   GT = %d\n", ltFlg, eqFlg, gtFlg);

		printf("\n");
		printf("%x %x %x %x\n", mem[0], mem[1], mem[2], mem[3]);
		printf("%x %x %x %x\n", mem[4], mem[5], mem[6], mem[7]);
		printf("%x %x %x %x\n", mem[8], mem[9], mem[10], mem[11]);
		printf("%x %x %x %x\n", mem[12], mem[13], mem[14], mem[15]);
		printf("%x %x %x %x\n", mem[16], mem[17], mem[18], mem[19]);
		printf("%x %x %x %x\n", mem[20], mem[21], mem[22], mem[23]);
		printf("%x %x %x %x\n", mem[24], mem[25], mem[26], mem[27]);

		getchar();	// Wait for the user to step the program
	} while (mem[pc-4] != 0x01);	// While the program has not halted

	fclose(infile);
	return 0;
}

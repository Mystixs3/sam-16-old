#ifndef LIBASM_H
#define LIBASM_H

#include <stdint.h>

typedef struct {
	char inst[50];
	char arg1[50];
	char arg2[50];
} Mnemonic;

typedef struct {
	uint8_t opcode;
	uint8_t data1;
	uint8_t data2;
	uint8_t data3;
} Instruction;

Instruction assemble(Mnemonic input);
Mnemonic disassemble(Instruction input);

#endif
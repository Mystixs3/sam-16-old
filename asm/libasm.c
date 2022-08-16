#include <stdio.h>	// IO
#include <stdint.h>	// uint8_t
#include <string.h>	// strcpy(), strcmp()
#include <ctype.h>	// toupper()
#include <stdlib.h> // atoi()

#include "libasm.h"

Instruction assemble(Mnemonic input)
{
	Instruction output;

	// Make sure everything is uppercase
	int i;
	for (i=0; i < 50; i++) {
		input.inst[i] = toupper(input.inst[i]);
		input.arg1[i] = toupper(input.arg1[i]);
		input.arg2[i] = toupper(input.arg2[i]);
	}

	// Match the input to an instruction
	if (!strcmp(input.inst, "NOP")) {
		output.opcode = 0x00;
		output.data1 = 0x00;
		output.data2 = 0x00;
		output.data3 = 0x00;
		return output;
	}
	if (!strcmp(input.inst, "HLT")) {
		output.opcode = 0x01;
		output.data1 = 0x00;
		output.data2 = 0x00;
		output.data3 = 0x00;
		return output;
	}
	if (!strcmp(input.inst, "LD")) {
		if (input.arg1[0] == 'R' && input.arg2[0] == 'R') {
			output.opcode = 0x02;
			output.data1 = atoi(&input.arg1[1]);
			output.data2 = atoi(&input.arg2[1]);
			output.data3 = 0x00;
			return output;
		}
		if (input.arg1[0] == 'R' && input.arg2[0] != 'R' && input.arg2[0] != '$') {
			output.opcode = 0x03;
			output.data1 = atoi(&input.arg1[1]);
			output.data2 = (atoi(input.arg2) >> 8) & 0xFF;
			output.data3 = atoi(input.arg2) & 0xFF;
			return output;
		}
		if (input.arg1[0] == 'R' && input.arg2[0] == '$') {
			output.opcode = 0x04;
			output.data1 = atoi(&input.arg1[1]);
			output.data2 = (atoi(input.arg2+1) >> 8) & 0xFF;
			output.data3 = atoi(input.arg2+1) & 0xFF;
			return output;
		}
		if (input.arg1[0] == '$' && input.arg2[0] == 'R') {
			output.opcode = 0x05;
			output.data1 = (atoi(input.arg1+1) >> 8) & 0xFF;
			output.data2 = atoi(input.arg1+1) & 0xFF;
			output.data3 = atoi(&input.arg2[1]);
			return output;
		}
	}
	if (!strcmp(input.inst, "ADD")) {
		output.opcode = 0x06;
		output.data1 = atoi(&input.arg1[1]);
		output.data2 = atoi(&input.arg2[1]);
		output.data3 = 0x00;
		return output;
	}
	if (!strcmp(input.inst, "SUB")) {
		output.opcode = 0x07;
		output.data1 = atoi(&input.arg1[1]);
		output.data2 = atoi(&input.arg2[1]);
		output.data3 = 0x00;
		return output;
	}
	if (!strcmp(input.inst, "MUL")) {
		output.opcode = 0x08;
		output.data1 = atoi(&input.arg1[1]);
		output.data2 = atoi(&input.arg2[1]);
		output.data3 = 0x00;
		return output;
	}
	if (!strcmp(input.inst, "DIV")) {
		output.opcode = 0x09;
		output.data1 = atoi(&input.arg1[1]);
		output.data2 = atoi(&input.arg2[1]);
		output.data3 = 0x00;
		return output;
	}
	if (!strcmp(input.inst, "PUSH")) {
		output.opcode = 0x0A;
		output.data1 = atoi(&input.arg1[1]);
		output.data2 = 0x00;
		output.data3 = 0x00;
		return output;
	}
	if (!strcmp(input.inst, "POP")) {
		output.opcode = 0x0B;
		output.data1 = atoi(&input.arg1[1]);
		output.data2 = 0x00;
		output.data3 = 0x00;
		return output;
	}

	// 	TODO
	//if (!strcmp(input.inst, "JMP")) {
	//}
	//if (!strcmp(input.inst, "JMPL")) {
	//}
	//if (!strcmp(input.inst, "JMPE")) {
	//}
	//if (!strcmp(input.inst, "JMPG")) {
	//}

	if (!strcmp(input.inst, "RET")) {
		output.opcode = 0x10;
		output.data1 = 0x00;
		output.data2 = 0x00;
		output.data3 = 0x00;
		return output;
	}
	if (!strcmp(input.inst, "CMP")) {
		output.opcode = 0x11;
		output.data1 = atoi(&input.arg1[1]);
		output.data2 = atoi(&input.arg2[1]);
		output.data3 = 0x00;
		return output;
	}
	if (!strcmp(input.inst, "CLF")) {
		output.opcode = 0x12;
		output.data1 = 0x00;
		output.data2 = 0x00;
		output.data3 = 0x00;
		return output;
	}
	if (!strcmp(input.inst, "AND")) {
		output.opcode = 0x13;
		output.data1 = atoi(&input.arg1[1]);
		output.data2 = atoi(&input.arg2[1]);
		output.data3 = 0x00;
		return output;
	}
	if (!strcmp(input.inst, "OR")) {
		output.opcode = 0x14;
		output.data1 = atoi(&input.arg1[1]);
		output.data2 = atoi(&input.arg2[1]);
		output.data3 = 0x00;
		return output;
	}
	if (!strcmp(input.inst, "NOT")) {
		output.opcode = 0x15;
		output.data1 = atoi(&input.arg1[1]);
		output.data2 = 0x00;
		output.data3 = 0x00;
		return output;
	}
	if (!strcmp(input.inst, "XOR")) {
		output.opcode = 0x16;
		output.data1 = atoi(&input.arg1[1]);
		output.data2 = atoi(&input.arg2[1]);
		output.data3 = 0x00;
		return output;
	}
	if (!strcmp(input.inst, "LSHIFT")) {
		output.opcode = 0x17;
		output.data1 = atoi(&input.arg1[1]);
		output.data2 = (atoi(input.arg2+1) >> 8) & 0xFF;
		output.data3 = atoi(input.arg2+1) & 0xFF;
		return output;
	}
	if (!strcmp(input.inst, "RSHIFT")) {
		output.opcode = 0x18;
		output.data1 = atoi(&input.arg1[1]);
		output.data2 = (atoi(input.arg2+1) >> 8) & 0xFF;
		output.data3 = atoi(input.arg2+1) & 0xFF;
		return output;
	}
	if (!strcmp(input.inst, "INC")) {
		output.opcode = 0x19;
		output.data1 = atoi(&input.arg1[1]);
		output.data2 = 0x00;
		output.data3 = 0x00;
		return output;
	}
	if (!strcmp(input.inst, "DEC")) {
		output.opcode = 0x20;
		output.data1 = atoi(&input.arg1[1]);
		output.data2 = 0x00;
		output.data3 = 0x00;
		return output;
	}
}

Mnemonic disassemble(Instruction input)
{
	Mnemonic output;

	// Match the input to an opcode
	if (input.opcode == 0x00) {
		strcpy(output.inst, "NOP");
		strcpy(output.arg1, "");
		strcpy(output.arg2, "");
		return output;
	}
	if (input.opcode == 0x01) {
		strcpy(output.inst, "HLT");
		strcpy(output.arg1, "");
		strcpy(output.arg2, "");
		return output;
	}
	if (input.opcode == 0x02) {
		strcpy(output.inst, "LD");
		sprintf(output.arg1, "R%d", input.data1);
		sprintf(output.arg2, "R%d", input.data2);
		return output;
	}
	if (input.opcode == 0x03) {
		strcpy(output.inst, "LD");
		sprintf(output.arg1, "R%d", input.data1);
		sprintf(output.arg2, "%d", (input.data2 << 8) + input.data3);
		return output;
	}
	if (input.opcode == 0x04) {
		strcpy(output.inst, "LD");
		sprintf(output.arg1, "R%d", input.data1);
		sprintf(output.arg2, "$%d", (input.data2 << 8) + input.data3);
		return output;
	}
	if (input.opcode == 0x05) {
		strcpy(output.inst, "LD");
		sprintf(output.arg1, "$%d", (input.data1 << 8) + input.data2);
		sprintf(output.arg2, "R%d", input.data3);
		return output;
	}
	if (input.opcode == 0x06) {
		strcpy(output.inst, "ADD");
		sprintf(output.arg1, "R%d", input.data1);
		sprintf(output.arg2, "R%d", input.data2);
		return output;
	}
	if (input.opcode == 0x07) {
		strcpy(output.inst, "SUB");
		sprintf(output.arg1, "R%d", input.data1);
		sprintf(output.arg2, "R%d", input.data2);
		return output;
	}
	if (input.opcode == 0x08) {
		strcpy(output.inst, "MUL");
		sprintf(output.arg1, "R%d", input.data1);
		sprintf(output.arg2, "R%d", input.data2);
		return output;
	}
	if (input.opcode == 0x09) {
		strcpy(output.inst, "DIV");
		sprintf(output.arg1, "R%d", input.data1);
		sprintf(output.arg2, "R%d", input.data2);
		return output;
	}
	if (input.opcode == 0x0A) {
		strcpy(output.inst, "PUSH");
		sprintf(output.arg1, "R%d", input.data1);
		strcpy(output.arg2, "");
		return output;
	}
	if (input.opcode == 0x0B) {
		strcpy(output.inst, "POP");
		sprintf(output.arg1, "R%d", input.data1);
		strcpy(output.arg2, "");
		return output;
	}
	// TODO
	//if (input.opcode == 0x0C) {
	//}
	//if (input.opcode == 0x0D) {
	//}
	//if (input.opcode == 0x0E) {
	//}
	//if (input.opcode == 0x0F) {
	//}
	if (input.opcode == 0x10) {
		strcpy(output.inst, "RET");		
		strcpy(output.arg1, "");
		strcpy(output.arg2, "");
		return output;
	}
	if (input.opcode == 0x11) {
		strcpy(output.inst, "CMP");
		sprintf(output.arg1, "R%d", input.data1);
		sprintf(output.arg2, "R%d", input.data2);
		return output;
	}
	if (input.opcode == 0x12) {
		strcpy(output.inst, "CLF");		
		strcpy(output.arg1, "");
		strcpy(output.arg2, "");
		return output;
	}
	if (input.opcode == 0x13) {
		strcpy(output.inst, "AND");
		sprintf(output.arg1, "R%d", input.data1);
		sprintf(output.arg2, "R%d", input.data2);
		return output;
	}
	if (input.opcode == 0x14) {
		strcpy(output.inst, "OR");
		sprintf(output.arg1, "R%d", input.data1);
		sprintf(output.arg2, "R%d", input.data2);
		return output;
	}
	if (input.opcode == 0x15) {
		strcpy(output.inst, "NOT");
		sprintf(output.arg1, "R%d", input.data1);
		strcpy(output.arg2, "");
		return output;
	}
	if (input.opcode == 0x16) {
		strcpy(output.inst, "XOR");
		sprintf(output.arg1, "R%d", input.data1);
		sprintf(output.arg2, "R%d", input.data2);
		return output;
	}
	if (input.opcode == 0x17) {
		strcpy(output.inst, "LSHIFT");
		sprintf(output.arg1, "R%d", input.data1);
		sprintf(output.arg1, "%d", (input.data1 << 8) + input.data2);
		return output;
	}
	if (input.opcode == 0x18) {
		strcpy(output.inst, "RSHIFT");
		sprintf(output.arg1, "R%d", input.data1);
		sprintf(output.arg1, "%d", (input.data1 << 8) + input.data2);
		return output;
	}
	if (input.opcode == 0x19) {
		strcpy(output.inst, "INC");
		sprintf(output.arg1, "R%d", input.data1);
		strcpy(output.arg2, "");
		return output;
	}
	if (input.opcode == 0x20) {
		strcpy(output.inst, "DEC");
		sprintf(output.arg1, "R%d", input.data1);
		strcpy(output.arg2, "");
		return output;
	}
}

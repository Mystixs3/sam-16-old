#include <stdio.h>	// IO
#include <stdint.h>	// uint8_t
#include <string.h>	// strcpy(), strcmp()

#include "libasm.h"

int main(int argc, char const *argv[])
{
	char infilePath[50];
	char outfilePath[50] = "out.asm";

	// Command line arguments
	if (argc == 1) {
		printf("Not enough arguments given\n");
		return 0;
	}
	if (argc > 1) {
		strcpy(infilePath, argv[1]);
	}
	if (argc > 2) {
		strcpy(outfilePath, argv[2]);
	}

	// Open the input file
	FILE *infile;
	infile = fopen(infilePath, "rb");
	if (infile == NULL) { printf("Couldn't open %s\n", infilePath); return 0; }

	// Open the output file
	FILE *outfile;
	outfile = fopen(outfilePath, "w");
	if (outfile == NULL) { printf("Couldn't open %s\n", outfilePath); return 0; }

	uint8_t buff[4];
	Instruction input;
	Mnemonic output;

	// Main loop
	for (;;) { 
		//Read a line from the file
		if (fread(&buff, 1, 4, infile) != 4) {
			printf("Finished disassembling %s to %s\n", infilePath, outfilePath);
			fclose(infile);
			fclose(outfile);
			return 0;
		}

		input.opcode = buff[0];
		input.data1 = buff[1];
		input.data2 = buff[2];
		input.data3 = buff[3];

		output = disassemble(input);
		fprintf(outfile, "\n%s", output.inst);

		// Only print out arg1 or arg2 if needed
		if (strcmp(output.arg1, "")) {
			fprintf(outfile, " %s", output.arg1);
		}
		if (strcmp(output.arg2, "")) {
			fprintf(outfile, " %s", output.arg2);
		}
	}
}

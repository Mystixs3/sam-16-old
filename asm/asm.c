#include <stdio.h>	// IO
#include <string.h>	// strcpy(), strcmp()

#include "libasm.h"

int main(int argc, char const *argv[])
{
	char infilePath[50];
	char outfilePath[50] = "out";

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
	infile = fopen(infilePath, "r");
	if (infile == NULL) { printf("Couldn't open %s", infilePath); return 0; }

	// Open the output file
	FILE *outfile;
	outfile = fopen(outfilePath, "wb");
	if (outfile == NULL) { printf("Couldn't open %s", outfilePath); return 0; }

	int i;
	Mnemonic input;
	Instruction output;
	char buff[50];

	// Main loop
	for (;;) {
		// Clear the inputs
		strcpy(&input.inst[i], "");
		strcpy(&input.arg1[i], "");
		strcpy(&input.arg2[i], "");

		// Read a line from the input file, if its the end of the file end the program
		if (!fgets(buff, 50, infile)) {
			printf("Finished assembling %s to %s\n", infilePath, outfilePath);
			fclose(infile);
			fclose(outfile);
			return 0;
		}

		// Ignore comments and blank lines
		if (buff[0] != ';' && buff[0] != '\n') {
				sscanf(buff, "%s %s %s", input.inst, input.arg1, input.arg2);
				output = assemble(input);
				fwrite(&output, 1, 4, outfile);
		}
	}
}
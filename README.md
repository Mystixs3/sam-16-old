# sam-16

My homemade 16 bit CPU ISA with its own assembly language, assembler/disassembler and emulator.

## Compiling

Just run `make -j3` (As long as you have at least 3 threads on your device)

## Assembler

Use `./bin/asm <input file> <output file (optional)>`
By default the output file is `./out`

## Disassembler

Use `./bin/disasm <input file> <output file (optional)>`
By default the output file is `./out.asm`

## Emulator

Use `./bin/emu <input file>`
Then use ENTER to step the emulator
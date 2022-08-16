CC = gcc
CCFLAGS = -O2

.PHONY: all asm disasm emu libasm clean

all: asm disasm emu

asm: binDir
	$(CC) $(CCFLAGS) -o bin/asm asm/libasm.c asm/asm.c

disasm: binDir
	$(CC) $(CCFLAGS) -o bin/disasm asm/libasm.c asm/disasm.c

emu: binDir
	$(CC) $(CCFLAGS) -o bin/emu asm/libasm.c emu/emu.c

libasm: binDir
	$(CC) $(CCFLAGS) -c -o bin/libasm.o asm/libasm.c

binDir:
	mkdir -p bin

clean:
	rm -r -f bin/ test.asm out
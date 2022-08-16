CC = gcc
CCFLAGS = -O2

.PHONY: all asm disasm emu libasm clean

all: asm disasm emu

asm:
	mkdir -p bin
	$(CC) $(CCFLAGS) -o bin/asm asm/libasm.c asm/asm.c 

disasm:
	mkdir -p bin
	$(CC) $(CCFLAGS) -o bin/disasm asm/libasm.c asm/disasm.c 

emu:
	mkdir -p bin
	$(CC) $(CCFLAGS) -o bin/emu asm/libasm.c emu/emu.c 

libasm: 
	mkdir -p bin
	$(CC) $(CCFLAGS) -c -o bin/libasm.o asm/libasm.c

clean:
	rm -r -f bin/ test.asm out
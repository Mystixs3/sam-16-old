CC = gcc
CCFLAGS = -O2

.PHONY: all asm disasm libasm clean

all: asm disasm

asm:
	mkdir -p bin
	$(CC) $(CCFLAGS) -o bin/asm asm/libasm.c asm/asm.c 

disasm:
	mkdir -p bin
	$(CC) $(CCFLAGS) -o bin/disasm asm/libasm.c asm/disasm.c 

libasm: 
	mkdir -p bin
	$(CC) $(CCFLAGS) -c -o bin/libasm.o asm/libasm.c

clean:
	rm -r -f bin/ test.asm out
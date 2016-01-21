CC=i686-pc-linux-gnu-gcc

all: mine.bin
run: all
	qemu-system-i386 -kernel mine.bin
debug: all
	qemu-system-i386 -kernel mine.bin -gdb tcp::1234 -S &
	sleep 1 # gdb要等qemu就绪
	gdb
clean:
	rm -rf isodir
	rm -f *.o mine.bin frogimine.iso
.PHONY: all run clean
boot.o: boot.asm
	nasm -felf32 boot.asm -o boot.o -ggdb
kernel.o: kernel.c
	${CC} -m32 -g -c kernel.c -o kernel.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
mine.bin: boot.o kernel.o
	${CC} -m32 -g -T linker.ld -o mine.bin -ffreestanding -O2 -nostdlib $^ -lgcc


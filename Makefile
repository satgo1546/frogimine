all: frogimine.iso
run: all
	qemu-system-i386 -cdrom frogimine.iso
.PHONY: all run
boot.o: boot.asm
	nasm -felf32 boot.asm -o boot.o
kernel.o: kernel.c
	i686-elf-gcc -c kernel.c -o kernel.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
mine.bin: boot.o kernel.o
	i686-elf-gcc -T linker.ld -o mine.bin -ffreestanding -O2 -nostdlib boot.o kernel.o -lgcc
frogimine.iso: mine.bin
	mkdir -p isodir/boot/grub
	cp mine.bin isodir/boot/
	cp grub.cfg isodir/boot/grub/
	grub-mkrescue -o frogimine.iso isodir

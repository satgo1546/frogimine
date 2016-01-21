all: frogimine.iso
run: all
	qemu-system-i386 -cdrom frogimine.iso
clean:
	rm -rf isodir
	rm -f *.o mine.bin frogimine.iso
.PHONY: all run clean
boot.o: boot.asm
	nasm -felf32 boot.asm -o boot.o
kernel.o: kernel.c
	i686-elf-gcc -c kernel.c -o kernel.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
mine.bin: boot.o kernel.o
	i686-elf-gcc -T linker.ld -o mine.bin -ffreestanding -O2 -nostdlib $^ -lgcc
frogimine.iso: mine.bin grub.cfg
	mkdir -p isodir/boot/grub
	cp mine.bin isodir/boot/
	cp grub.cfg isodir/boot/grub/
	grub-mkrescue --fonts="" --locales="" --themes="" \
		--compress=no --output=frogimine.iso isodir

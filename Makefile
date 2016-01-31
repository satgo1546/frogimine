#==============================================================================
# ■ Makefile
#==============================================================================

SOURCES = $(shell find src | grep --invert-match "/generated|^src$|/\\.")

all:
	mkdir -p src/generated
	awk -f src/colors-cpp.awk src/indexed-colors.csv > src/generated/colors-cpp.txt
	awk -f src/colors-nasm.awk src/indexed-colors.csv > src/generated/colors-nasm.txt
	clang -c everything.cpp -o everything.cpp.o -m32 -O2 -std=c++11 -Wall -ggdb -nostdinc -fno-builtin -fno-stack-protector
	nasm -f elf32 everything.asm -o everything.asm.o -l everything.asm.lst
	ld -T src/linker.lds everything.asm.o everything.cpp.o -o mine.bin -melf_i386 -O2 -nostdlib
	mkdir -p isodir/boot/grub
	cp mine.bin isodir/boot/
	cp src/grub.cfg isodir/boot/grub/
	grub-mkrescue --directory=/usr/lib/grub/i386-pc --fonts="" --locales="" --themes="" --compress=no --output=frogimine.iso isodir -- -quiet
run: all
	qemu-system-i386 -cdrom frogimine.iso
debug: all
	qemu-system-i386 -cdrom frogimine.iso -S -gdb tcp::23333 &
	sleep 1
	gdb -tui -x src/gdbinit
clean:
	rm -rf isodir src/generated
	rm -f *.o *.lst 
	rm -f mine.bin frogimine.iso
.PHONY: all run debug clean

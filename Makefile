#  Copyright 2016 Frog Chen
#
#  Licensed under the Apache License, Version 2.0 (the "License");
#  you may not use this file except in compliance with the License.
#  You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
#  Unless required by applicable law or agreed to in writing, software
#  distributed under the License is distributed on an "AS IS" BASIS,
#  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
#  See the License for the specific language governing permissions and
#  limitations under the License.
#==============================================================================
# ■ Makefile
#==============================================================================

SOURCES = $(shell find src | grep --invert-match "/generated|^src$|/\\.")
SRC_OUT = src/generated

all:
	mkdir -p $(SRC_OUT)
	awk -v output=cpp -f src/colors--.awk src/indexed-colors.csv > $(SRC_OUT)/colors-cpp.txt
	awk -v output=nasm -f src/colors--.awk src/indexed-colors.csv > $(SRC_OUT)/colors-nasm.txt
	awk -f src/font-data--cpp.awk src/default-font-data.txt > $(SRC_OUT)/default-font-data.txt
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

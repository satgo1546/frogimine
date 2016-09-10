#==============================================================================
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
#------------------------------------------------------------------------------
#   make真是太神奇了，吓得我都不敢用它了。
#==============================================================================

#------------------------------------------------------------------------------
# ● 定义变量
#------------------------------------------------------------------------------
CC = clang
CXX = clang++
AS = nasm
LD = ld
CFLAGS = \
	-m32 -O2 -std=gnu++11 -Wall -Wextra -ggdb \
	-nostdinc -fno-builtin -fno-stack-protector
ASFLAGS = -f elf32 -g -F stabs
LDFLAGS = -T scripts/linker.lds -melf_i386 -no-builtin -nostdlib -O2
GRUB_MKRESCUE_FLAGS = \
	--directory=/usr/lib/grub/i386-pc \
	--fonts="" --locales="" --themes="" --compress=no

QEMU_COMMAND = qemu-system-i386 -cdrom frogimine.iso -display sdl

SOURCES = $(shell find src | grep --invert-match "/generated|^src$|/\\.")
SRC_OUT_DIR = src/generated
ISO_DIR = /tmp/iso_dir

#------------------------------------------------------------------------------
# ● 构建目标
#------------------------------------------------------------------------------
all: frogimine.iso
run: all
	$(QEMU_COMMAND)
debug: all
	$(QEMU_COMMAND) -S -gdb tcp::23333 &
	sleep .5
	gdb -tui -x scripts/gdbinit
clean:
	$(RM) -r $(ISO_DIR) $(SRC_OUT_DIR)
	$(RM) *.o *.lst
	$(RM) mine.bin frogimine.iso

$(SRC_OUT_DIR)/colors-cpp.txt: src/indexed-colors.csv
	mkdir -p $(SRC_OUT_DIR)
	awk -v output=cpp -f src/colors--.awk $< > $@
$(SRC_OUT_DIR)/colors-nasm.txt: src/indexed-colors.csv
	mkdir -p $(SRC_OUT_DIR)
	awk -v output=nasm -f src/colors--.awk $< > $@
$(SRC_OUT_DIR)/default-font-data.txt: src/default-font-data.txt
	mkdir -p $(SRC_OUT_DIR)
	awk -f src/font-data--cpp.awk $< > $@
src-out: $(SRC_OUT_DIR)/colors-cpp.txt $(SRC_OUT_DIR)/colors-nasm.txt $(SRC_OUT_DIR)/default-font-data.txt

compile: src-out
	$(CXX) -c everything.cpp -o everything.cpp.o $(CFLAGS)
	$(AS) $(ASFLAGS) everything.asm -o everything.asm.o
	$(LD) $(LDFLAGS) everything.asm.o everything.cpp.o -o mine.bin
frogimine.iso: compile
	mkdir -p $(ISO_DIR)/boot/grub
	cp mine.bin $(ISO_DIR)/boot/
	cp src/grub.cfg $(ISO_DIR)/boot/grub/
	grub-mkrescue $(GRUB_MKRESCUE_FLAGS) --output=frogimine.iso $(ISO_DIR)
listing: src-out
	$(AS) $(ASFLAGS) everything.asm -l everything.asm.lst
	$(CXX) -E everything.cpp -o everything.cpp.lst $(CFLAGS)
.PHONY: all run debug clean src-out compile listing

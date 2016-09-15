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
#   《小心翼翼地编写Makefile》
#==============================================================================

#------------------------------------------------------------------------------
# ● 定义变量
#------------------------------------------------------------------------------
CC = clang
CXX = clang++
AS = nasm
LD = ld
CFLAGS = \
	-m32 -O2 -std=gnu++11 -Wall -Wextra -g -Isrc \
	-nostdinc -fno-builtin -fno-stack-protector
ASFLAGS = -f elf32 -g
LDFLAGS = -T scripts/linker.lds -melf_i386 -no-builtin -nostdlib -O2
GRUB_MKRESCUE_FLAGS = \
	--directory=/usr/lib/grub/i386-pc \
	--fonts="" --locales="" --themes="" --compress=no

QEMU_COMMAND = qemu-system-i386 -kernel $(MINE_BIN) -display sdl

SOURCES = $(shell find src -name "*.cpp" -or -name "*.asm" | \
	grep --invert-match "/generated")
ISO_DIR = /tmp/iso_dir
MINE_BIN = mine.bin
MINE_ISO = frogimine.iso

#------------------------------------------------------------------------------
# ● 构建目标
#------------------------------------------------------------------------------
all: $(MINE_BIN)
run: all
	$(QEMU_COMMAND)
debug: all
	$(QEMU_COMMAND) -S -gdb tcp::23333 &
	sleep .5
	gdb -x scripts/gdbinit
clean:
	$(RM) -r $(ISO_DIR) src/generated
	$(RM) *.o *.lst
	$(RM) $(MINE_BIN) $(MINE_ISO)

src/generated: data scripts
	mkdir -p src/generated
	awk -v output=cpp -f scripts/colors__.awk data/indexed_colors.csv > src/generated/colors_cpp.txt
	awk -v output=nasm -f scripts/colors__.awk data/indexed_colors.csv > src/generated/colors_nasm.txt
	awk -f scripts/font_data__cpp.awk data/default_font_data.txt > src/generated/default_font_data.txt

$(MINE_BIN): src/generated $(SOURCES)
	$(CXX) -c everything.cpp -o everything.cpp.o $(CFLAGS)
	$(AS) $(ASFLAGS) everything.asm -o everything.asm.o
	$(LD) $(LDFLAGS) everything.asm.o everything.cpp.o -o $(MINE_BIN)
$(MINE_ISO): $(MINE_BIN)
	mkdir -p $(ISO_DIR)/boot/grub
	cp $(MINE_BIN) $(ISO_DIR)/boot/
	cp src/grub.cfg $(ISO_DIR)/boot/grub/
	grub-mkrescue $(GRUB_MKRESCUE_FLAGS) --output=$(MINE_ISO) $(ISO_DIR)
listing: src/generated
	$(AS) $(ASFLAGS) everything.asm -l everything.asm.lst
	$(CXX) -E everything.cpp -o everything.cpp.lst $(CFLAGS)

.PHONY: all run debug clean listing

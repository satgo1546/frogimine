#==============================================================================
# ■ Makefile
#==============================================================================

#----------------------------------------------------------------------------
# ● 定义变量
#----------------------------------------------------------------------------
ARCH = i686

CC = clang++
LD = ld
ASM = nasm

CC_FLAGS = -m32 -O2 -Wall -ggdb -nostdinc -fno-builtin -fno-stack-protector
LD_FLAGS = -melf_i386 -O2 -nostdlib
ASM_FLAGS = -f elf32

GDB_PORT = 23333
FN_BIN = mine.bin
FN_ISO = frogimine.iso
FN_GDBINIT = gdbinit

#----------------------------------------------------------------------------
# ● 一般目标
#----------------------------------------------------------------------------
all: $(FN_ISO)
run: all
	qemu-system-i386 -cdrom $(FN_ISO)
debug: all $(FN_GDBINIT)
	qemu-system-i386 -kernel $(FN_BIN) -S -gdb tcp::$(GDB_PORT) &
	sleep 1
	gdb -tui -x $(FN_GDBINIT)
clean:
	rm -rf isodir
	rm -f *.o $(FN_BIN) $(FN_ISO) $(FN_GDBINIT)
.PHONY: all run debug clean

boot.o: boot.asm
	$(ASM) $(ASM_FLAGS) $< -o $@ -l $(basename $@).lst
kernel.o: kernel.cpp core/util.cpp core/terminal.cpp
	$(CC) -c $< -o $@ $(CC_FLAGS)
$(FN_BIN): linker.ld boot.o kernel.o
	$(LD) -T $^ -o $@ $(LD_FLAGS)
$(FN_ISO): $(FN_BIN) grub.cfg
	mkdir -p isodir/boot/grub
	cp $(FN_BIN) isodir/boot/
	cp grub.cfg isodir/boot/grub/
	grub-mkrescue --fonts="" --locales="" --themes="" \
		--compress=no --output=$(FN_ISO) isodir
$(FN_GDBINIT): Makefile
	echo "file $(FN_BIN)" > $@
	echo "target remote :$(GDB_PORT)" >> $@
	echo "break kernel_main" >> $@
	echo "continue" >> $@

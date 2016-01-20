; 本段参照Multiboot规范中“OS image format”一段。
; https://www.gnu.org/software/grub/manual/multiboot/multiboot.html#OS-image-format
FLAGS equ 0b111 ; 对齐页面 + 提供memory map + 指定图像模式
MULTIBOOT_MAGIC equ 0x1badb002 ; 魔法，参照Multiboot规范
GRAPHICS_MODE equ 0 ; 线性图像模式（linear graphics mode）
GRAPHICS_WIDTH equ 320 ; 分辨率（横向）
GRAPHICS_HEIGHT equ 200 ; 分辨率（纵向）
GRAPHICS_DEPTH equ 8 ; 色深
section .multiboot
align 4
	dd MULTIBOOT_MAGIC
	dd FLAGS
	dd -(MULTIBOOT_MAGIC + FLAGS)
	resb 5 << 2
	dd GRAPHICS_MODE
	dd GRAPHICS_WIDTH
	dd GRAPHICS_HEIGHT
	dd GRAPHICS_DEPTH

; Currently the stack pointer register (esp) points at anything and using it may
; cause massive harm. Instead, we'll provide our own stack. We will allocate
; room for a small temporary stack by creating a symbol at the bottom of it,
; then allocating 16384 bytes for it, and finally creating a symbol at the top.
section .bootstrap_stack, nobits
align 4
stack_bottom:
resb 16384
stack_top:

; The linker script specifies _start as the entry point to the kernel and the
; bootloader will jump to this position once the kernel has been loaded. It
; doesn't make sense to return from this function as the bootloader is gone.
section .text
global _start
_start:
	; Welcome to kernel mode! We now have sufficient code for the bootloader to
	; load and run our operating system. It doesn't do anything interesting yet.
	; Perhaps we would like to call printf("Hello, World\n"). You should now
	; realize one of the profound truths about kernel mode: There is nothing
	; there unless you provide it yourself. There is no printf function. There
	; is no <stdio.h> header. If you want a function, you will have to code it
	; yourself. And that is one of the best things about kernel development:
	; you get to make the entire system yourself. You have absolute and complete
	; power over the machine, there are no security restrictions, no safe
	; guards, no debugging mechanisms, there is nothing but what you build.

	; By now, you are perhaps tired of assembly language. You realize some
	; things simply cannot be done in C, such as making the multiboot header in
	; the right section and setting up the stack. However, you would like to
	; write the operating system in a higher level language, such as C or C++.
	; To that end, the next task is preparing the processor for execution of
	; such code. C doesn't expect much at this point and we only need to set up
	; a stack. Note that the processor is not fully initialized yet and stuff
	; such as floating point instructions are not available yet.

	; 创建自己的堆栈
	mov esp, stack_top

	; 调用系统内核的主程序
	extern kernel_main
	call kernel_main
	;mov dword edx, [ebx + 80]
	;mov dword [0xb8000], eax
	;mov dword [0xb80a0], edx

	; 当内核主程序返回后，就让电脑进入死循环
	cli ; 禁用中断
.loop:
	; 等待到下一次中断来临
	hlt
	jmp .loop

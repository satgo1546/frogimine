;==============================================================================
; ■ start.asm
;------------------------------------------------------------------------------
;   系统内核的入口点。
;==============================================================================

; 分配堆栈所使用的空间
section .bootstrap_stack, nobits
align 4
stack_bottom:
resb 16384
stack_top:

; 链接脚本指定了_start作为系统内核的入口点，所以引导程序在内核读完后会跳到这里
; 执行。此函数无需返回，因为引导程序没了。
section .text
global _start
_start:
	; 创建自己的堆栈
	mov esp, stack_top

	; 判断是否为Multiboot引导，并传入参数
	cmp eax, 0x2badb002
	jne not_multiboot
	push dword ebx
	jmp multiboot_end
not_multiboot:
	push dword 0xffffffff
multiboot_end:

	; 设置调色板
	; 参照：http://wiki.osdev.org/VGA_Hardware#Port_0x3C8
	pushfd
	cli
	mov dx, 0x03c8
	xor al, al
	out dx, al
	inc dx
	%macro color 3
		mov al, %1 >> 2
		out dx, al
		mov al, %2 >> 2
		out dx, al
		mov al, %3 >> 2
		out dx, al
	%endmacro
	; 调色板数据
	; 由于内部使用的是0~63数据范围，因此即使在这里指定得很精确也毫无作用。
	; 在这里用0~255的范围仅是为了方便处理而使用。
	; 0~15：HTML规定的标准16色、Windows cmd.exe默认颜色等。可参照：
	; https://www.w3.org/TR/REC-html40/types.html#idx-color
	%include "src/generated/colors-nasm.txt"
	%unmacro color 3
	popfd

	; 调用系统内核的主程序
	extern kernel_main
	call kernel_main

	; 当内核主程序返回后，就让电脑进入死循环
	; 禁用中断
	cli
.loop:
	; 等待到下一次中断来临
	hlt
	jmp .loop
[bits 32]

; Multiboot的头
; 参照Multiboot规范中“OS image format”一段：
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
	times 5 dd 0
	dd GRAPHICS_MODE
	dd GRAPHICS_WIDTH
	dd GRAPHICS_HEIGHT
	dd GRAPHICS_DEPTH

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
	; ▼ 欢迎来到内核模式！
	
	; 创建自己的堆栈
	mov esp, stack_top
	
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
	; 0~16：HTML规定的标准16色、Windows cmd.exe默认颜色等。可参照：
	; https://www.w3.org/TR/REC-html40/types.html#idx-color
	color 0, 0, 0
	color 0, 0, 128
	color 0, 128, 0
	color 0, 128, 128
	color 128, 0, 0
	color 128, 0, 128
	color 128, 128, 0
	color 192, 192, 192
	color 128, 128, 128
	color 0, 0, 255
	color 0, 255, 0
	color 0, 255, 255
	color 255, 0, 0
	color 255, 0, 255
	color 255, 255, 0
	color 255, 255, 255
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

;==============================================================================
;  Copyright 2016 Frog Chen
;
;  Licensed under the Apache License, Version 2.0 (the "License");
;  you may not use this file except in compliance with the License.
;  You may obtain a copy of the License at
;
;      http://www.apache.org/licenses/LICENSE-2.0
;
;  Unless required by applicable law or agreed to in writing, software
;  distributed under the License is distributed on an "AS IS" BASIS,
;  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
;  See the License for the specific language governing permissions and
;  limitations under the License.
;==============================================================================
; ■ start.asm
;------------------------------------------------------------------------------
;   系统内核的入口点。
;==============================================================================

;------------------------------------------------------------------------------
; ● Multiboot的头。参照Multiboot规范中“OS image format”一段：
;   https://www.gnu.org/software/grub/manual/multiboot/multiboot.html#OS-image-format
;------------------------------------------------------------------------------
MULTIBOOT_MAGIC equ 0x1badb002
; 对齐页面 + 提供内存图
; 不指定图像模式，也不指定载入地址
MULTIBOOT_FLAGS equ 0b00000011

; 单独的Multiboot区段
section .multiboot
align 4
	dd MULTIBOOT_MAGIC
	dd MULTIBOOT_FLAGS
	dd -(MULTIBOOT_MAGIC + MULTIBOOT_FLAGS)
	times 5 dd 0
	times 4 dd 0

;------------------------------------------------------------------------------
; ● 分配堆栈与启动系统
;------------------------------------------------------------------------------
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

	; 写一段不知道干什么用的文字
	mov esi, booting_message
	mov edi, 0xb8142
	mov ecx, 40
	cld
	rep movsb

	; 调用系统内核的主程序
	extern kernel_main
	call kernel_main

booting_message:
	db 'F', 0x0a, 'r', 0x0a, 'o', 0x0a, 'g', 0x0a
	db 'i', 0x0a, 'm', 0x0a, 'i', 0x0a, 'n', 0x0a
	db 'e', 0x0a, '?', 0x00, '-', 0x07, '?', 0x00
	db 'W', 0x02, 'e', 0x02, 'l', 0x02, 'c', 0x02
	db 'o', 0x02, 'm', 0x02, 'e', 0x02, '!', 0x02

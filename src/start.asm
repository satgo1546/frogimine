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

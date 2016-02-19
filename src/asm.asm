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
; ■ asm.asm
;------------------------------------------------------------------------------
;   asm.cpp和其它一些程序需要的、一定要用汇编写的函数。
;   附注：一定要写ret！总计被这个坑过1次。
;==============================================================================

;----------------------------------------------------------------------------
; ● STI + HLT
;----------------------------------------------------------------------------
global sti_hlt
sti_hlt:
	sti
	hlt
	ret

;----------------------------------------------------------------------------
; ● 设置GDTR寄存器
;----------------------------------------------------------------------------
global set_gdtr
set_gdtr:
	mov ax, [esp + 4]
	mov [esp + 6], ax
	lgdt [esp + 6]
	ret

;----------------------------------------------------------------------------
; ● 更新段寄存器
;----------------------------------------------------------------------------
global update_segment_registers
update_segment_registers:
	mov ax, 2 << 3
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov ss, ax
	jmp (1 << 3):cs_updater
cs_updater:
	ret

;----------------------------------------------------------------------------
; ● 设置IDTR寄存器
;----------------------------------------------------------------------------
global set_idtr
set_idtr:
	mov ax, [esp + 4]
	mov [esp + 6], ax
	lidt [esp + 6]
	ret

;----------------------------------------------------------------------------
; ● 设置调色板
;   参照：http://wiki.osdev.org/VGA_Hardware#Port_0x3C8
;----------------------------------------------------------------------------
global initialize_pattle
initialize_pattle:
	pushfd
	cli
	mov dx, 0x03c8
	xor al, al
	out dx, al
	inc dx
	%macro color 3.nolist
		mov al, %1 >> 2
		out dx, al
		%if %1 != %2
			mov al, %2 >> 2
		%endif
		out dx, al
		%if %2 != %3
			mov al, %3 >> 2
		%endif
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
	ret

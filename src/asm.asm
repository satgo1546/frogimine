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
;   这个文件能正确嵌入C++程序中已是一个奇迹……
;==============================================================================

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

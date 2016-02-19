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
; ■ interrupt.asm
;------------------------------------------------------------------------------
;   处理中断专用的汇编文件。
;==============================================================================

%macro make_int 1
	extern int%1
	global asm_int%1
	asm_int%1:
		push es
		push ds
		pushad
		mov eax, esp
		push eax
		mov ax, ss
		mov ds, ax
		mov es, ax
		call int%1
		pop eax
		popad
		pop ds
		pop es
		iretd
%endmacro

make_int 33
make_int 44

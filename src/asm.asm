;==============================================================================
; ■ asm.asm
;------------------------------------------------------------------------------
;   asm.cpp需要的、一定要用汇编写的函数。
;   这个文件能正确嵌入C++程序中已是一个奇迹……
;==============================================================================

;----------------------------------------------------------------------------
; ● NOP
;   再也找不到比这个函数更没用的函数了 :)
;----------------------------------------------------------------------------
global asm_nop
asm_nop:
	nop
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
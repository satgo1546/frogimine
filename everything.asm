;==============================================================================
; ■ everything.asm
;------------------------------------------------------------------------------
;   用%include把所有汇编代码塞到这里，免除不会链接的烦恼。
;==============================================================================

[bits 32]
%include "src/multiboot-head.asm"
%include "src/start.asm"
%include "src/asm.asm"

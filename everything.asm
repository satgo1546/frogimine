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
; ■ everything.asm
;------------------------------------------------------------------------------
;   用%include把所有汇编代码塞到这里，免除不会链接的烦恼。
;==============================================================================

[bits 32]
%include "src/multiboot-head.asm"
%include "src/start.asm"
%include "src/asm.asm"
%include "src/interrupt.asm"

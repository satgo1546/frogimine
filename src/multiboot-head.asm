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
; ■ multiboot-head.asm
;------------------------------------------------------------------------------
;   Multiboot的头。参照Multiboot规范中“OS image format”一段：
;   https://www.gnu.org/software/grub/manual/multiboot/multiboot.html#OS-image-format
;==============================================================================

FLAGS equ 0b00000111 ; 对齐页面 + 提供memory map + 指定图像模式
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

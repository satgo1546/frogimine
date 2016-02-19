/*===========================================================================*/
/* Copyright 2016 Frog Chen
/*
/* Licensed under the Apache License, Version 2.0 (the "License");
/* you may not use this file except in compliance with the License.
/* You may obtain a copy of the License at
/*
/*     http://www.apache.org/licenses/LICENSE-2.0
/*
/* Unless required by applicable law or agreed to in writing, software
/* distributed under the License is distributed on an "AS IS" BASIS,
/* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
/* See the License for the specific language governing permissions and
/* limitations under the License.
/*===========================================================================*/
/* ■ linker.lds
/*-----------------------------------------------------------------------------
/*   链接器脚本。话说这注释格式真够蛋疼的……
/*===========================================================================*/

ENTRY(_start)

SECTIONS {
	/* 从1MiB处开始放置区块，这里比较方便。 */
	. = 1M;
	PROVIDE(kernel_start__defined_by_linker_script = .);

	/* 首先把Multiboot头部扔进去。Multiboot规范要求这个头在系统的最初8192字节内，
	/* 而且是越早越好。在此之后是.text区块。 */
	.text BLOCK(4K) : ALIGN(4K) {
		*(.multiboot)
		*(.text)
	}

	/* 数据 */
	.data BLOCK(4K) : ALIGN(4K) {
		*(.data)
		*(.rodata)
	}

	/* 未初始化的可读写数据和栈 */
	.bss BLOCK(4K) : ALIGN(4K) {
		*(COMMON)
		*(.bss)
		*(.bootstrap_stack)
	}

	PROVIDE(kernel_end__defined_by_linker_script = .);
}

// Copyright 2016 Iceberg OS
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//=============================================================================
// ■ idt.h
//-----------------------------------------------------------------------------
//   i686基础驱动：IDT。
//=============================================================================

#ifndef INCLUDE_IDT_H
#define INCLUDE_IDT_H

#include "StdC++/std.h"
#include "Basic/io.h"

class IDT {
	private:
	//---------------------------------------------------------------------------
	// ● 中断描述符
	//---------------------------------------------------------------------------
	typedef struct idt_entry_t {
		uint16_t base_lo;        // 中断处理函数地址 15～0 位
		uint16_t sel;            // 目标代码段描述符选择子
		uint8_t  always0;        // 置 0 段
		uint8_t  flags;          // 一些标志，文档有解释
		uint16_t base_hi;        // 中断处理函数地址 31～16 位
	}__attribute__((packed)) idt_entry_t;
	//---------------------------------------------------------------------------
	// ● IDTR
	//---------------------------------------------------------------------------
	typedef struct idt_ptr_t {
		uint16_t limit; 	// 限长
		uint32_t base; 		// 基址
	} __attribute__((packed)) idt_ptr_t;
	//---------------------------------------------------------------------------
	// ● 寄存器类型
	//---------------------------------------------------------------------------
	typedef struct pt_regs_t {
		uint32_t ds;		// 用于保存用户的数据段描述符
		uint32_t edi; 		// 从 edi 到 eax 由 pusha 指令压入
		uint32_t esi; 
		uint32_t ebp;
		uint32_t esp;
		uint32_t ebx;
		uint32_t edx;
		uint32_t ecx;
		uint32_t eax;
		uint32_t int_no; 	// 中断号
		uint32_t err_code;  // 错误代码(有中断错误代码的中断会由CPU压入)
		uint32_t eip;		// 以下由处理器自动压入
		uint32_t cs; 		
		uint32_t eflags;
		uint32_t useresp;
		uint32_t ss;
	} pt_regs;
	//---------------------------------------------------------------------------
	// ● 中断描述符表
	//---------------------------------------------------------------------------
	idt_entry_t idt_entries[256];
	//---------------------------------------------------------------------------
	// ● IDTR
	//---------------------------------------------------------------------------
	idt_ptr_t idt_ptr;
	//---------------------------------------------------------------------------
	// ● 中断处理函数的指针
	//---------------------------------------------------------------------------
	typedef void (*interrupt_handler_t)(pt_regs *);
	//---------------------------------------------------------------------------
	// ● 中断处理函数的指针数组
	//---------------------------------------------------------------------------
	interrupt_handler_t interrupt_handlers[256] __attribute__((packed));;

	public:
	//---------------------------------------------------------------------------
	// ● IDT初始化
	//---------------------------------------------------------------------------
	IDT();
};

#endif

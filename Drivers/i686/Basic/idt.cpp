/* Copyright 2016 Iceberg OS

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/

//=============================================================================
// ■ idt.cpp
//-----------------------------------------------------------------------------
//   Driver > Basic > i686 > idt
//=============================================================================

#include "Basic/idt.h"

IDT::IDT() {
	IO io = IO();

	// 重新映射 IRQ 表
	// 两片级联的 Intel 8259A 芯片
	// 主片端口 0x20 0x21
	// 从片端口 0xA0 0xA1
	
	// 初始化主片、从片
	// 0001 0001
	io.out8(0x20, 0x11);
	io.out8(0xA0, 0x11);

	// 设置主片 IRQ 从 0x20(32) 号中断开始
	io.out8(0x21, 0x20);

	// 设置从片 IRQ 从 0x28(40) 号中断开始
	io.out8(0xA1, 0x28);
	
	// 设置主片 IR2 引脚连接从片
	io.out8(0x21, 0x04);

	// 告诉从片输出引脚和主片 IR2 号相连
	io.out8(0xA1, 0x02);
	
	// 设置主片和从片按照 8086 的方式工作
	io.out8(0x21, 0x01);
	io.out8(0xA1, 0x01);
	
	// 设置主从片允许中断
	io.out8(0x21, 0x0);
	io.out8(0xA1, 0x0);

	//fillchar((uint8_t*)interrupt_handlers, sizeof(interrupt_handlers_t), 0x00);
	fillchar((uint8_t*)idt_entries, sizeof(idt_entry_t), 0x00);
	
}

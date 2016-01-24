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
// ■ idt.cpp
//-----------------------------------------------------------------------------
//   i686基础驱动：IDT。
//=============================================================================

#include "Basic/idt.h"

//---------------------------------------------------------------------------
// ● 声明中断处理函数 0-19 属于 CPU 的异常中断
//---------------------------------------------------------------------------
// ISR:中断服务程序(interrupt service routine)
//---------------------------------------------------------------------------
void IDT::isr0() {}; 		// 0 #DE 除 0 异常 
void IDT::isr1() {}; 		// 1 #DB 调试异常 
void IDT::isr2() {}; 		// 2 NMI 
void IDT::isr3() {}; 		// 3 BP 断点异常 
void IDT::isr4() {}; 		// 4 #OF 溢出 
void IDT::isr5() {}; 		// 5 #BR 对数组的引用超出边界 
void IDT::isr6() {}; 		// 6 #UD 无效或未定义的操作码 
void IDT::isr7() {}; 		// 7 #NM 设备不可用(无数学协处理器) 
void IDT::isr8() {}; 		// 8 #DF 双重故障(有错误代码) 
void IDT::isr9() {}; 		// 9 协处理器跨段操作 
void IDT::isr10() {}; 		// 10 #TS 无效TSS(有错误代码) 
void IDT::isr11() {};; 		// 11 #NP 段不存在(有错误代码) 
void IDT::isr12() {};; 		// 12 #SS 栈错误(有错误代码) 
void IDT::isr13() {};; 		// 13 #GP 常规保护(有错误代码) 
void IDT::isr14() {};; 		// 14 #PF 页故障(有错误代码) 
void IDT::isr15() {};; 		// 15 CPU 保留 
void IDT::isr16() {};; 		// 16 #MF 浮点处理单元错误 
void IDT::isr17() {};; 		// 17 #AC 对齐检查 
void IDT::isr18() {};; 		// 18 #MC 机器检查 
void IDT::isr19() {};; 		// 19 #XM SIMD(单指令多数据)浮点异常
//---------------------------------------------------------------------------
// 20-31 Intel 保留
//---------------------------------------------------------------------------
void IDT::isr20() {};
void IDT::isr21() {};
void IDT::isr22() {};
void IDT::isr23() {};
void IDT::isr24() {};
void IDT::isr25() {};
void IDT::isr26() {};
void IDT::isr27() {};
void IDT::isr28() {};
void IDT::isr29() {};
void IDT::isr30() {};
void IDT::isr31() {};
//---------------------------------------------------------------------------
// 32～255 用户自定义异常
//---------------------------------------------------------------------------
void IDT::isr180() {};	// 180 系统中断（Syscall）
							// 不使用int80，int80用于兼容unix/linux syscall
//---------------------------------------------------------------------------
// ● i声明 IRQ 函数
//---------------------------------------------------------------------------
// IRQ:中断请求(Interrupt Request)
//---------------------------------------------------------------------------
void IDT::irq0() {};		// 电脑系统计时器
void IDT::irq1() {}; 		// 键盘
void IDT::irq2() {}; 		// 与 IRQ9 相接，MPU-401 MD 使用
void IDT::irq3() {}; 		// 串口设备
void IDT::irq4() {}; 		// 串口设备
void IDT::irq5() {}; 		// 建议声卡使用
void IDT::irq6() {}; 		// 软驱传输控制使用
void IDT::irq7() {}; 		// 打印机传输控制使用
void IDT::irq8() {}; 		// 即时时钟
void IDT::irq9() {}; 		// 与 IRQ2 相接，可设定给其他硬件
void IDT::irq10() {}; 		// 建议网卡使用
void IDT::irq11() {}; 		// 建议 AGP 显卡使用
void IDT::irq12() {}; 		// 接 PS/2 鼠标，也可设定给其他硬件
void IDT::irq13() {}; 		// 协处理器使用
void IDT::irq14() {}; 		// IDE0 传输控制使用
void IDT::irq15() {}; 		// IDE1 传输控制使用
	
//---------------------------------------------------------------------------
// ● IDT门设定  （flag | 0x60为设置用户态）
//---------------------------------------------------------------------------
void IDT::idt_set_gate(uint8_t num, uint32_t base, uint16_t sel, uint8_t flags)
{
	idt_entries[num].base_lo = base & 0xFFFF;
	idt_entries[num].base_hi = (base >> 16) & 0xFFFF;

	idt_entries[num].sel     = sel;
	idt_entries[num].always0 = 0;

	idt_entries[num].flags = flags;
}

//---------------------------------------------------------------------------
// ● IDT表设定
//---------------------------------------------------------------------------
void IDT::idt_set_gates()
{
	idt_set_gate( 0, (uint32_t)isr0,  0x08, 0x8E);
	idt_set_gate( 1, (uint32_t)isr1,  0x08, 0x8E);
	idt_set_gate( 2, (uint32_t)isr2,  0x08, 0x8E);
	idt_set_gate( 3, (uint32_t)isr3,  0x08, 0x8E);
	idt_set_gate( 4, (uint32_t)isr4,  0x08, 0x8E);
	idt_set_gate( 5, (uint32_t)isr5,  0x08, 0x8E);
	idt_set_gate( 6, (uint32_t)isr6,  0x08, 0x8E);
	idt_set_gate( 7, (uint32_t)isr7,  0x08, 0x8E);
	idt_set_gate( 8, (uint32_t)isr8,  0x08, 0x8E);
	idt_set_gate( 9, (uint32_t)isr9,  0x08, 0x8E);
	idt_set_gate(10, (uint32_t)isr10, 0x08, 0x8E);
	idt_set_gate(11, (uint32_t)isr11, 0x08, 0x8E);
	idt_set_gate(12, (uint32_t)isr12, 0x08, 0x8E);
	idt_set_gate(13, (uint32_t)isr13, 0x08, 0x8E);
	idt_set_gate(14, (uint32_t)isr14, 0x08, 0x8E);
	idt_set_gate(15, (uint32_t)isr15, 0x08, 0x8E);
	idt_set_gate(16, (uint32_t)isr16, 0x08, 0x8E);
	idt_set_gate(17, (uint32_t)isr17, 0x08, 0x8E);
	idt_set_gate(18, (uint32_t)isr18, 0x08, 0x8E);
	idt_set_gate(19, (uint32_t)isr19, 0x08, 0x8E);
	idt_set_gate(20, (uint32_t)isr20, 0x08, 0x8E);
	idt_set_gate(21, (uint32_t)isr21, 0x08, 0x8E);
	idt_set_gate(22, (uint32_t)isr22, 0x08, 0x8E);
	idt_set_gate(23, (uint32_t)isr23, 0x08, 0x8E);
	idt_set_gate(24, (uint32_t)isr24, 0x08, 0x8E);
	idt_set_gate(25, (uint32_t)isr25, 0x08, 0x8E);
	idt_set_gate(26, (uint32_t)isr26, 0x08, 0x8E);
	idt_set_gate(27, (uint32_t)isr27, 0x08, 0x8E);
	idt_set_gate(28, (uint32_t)isr28, 0x08, 0x8E);
	idt_set_gate(29, (uint32_t)isr29, 0x08, 0x8E);
	idt_set_gate(30, (uint32_t)isr30, 0x08, 0x8E);
	idt_set_gate(31, (uint32_t)isr31, 0x08, 0x8E);

	idt_set_gate(32, (uint32_t)irq0, 0x08, 0x8E);
	idt_set_gate(33, (uint32_t)irq1, 0x08, 0x8E);
	idt_set_gate(34, (uint32_t)irq2, 0x08, 0x8E);
	idt_set_gate(35, (uint32_t)irq3, 0x08, 0x8E);
	idt_set_gate(36, (uint32_t)irq4, 0x08, 0x8E);
	idt_set_gate(37, (uint32_t)irq5, 0x08, 0x8E);
	idt_set_gate(38, (uint32_t)irq6, 0x08, 0x8E);
	idt_set_gate(39, (uint32_t)irq7, 0x08, 0x8E);
	idt_set_gate(40, (uint32_t)irq8, 0x08, 0x8E);
	idt_set_gate(41, (uint32_t)irq9, 0x08, 0x8E);
	idt_set_gate(42, (uint32_t)irq10, 0x08, 0x8E);
	idt_set_gate(43, (uint32_t)irq11, 0x08, 0x8E);
	idt_set_gate(44, (uint32_t)irq12, 0x08, 0x8E);
	idt_set_gate(45, (uint32_t)irq13, 0x08, 0x8E);
	idt_set_gate(46, (uint32_t)irq14, 0x08, 0x8E);
	idt_set_gate(47, (uint32_t)irq15, 0x08, 0x8E);

	// 255 将来用于实现系统调用
	idt_set_gate(255, (uint32_t)isr180, 0x08, 0x8E);
}

//---------------------------------------------------------------------------
// ● IDT初始化
//---------------------------------------------------------------------------
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

	//fillchar((uint8_t*)interrupt_handlers, sizeof(interrupt_handler_t) * 256, 0x00);
	//fillchar((uint8_t*)idt_entries, sizeof(idt_entry_t) * 256, 0x00);
	
	idt_ptr.limit = sizeof(idt_entry_t) * 256 -1;
	idt_ptr.base = (uint32_t)&idt_entries;
	
	idt_set_gates();
	
	// 更新芯片中IDT表
	idt_update((uint32_t)&idt_ptr);
}

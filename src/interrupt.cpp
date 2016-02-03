// Copyright 2016 Frog Chen
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
// ■ interrupt.cpp
//-----------------------------------------------------------------------------
//   处理中断信号用。
//=============================================================================

namespace Interrupt {
	//-------------------------------------------------------------------------
	// ● 初始化PIC
	//-------------------------------------------------------------------------
	void initialize_pic() {
		// 设定中断前，先屏蔽所有中断
		//  PIC0&1↘       ✗✗✗✗✗✗✗✗
		ASM::out8(0x21, 0b11111111);
		ASM::out8(0xa1, 0b11111111);
		// 边沿触发模式
		ASM::out8(0x20, 0x11);
		ASM::out8(0xa0, 0x11);
		// IRQ 0~7  → INT 0x20~0x27
		// IRQ 8~15 → INT 0x28~0x2f
		ASM::out8(0x21, 0x20);
		ASM::out8(0xa1, 0x28);
		// PIC1 -- IRQ2
		ASM::out8(0x21, 1 << 2);
		ASM::out8(0xa1, 2);
		// 无缓冲区模式
		ASM::out8(0x21, 0x01);
		ASM::out8(0xa1, 0x01);
		//    PIC0↘  #2 PIC1 ✓ ↴
		ASM::out8(0x21, 0b11111011);
		//    PIC1↘       ✗✗✗✗✗✗✗✗
		ASM::out8(0xa1, 0b11111111);
	}

	//-------------------------------------------------------------------------
	// ● 包装后的中断函数们
	//-------------------------------------------------------------------------
	extern "C" void asm_int33();
	extern "C" void asm_int44();

	//-------------------------------------------------------------------------
	// ● 初始化中断
	//-------------------------------------------------------------------------
	void initialize_interrupt() {
		// 设置IDT中的值
		IDT::set(33, (type_address) asm_int33, 1 << 3, 0x8e);
		IDT::set(44, (type_address) asm_int44, 1 << 3, 0x8e);
		//           #1 INT 33 ←┐
		//    PIC0↘  #2 PIC1   ↰│
		ASM::out8(0x21, 0b11111001);
		//    PIC1↘  #4 INT 44
		ASM::out8(0xa1, 0b11101111);
	}

	//-------------------------------------------------------------------------
	// ● 初始化
	//-------------------------------------------------------------------------
	void initialize() {
		initialize_pic();
		initialize_interrupt();
	}
}

//---------------------------------------------------------------------------
// ● INT 0x21：PS/2键盘
//---------------------------------------------------------------------------
extern "C" void int33(uint32_t* esp) {
	ASM::out8(0x20, 64 + 33);
	Keyboard::queue.push(ASM::in8(0x60));
}

//---------------------------------------------------------------------------
// ● INT 0x2c：PS/2鼠标
//---------------------------------------------------------------------------
extern "C" void int44(uint32_t* esp) {
	ASM::out8(0xa0, 0x64);
	ASM::out8(0x20, 0x62);
	Mouse::queue.push(ASM::in8(0x60));
}

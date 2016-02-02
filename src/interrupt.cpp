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
	// ● 初始化中断
	//-------------------------------------------------------------------------
	void initialize_interrupt() {
		// 设置IDT中的值
		IDT::set(33, (type_address) ASM::asm_int33, 1 << 3, 0x8e);
		//           #1 INT 33 ←┐
		//    PIC0↘  #2 PIC1   ↰│
		ASM::out8(0x21, 0b11111101);
		ASM::out8(0xa1, 0b11111111);
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
	static unsigned int job = 0;
	job++;
	ASM::out8(0x20, 64 + 33);
	uint8_t data = ASM::in8(0x60);
	char buf[4];
	Graphics::fill_rect((struct rect) {
		.x = 0,
		.y = 128,
		.width = Graphics::width,
		.height = Graphics::default_font_height,
	}, Graphics::BLACK);
	FMString::long2charbuf(buf, job);
	Graphics::draw_text((struct pos) {0, 128}, buf, Graphics::WHITE);
	FMString::long2charbuf(buf, data);
	Graphics::draw_text((struct pos) {32, 128}, buf, Graphics::WHITE);
}

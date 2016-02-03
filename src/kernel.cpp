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
// ■ kernel.cpp
//-----------------------------------------------------------------------------
//   内核。不知道有什么用。
//=============================================================================

namespace Kernel {
	//-------------------------------------------------------------------------
	// ● 等待键盘响应
	//-------------------------------------------------------------------------
	inline void wait_keyboard() {
		while (ASM::in8(0x64) & 1 << 1);
	}
	//-------------------------------------------------------------------------
	// ● 初始化
	//-------------------------------------------------------------------------
	void initialize(type_address multiboot_info_address) {
		MultibootInfo::initialize(multiboot_info_address);
		GDT::initialize();
		IDT::initialize();
		Interrupt::initialize();
		ASM::sti();
		Terminal::width = 80;
		Terminal::height = 25;
		// 给可怜的只能用字符终端的用户一个系统成功启动的提示，然后就没有然后了
		Terminal::write_char(
			(struct pos) {4, 4},
			'%',
			(struct Terminal::char_color) {
				.fg = Terminal::AQUA,
				.bg = Terminal::NAVY,
			}
		);
		Graphics::width = 320;
		Graphics::height = 200;
		// 初始化键盘并启用鼠标
		wait_keyboard(); ASM::out8(0x64, 0x60);
		wait_keyboard(); ASM::out8(0x60, 0x47);
		wait_keyboard(); ASM::out8(0x64, 0xd4);
		wait_keyboard(); ASM::out8(0x60, 0xf4);
	}

	//-------------------------------------------------------------------------
	// ● 主程序
	//-------------------------------------------------------------------------
	void main() {
	}
}

//---------------------------------------------------------------------------
// ● 供外部调用的内核主程序
//---------------------------------------------------------------------------
extern "C" void kernel_main(type_address multiboot_info_address) {
	char buf[15];
	Kernel::initialize(multiboot_info_address);
	Kernel::main();
	for (;;) {
		ASM::cli();
		if (!keyboard_queue.is_empty()) {
			Graphics::fill_rect(0, 0, Graphics::width, Graphics::height, Graphics::BLACK);
			FMString::long2charbuf(buf, keyboard_queue.shift());
			Graphics::draw_text((struct pos) {0, 0}, buf, Graphics::WHITE);
		} else if (!mouse_queue.is_empty()) {
			Graphics::fill_rect(0, 0, Graphics::width, Graphics::height, Graphics::BLACK);
			FMString::long2charbuf(buf, mouse_queue.shift());
			Graphics::draw_text((struct pos) {0, 32}, buf, Graphics::WHITE);
		} else {
			ASM::sti_hlt();
		}
	}
}

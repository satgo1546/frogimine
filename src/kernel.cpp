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
		Keyboard::initialize();
		Mouse::initialize();
	}

	//-------------------------------------------------------------------------
	// ● 主程序
	//-------------------------------------------------------------------------
	void main() {
		Graphics::draw_text((struct pos) {0, 0}, MultibootInfo::mem_lower, Graphics::WHITE);
		Graphics::draw_text((struct pos) {100, 0}, MultibootInfo::mem_upper, Graphics::WHITE);
	}
}

//---------------------------------------------------------------------------
// ● 供外部调用的内核主程序
//---------------------------------------------------------------------------
extern "C" void kernel_main(type_address multiboot_info_address) {
	Kernel::initialize(multiboot_info_address);
	Kernel::main();
	for (;;) {
		ASM::cli();
		if (!Keyboard::queue.is_empty()) {
			Keyboard::process_data();
		} else if (!Mouse::queue.is_empty()) {
			Mouse::process_data();
		} else {
			ASM::sti_hlt();
		}
	}
}

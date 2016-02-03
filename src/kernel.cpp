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
//   这个文件是干什么的？www
//=============================================================================

//---------------------------------------------------------------------------
// ● 初始化
//---------------------------------------------------------------------------
void initialize(type_address multiboot_info_address) {
	MultibootInfo::initialize(multiboot_info_address);
	GDT::initialize();
	IDT::initialize();
	Interrupt::initialize();
	ASM::sti();
	Terminal::width = 80;
	Terminal::height = 25;
	// 给可怜的只能用字符终端的用户一个系统成功启动的提示，然后就没有然后了
	Terminal::write_char((struct pos) {4, 4}, '%', (struct Terminal::char_color) {
		.fg = Terminal::AQUA,
		.bg = Terminal::NAVY,
	});
	Graphics::width = 320;
	Graphics::height = 200;
}
//---------------------------------------------------------------------------
// ● 主程序
//   函数名字main是C/C++保留的。
//---------------------------------------------------------------------------
void m_a_i_n() {
	char buf[15];
	uint8_t a[6];
	FMQueue8 q(a, 6);
	q.push(2 * 2);
	if (q.is_empty()) Graphics::set_pixel((struct pos) {5, 5}, Graphics::WHITE);
	FMString::long2charbuf(buf, q.shift());
	Graphics::draw_text((struct pos) {0, 120}, buf, Graphics::WHITE);
	if (q.is_empty()) Graphics::set_pixel((struct pos) {10, 10}, Graphics::WHITE);
}

//---------------------------------------------------------------------------
// ● 内核主程序
//---------------------------------------------------------------------------
extern "C" void kernel_main(type_address multiboot_info_address) {
	initialize(multiboot_info_address);
	m_a_i_n();
	for (;;) ASM::hlt();
}

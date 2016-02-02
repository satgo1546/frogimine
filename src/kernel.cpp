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
// ● 主程序
//---------------------------------------------------------------------------
void initialize_main() {
	Terminal::width = 80;
	Terminal::height = 25;
	Terminal::write_char((struct pos) {4, 4}, '%', (struct Terminal::char_color) {
		.fg = Terminal::AQUA,
		.bg = Terminal::NAVY,
	});
	Graphics::width = 320;
	Graphics::height = 200;
	Graphics::fill_rect(16, 16, Graphics::width - 16 * 2,
		Graphics::height - 16 * 2, Graphics::GREEN);
	Graphics::draw_text((struct pos) {32, 32}, "Frogimine", Graphics::LIME);
	Graphics::set_pixel((struct pos) {64, 64}, Graphics::YELLOW);
	Graphics::draw_text((struct pos) {32, 0}, "Proudly booted by", Graphics::FUCHSIA);
	Graphics::draw_text((struct pos) {32, 12}, MultibootInfo::boot_loader_name, Graphics::FUCHSIA);
	char buf[15];
	FMString::long2charbuf(buf, 233);
	Graphics::draw_text((struct pos) {32, 24}, buf, Graphics::WHITE);
	Graphics::draw_text((struct pos) {32, 64}, MultibootInfo::cmdline, Graphics::WEB_CCC);
	return;
}

//---------------------------------------------------------------------------
// ● 内核主程序
//---------------------------------------------------------------------------
extern "C" void kernel_main(type_address multiboot_info_address) {
	MultibootInfo::initialize(multiboot_info_address);
	GDT::initialize();
	IDT::initialize();
	Interrupt::initialize();
	ASM::sti();
	initialize_main();
	for (;;) ASM::hlt();
}

//=============================================================================
// ■ kernel.cpp
//-----------------------------------------------------------------------------
//   这个文件是干什么的？www
//=============================================================================

#include "global.h"
#include "core/util.cpp"
#include "core/terminal.cpp"
#include "core/graphics.cpp"

//---------------------------------------------------------------------------
// ● Multiboot
//---------------------------------------------------------------------------
void initialize_multiboot(type_address address) {
	int a = read_memory32(address);
}

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
		Graphics::height - 16 * 2, Graphics::TEAL);
	Graphics::set_pixel((struct pos) {16, 16}, Graphics::LIME);
	return;
}

//---------------------------------------------------------------------------
// ● 内核主程序
//---------------------------------------------------------------------------
extern "C" void kernel_main(type_address multiboot_info_address) {
	initialize_multiboot(multiboot_info_address);
	initialize_main();
}

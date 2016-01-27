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
// ● 初始化
//---------------------------------------------------------------------------
void initialize() {
	Terminal::width = 80;
	Terminal::height = 25;
	Terminal::write_char((struct pos) {4, 4}, '%', (struct Terminal::char_color) {
		.fg = Terminal::AQUA,
		.bg = Terminal::NAVY,
	});
	Graphics::width = 320;
	Graphics::height = 200;
	Graphics::set_pixel((struct pos) {16, 16}, Graphics::LIME);
	return;
}

//---------------------------------------------------------------------------
// ● 主程序
//---------------------------------------------------------------------------
extern "C" void kernel_main() {
	initialize();
}

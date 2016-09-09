//=============================================================================
// ■ terminal.cpp
//-----------------------------------------------------------------------------
//   字符模式下的显卡驱动。
//=============================================================================

#include "../global.h"
#include "util.cpp"
#ifndef INCLUDE_TERMINAL_CPP
#define INCLUDE_TERMINAL_CPP

//---------------------------------------------------------------------------
// ● 定义类型
//---------------------------------------------------------------------------
enum terminal_color {
	TERMINAL_COLOR_BLACK = 0,
	TERMINAL_COLOR_NAVY = 1,
	TERMINAL_COLOR_GREEN = 2,
	TERMINAL_COLOR_TEAL = 3,
	TERMINAL_COLOR_MAROON = 4,
	TERMINAL_COLOR_PURPLE = 5,
	TERMINAL_COLOR_OLIVE = 6,
	TERMINAL_COLOR_SILVER = 7,
	TERMINAL_COLOR_GRAY = 8,
	TERMINAL_COLOR_BLUE = 9,
	TERMINAL_COLOR_LIME = 10,
	TERMINAL_COLOR_AQUA = 11,
	TERMINAL_COLOR_RED = 12,
	TERMINAL_COLOR_FUCHSIA = 13,
	TERMINAL_COLOR_YELLOW = 14,
	TERMINAL_COLOR_WHITE = 15,
};
struct terminal_char_color {
	enum terminal_color bg, fg;
};

//---------------------------------------------------------------------------
// ● 定义变量
//---------------------------------------------------------------------------
unsigned int terminal_width;
unsigned int terminal_height;
static int terminal_cursor_x;
static int terminal_cursor_y;

//---------------------------------------------------------------------------
// ● 计算显示位置的内存地址
//---------------------------------------------------------------------------
inline type_address terminal_memory_address(struct pos pos) {
	return 0xb8000 + (pos.x + pos.y * terminal_width) * 2;
}

//---------------------------------------------------------------------------
// ● 移动光标
//---------------------------------------------------------------------------
void terminal_set_pos(struct pos pos) {
	terminal_cursor_x = pos.x;
	terminal_cursor_y = pos.y;
	unsigned short pos_info = pos.x + pos.y * terminal_width;
	asm_out8(0x03d4, 14);
	asm_out8(0x03d5, pos_info >> 8);
	asm_out8(0x03d4, 15);
	asm_out8(0x03d5, pos_info & 0xff);
}

//---------------------------------------------------------------------------
// ● 写出一个字符
//   pos : 目标字符的位置
//   c : 字符
//   color : 字符的颜色
//---------------------------------------------------------------------------
void terminal_write_char(struct pos pos, char c,
struct terminal_char_color color) {
	type_address address = terminal_memory_address(pos);
	write_memory(address, c);
	unsigned char attribute = 1 << 7 | color.bg << 4 | color.fg;
	write_memory(address + 1, attribute);
}

#endif

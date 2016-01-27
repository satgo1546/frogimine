//=============================================================================
// ■ graphics.cpp
//-----------------------------------------------------------------------------
//   图形模式显卡驱动。
//=============================================================================

#include "../global.h"
#include "util.cpp"
#ifndef INCLUDE_GRAPHICS_CPP
#define INCLUDE_GRAPHICS_CPP

//---------------------------------------------------------------------------
// ● 定义类型
//---------------------------------------------------------------------------
enum indexed_color {
	INDEXED_COLOR_BLACK = 0,
	INDEXED_COLOR_NAVY = 1,
	INDEXED_COLOR_GREEN = 2,
	INDEXED_COLOR_TEAL = 3,
	INDEXED_COLOR_MAROON = 4,
	INDEXED_COLOR_PURPLE = 5,
	INDEXED_COLOR_OLIVE = 6,
	INDEXED_COLOR_SILVER = 7,
	INDEXED_COLOR_GRAY = 8,
	INDEXED_COLOR_BLUE = 9,
	INDEXED_COLOR_LIME = 10,
	INDEXED_COLOR_AQUA = 11,
	INDEXED_COLOR_RED = 12,
	INDEXED_COLOR_FUCHSIA = 13,
	INDEXED_COLOR_YELLOW = 14,
	INDEXED_COLOR_WHITE = 15,
};

//---------------------------------------------------------------------------
// ● 定义变量
//---------------------------------------------------------------------------
unsigned int graphics_width;
unsigned int graphics_height;

//---------------------------------------------------------------------------
// ● 计算显示位置的内存地址
//---------------------------------------------------------------------------
inline type_address graphics_memory_address(struct pos pos) {
	return 0xa0000 + pos.x + pos.y * graphics_width;
}

//---------------------------------------------------------------------------
// ● 设定像素的颜色
//---------------------------------------------------------------------------
void graphics_set_pixel(struct pos pos, enum indexed_color color) {
	write_memory(graphics_memory_address(pos), color);
}

#endif

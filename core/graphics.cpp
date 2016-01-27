//=============================================================================
// ■ graphics.cpp
//-----------------------------------------------------------------------------
//   图形模式显卡驱动。
//=============================================================================

#include "../global.h"
#include "util.cpp"
#ifndef INCLUDE_GRAPHICS_CPP
#define INCLUDE_GRAPHICS_CPP

namespace Graphics {
	//-------------------------------------------------------------------------
	// ● 定义类型
	//-------------------------------------------------------------------------
	enum indexed_color {
		BLACK = 0,
		NAVY = 1,
		GREEN = 2,
		TEAL = 3,
		MAROON = 4,
		PURPLE = 5,
		OLIVE = 6,
		SILVER = 7,
		GRAY = 8,
		BLUE = 9,
		LIME = 10,
		AQUA = 11,
		RED = 12,
		FUCHSIA = 13,
		YELLOW = 14,
		WHITE = 15,
	};

	//-------------------------------------------------------------------------
	// ● 定义变量
	//-------------------------------------------------------------------------
	unsigned int width;
	unsigned int height;

	//-------------------------------------------------------------------------
	// ● 计算显示位置的内存地址
	//-------------------------------------------------------------------------
	inline type_address memory_address(struct pos pos) {
		return 0xa0000 + pos.x + pos.y * width;
	}

	//-------------------------------------------------------------------------
	// ● 设定像素的颜色
	//-------------------------------------------------------------------------
	void set_pixel(struct pos pos, enum indexed_color color) {
		write_memory(memory_address(pos), color);
	}

	//-------------------------------------------------------------------------
	// ● 填充矩形
	//-------------------------------------------------------------------------
	void fill_rect(struct rect rect, enum indexed_color color) {
		int x, y;
		int end_x = rect.x + rect.width;
		int end_y = rect.y + rect.height;
		for (y = rect.y; y < end_y; y++) {
			for (x = rect.x; x < end_x; x++) {
				set_pixel((struct pos) {x, y}, color);
			}
		}
	}
}

#endif

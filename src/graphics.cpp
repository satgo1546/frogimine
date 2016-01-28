//=============================================================================
// ■ graphics.cpp
//-----------------------------------------------------------------------------
//   图形模式显卡驱动。
//=============================================================================

namespace Graphics {
	//-------------------------------------------------------------------------
	// ● 定义
	//-------------------------------------------------------------------------
	const uint8_t a[11] = {
		0b00000000,
		0b00000000,
		0b11111110,
		0b10000001,
		0b00000001,
		0b11111111,
		0b10000001,
		0b10000001,
		0b01111111,
		0b00000000,
		0b00000000,
	};

	enum indexed_color {
		#include "generated/colors-cpp.txt"
	};

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
		Memory::write8_at(memory_address(pos), color);
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
	void fill_rect(int x, int y, unsigned int width, unsigned int height,
	enum indexed_color color) {
		fill_rect((struct rect) {
			.x = x,
			.y = y,
			.width = width,
			.height = height,
		}, color);
	}

	//-------------------------------------------------------------------------
	// ● 绘制“A”
	//-------------------------------------------------------------------------
	void draw_a(struct pos pos, enum indexed_color color) {
		int i;
		for (i = 0; i < 11; i++) {
			if (a[i] & 1     ) { set_pixel((struct pos) {pos.x + 7, pos.y + i}, color); }
			if (a[i] & 1 << 1) { set_pixel((struct pos) {pos.x + 6, pos.y + i}, color); }
			if (a[i] & 1 << 2) { set_pixel((struct pos) {pos.x + 5, pos.y + i}, color); }
			if (a[i] & 1 << 3) { set_pixel((struct pos) {pos.x + 4, pos.y + i}, color); }
			if (a[i] & 1 << 4) { set_pixel((struct pos) {pos.x + 3, pos.y + i}, color); }
			if (a[i] & 1 << 5) { set_pixel((struct pos) {pos.x + 2, pos.y + i}, color); }
			if (a[i] & 1 << 6) { set_pixel((struct pos) {pos.x + 1, pos.y + i}, color); }
			if (a[i] & 1 << 7) { set_pixel((struct pos) {pos.x    , pos.y + i}, color); }
		}
	}
}

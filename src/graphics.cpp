//=============================================================================
// ■ graphics.cpp
//-----------------------------------------------------------------------------
//   图形模式显卡驱动。
//=============================================================================

namespace Graphics {
	//-------------------------------------------------------------------------
	// ● 定义
	//-------------------------------------------------------------------------
	#include "default-font.cpp"

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
	// ● 绘制字符
	//-------------------------------------------------------------------------
	void draw_char(char c, struct pos pos, enum indexed_color color) {
		int i;
		unsigned int index = c - 32;
		for (i = 0; i < 12; i++) {
			if (default_font[index][i] & 1     ) { set_pixel((struct pos) {pos.x + 7, pos.y + i}, color); }
			if (default_font[index][i] & 1 << 1) { set_pixel((struct pos) {pos.x + 6, pos.y + i}, color); }
			if (default_font[index][i] & 1 << 2) { set_pixel((struct pos) {pos.x + 5, pos.y + i}, color); }
			if (default_font[index][i] & 1 << 3) { set_pixel((struct pos) {pos.x + 4, pos.y + i}, color); }
			if (default_font[index][i] & 1 << 4) { set_pixel((struct pos) {pos.x + 3, pos.y + i}, color); }
			if (default_font[index][i] & 1 << 5) { set_pixel((struct pos) {pos.x + 2, pos.y + i}, color); }
			if (default_font[index][i] & 1 << 6) { set_pixel((struct pos) {pos.x + 1, pos.y + i}, color); }
			if (default_font[index][i] & 1 << 7) { set_pixel((struct pos) {pos.x    , pos.y + i}, color); }
		}
	}

	//-------------------------------------------------------------------------
	// ● 绘制“a”
	//-------------------------------------------------------------------------
	void draw_a(struct pos pos, enum indexed_color color) {
		draw_char('a', pos, color);
	}
}

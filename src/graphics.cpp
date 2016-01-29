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
	const type_address vram_base = 0xa0000;

	enum indexed_color {
		#include "generated/colors-cpp.txt"
	};

	unsigned int width;
	unsigned int height;

	//-------------------------------------------------------------------------
	// ● 计算显示位置的内存地址
	//-------------------------------------------------------------------------
	inline type_address memory_address(struct pos pos) {
		return vram_base + pos.x + pos.y * width;
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
	void draw_char(struct pos pos, char c, enum indexed_color color) {
		int i, y;
		uint8_t line;
		type_address address;
		unsigned int index = c - 32;
		for (i = 0; i < default_font_height; i++) {
			y = pos.y + i;
			line = default_font[index][i];
			address = memory_address((struct pos) {pos.x, y});
			if (line & 1 << 0) { Memory::write8_at(address + 7, color); }
			if (line & 1 << 1) { Memory::write8_at(address + 6, color); }
			if (line & 1 << 2) { Memory::write8_at(address + 5, color); }
			if (line & 1 << 3) { Memory::write8_at(address + 4, color); }
			if (line & 1 << 4) { Memory::write8_at(address + 3, color); }
			if (line & 1 << 5) { Memory::write8_at(address + 2, color); }
			if (line & 1 << 6) { Memory::write8_at(address + 1, color); }
			if (line & 1 << 7) { Memory::write8_at(address    , color); }
		}
	}

	//-------------------------------------------------------------------------
	// ● 绘制“a”
	//-------------------------------------------------------------------------
	void draw_a(struct pos pos, enum indexed_color color) {
		draw_char(pos, 'a', color);
	}
}

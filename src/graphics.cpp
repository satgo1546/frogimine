//=============================================================================
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
	enum indexed_color cursor_color = GRAY_DDD;

	//-------------------------------------------------------------------------
	// ● 初始化
	//-------------------------------------------------------------------------
	void initialize() {
		ASM::initialize_pattle();
	}

	//-------------------------------------------------------------------------
	// ● 填充整个屏幕
	//-------------------------------------------------------------------------
	void fill(enum indexed_color color) {
		type_address i;
		type_address end_i = vram_base + Screen::width * Screen::height;
		for (i = vram_base; i < end_i; i++) Memory::write8_at(i, color);
	}

	//-------------------------------------------------------------------------
	// ● 计算显示位置的内存地址
	//-------------------------------------------------------------------------
	inline type_address memory_address(struct pos pos) {
		return vram_base + pos.x + pos.y * Screen::width;
	}

	//-------------------------------------------------------------------------
	// ● 设定像素的颜色
	//-------------------------------------------------------------------------
	void set_pixel(struct pos pos, enum indexed_color color) {
		if (pos.x < 0 || pos.x >= Screen::width || pos.y < 0 || pos.y >= Screen::height) return;
		Memory::write8_at(memory_address(pos), color);
	}

	//-------------------------------------------------------------------------
	// ● 填充矩形
	//-------------------------------------------------------------------------
	void fill_rect(struct rect rect, enum indexed_color color) {
		int x, y;
		int end_x = rect.x + rect.width;
		if (end_x >= Screen::width) end_x = Screen::width;
		int end_y = rect.y + rect.height;
		if (end_y >= Screen::height) end_y = Screen::height;
		for (y = (rect.y < 0 ? 0 : rect.y); y < end_y; y++) {
			for (x = (rect.x < 0 ? 0 : rect.x); x < end_x; x++) {
				set_pixel((struct pos) {x, y}, color);
			}
		}
	}
	void fill_rect(int x, int y, int width, int height,
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
		int i, y; uint8_t line;
		type_address address;
		int index = c - 32;
		if (pos.x >= Screen::width || pos.y >= Screen::height || index <= 0 || c > '~') return;
		for (i = 0; i < default_font_height; i++) {
			y = pos.y + i;
			line = default_font[index][i];
			address = memory_address((struct pos) {pos.x, y});
			if (line & 1 << 0) Memory::write8_at(address + 7, color);
			if (line & 1 << 1) Memory::write8_at(address + 6, color);
			if (line & 1 << 2) Memory::write8_at(address + 5, color);
			if (line & 1 << 3) Memory::write8_at(address + 4, color);
			if (line & 1 << 4) Memory::write8_at(address + 3, color);
			if (line & 1 << 5) Memory::write8_at(address + 2, color);
			if (line & 1 << 6) Memory::write8_at(address + 1, color);
			if (line & 1 << 7) Memory::write8_at(address + 0, color);
		}
	}

	//-------------------------------------------------------------------------
	// ● 绘制文本
	//-------------------------------------------------------------------------
	void draw_text(struct pos pos, const char* str, enum indexed_color color) {
		int x = pos.x, y = pos.y;
		if (x >= Screen::width || y >= Screen::height) return;
		while (*str != '\0') {
			draw_char((struct pos) {x, y}, *str, color);
			x += default_font_width;
			str++;
		}
	}

	//-------------------------------------------------------------------------
	// ● 绘制数值
	//-------------------------------------------------------------------------
	void draw_text(struct pos pos, long value, enum indexed_color color) {
		char buf[12];
		FMString::long2charbuf(buf, value);
		draw_text(pos, buf, color);
	}

	//-------------------------------------------------------------------------
	// ● 绘制鼠标指针
	//-------------------------------------------------------------------------
	void draw_cursor(struct pos pos) {
		fill_rect((struct rect) {pos.x - 3, pos.y, 7, 1}, cursor_color);
		fill_rect((struct rect) {pos.x, pos.y - 3, 1, 7}, cursor_color);
	}

	//-------------------------------------------------------------------------
	// ● 重绘
	//-------------------------------------------------------------------------
	void redraw() {
		fill(GRAY);
		draw_cursor(Mouse::state.pos);
	}
}

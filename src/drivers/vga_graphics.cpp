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
// ■ vga_graphics.cpp
//-----------------------------------------------------------------------------
//   图形模式VGA显卡驱动。
//=============================================================================

namespace VGA { namespace Graphics {
	//-------------------------------------------------------------------------
	// ● 定义
	//-------------------------------------------------------------------------
	auto vram_base = (char* const) 0xa0000;
	//-------------------------------------------------------------------------
	// ● 计算显示位置的内存地址
	//-------------------------------------------------------------------------
	char* memory_address(struct pos pos) {
		return vram_base + pos.x + pos.y * ::Graphics::pixel_size.width;
	}
	//-------------------------------------------------------------------------
	// ● 设定像素的颜色
	//-------------------------------------------------------------------------
	void set_pixel(struct pos pos, enum indexed_color color) {
		if (pos.x < 0 || pos.x >= ::Graphics::pixel_size.width) return;
		if (pos.y < 0 || pos.y >= ::Graphics::pixel_size.height) return;
		*memory_address(pos) = color;
	}
	//-------------------------------------------------------------------------
	// ● 填充整个屏幕
	//-------------------------------------------------------------------------
	void fill(enum indexed_color color) {
		char* end_i = memory_address((struct pos) {
			::Graphics::pixel_size.width - 1,
			::Graphics::pixel_size.height - 1,
		});
		for (char* i = vram_base; i < end_i; i++) *i = color;
	}
	//-------------------------------------------------------------------------
	// ● 填充矩形
	//-------------------------------------------------------------------------
	void fill_rect(struct rect rect, enum indexed_color color) {
		/*
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
		*/
	}

	//-------------------------------------------------------------------------
	// ● 绘制字符
	//-------------------------------------------------------------------------
	void draw_char(struct pos pos, struct vector offset, char c, enum indexed_color color) {
		int i, y;
		uint8_t line;
		char* address;
		if (pos.x >= ::Graphics::block_size.width
			|| pos.y >= ::Graphics::block_size.height
			|| c < ' ' || c > '~') {
			return;
		}
		c -= 32;
		for (i = 0; i < default_font_height; i++) {
			y = pos.y * 16 + offset.y + i;
			line = default_font[c][i];
			address = memory_address((struct pos) {pos.x * 16 + offset.x, y});
			if (line & 1 << 0) *(address + 7) = color;
			if (line & 1 << 1) *(address + 6) = color;
			if (line & 1 << 2) *(address + 5) = color;
			if (line & 1 << 3) *(address + 4) = color;
			if (line & 1 << 4) *(address + 3) = color;
			if (line & 1 << 5) *(address + 2) = color;
			if (line & 1 << 6) *(address + 1) = color;
			if (line & 1 << 7) *(address + 0) = color;
		}
	}
	//-------------------------------------------------------------------------
	// ● 绘制文本
	//-------------------------------------------------------------------------
	void draw_text(struct pos pos, struct vector offset, const char* str, enum indexed_color color) {
		if (pos.x >= ::Graphics::block_size.width
			|| pos.y >= ::Graphics::block_size.height) {
			return;
		}
		int ox = offset.x;
		while (*str) {
			draw_char(pos, (struct vector) {ox, offset.y}, *str, color);
			ox += 8; str++;
		}
	}
	//-------------------------------------------------------------------------
	// ● 绘制鼠标指针
	//-------------------------------------------------------------------------
	void draw_cursor(struct pos pos) {
		/*
		fill_rect((struct rect) {pos.x - 3, pos.y, 7, 1}, cursor_color);
		fill_rect((struct rect) {pos.x, pos.y - 3, 1, 7}, cursor_color);
		*/
	}
	//-------------------------------------------------------------------------
	// ● 启用
	//-------------------------------------------------------------------------
	void set() {
		::Graphics::cleanup = FM::nop;
		::Graphics::pixel_size.width = 320;
		::Graphics::pixel_size.height = 200;
		::Graphics::update_block_size();
	}
}}

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
// ■ vga_text.cpp
//-----------------------------------------------------------------------------
//   字符模式VGA显卡驱动。
//=============================================================================

namespace VGA { namespace Text {
	// ↑ 你问我为什么不能一步到位？C++1z是什么，好吃吗？
	//-------------------------------------------------------------------------
	// ● 定义
	//-------------------------------------------------------------------------
	auto vram_base = (char* const) 0xb8000;
	struct size char_size;
	//-------------------------------------------------------------------------
	// ● 计算显示位置的内存地址
	//-------------------------------------------------------------------------
	char* memory_address(struct pos char_pos) {
		return vram_base + (char_pos.x + char_pos.y * char_size.width) * 2;
	}
	//-------------------------------------------------------------------------
	// ● 填充整个屏幕
	//-------------------------------------------------------------------------
	void fill(struct color color) {
		auto end_i = (unsigned char*) memory_address((struct pos) {
			char_size.width - 1,
			char_size.height - 1,
		});
		unsigned char c = ((uint8_t) rgb_to_cga16(color)) << 4;
		for (auto i = (unsigned char*) vram_base; i < end_i; *i++ = ' ', *i++ = c);
	}
	//-------------------------------------------------------------------------
	// ● 填充矩形
	//-------------------------------------------------------------------------
	void fill_rect(struct rect rect, struct color color) {/*
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
		}, color);*/
	}
	//-------------------------------------------------------------------------
	// ● 绘制字符
	//-------------------------------------------------------------------------
	void draw_char(struct pos pos, struct vector offset, char c, enum indexed_color color) {
		char* address = memory_address((struct pos) {pos.x * 2 + offset.x / 8, pos.y});
		*address = c; address++;
		*address = (*address & 0xf0) | ((char) color & 0x0f);
	}
	//-------------------------------------------------------------------------
	// ● 绘制文本
	//-------------------------------------------------------------------------
	void draw_text(struct pos pos, struct vector offset, const char* str, struct color color) {
		if (pos.x >= ::Graphics::block_size.width
			|| pos.y >= ::Graphics::block_size.height) {
			return;
		}
		int ox = offset.x;
		enum indexed_color c = rgb_to_cga16(color);
		while (*str) {
			draw_char(pos, (struct vector) {ox, offset.y}, *str, c);
			ox += 8; str++;
		}
	}
	//-------------------------------------------------------------------------
	// ● 绘制鼠标指针
	//-------------------------------------------------------------------------
	void draw_cursor(struct pos pos, struct vector offset) {
		char* address = memory_address((struct pos) {pos.x * 2, pos.y});
		address++;
		*address = 0x77;
		address++;
		address++;
		*address = 0x77;
	}
	//-------------------------------------------------------------------------
	// ● 启用
	//-------------------------------------------------------------------------
	void set() {
		::Graphics::cleanup = FM::nop;
		char_size.width = 80;
		char_size.height = 25;
		::Graphics::pixel_size =
			(struct size) {char_size.width * 8, char_size.height * 16};
		::Graphics::update_block_size();
		::Graphics::fill = fill;
		::Graphics::draw_text = draw_text;
		::Graphics::draw_cursor = draw_cursor;
	}
}}

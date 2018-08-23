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
//   图形绘制函数库。
//=============================================================================

namespace Graphics {
	//-------------------------------------------------------------------------
	// ● 驱动提供的接口
	//-------------------------------------------------------------------------
	void (*cleanup)();
	struct size pixel_size, block_size;
	void (*fill)(struct color);
	void (*draw_text)(struct pos, struct vector, const char*, struct color);
	void (*draw_cursor)(struct pos, struct vector);
	//-------------------------------------------------------------------------
	// ● 根据pixel_size更新block_size
	//-------------------------------------------------------------------------
	void update_block_size() {
		block_size.width = pixel_size.width / 16;
		block_size.height = pixel_size.height / 16;
	}
	//-------------------------------------------------------------------------
	// ● 绘制数值
	//-------------------------------------------------------------------------
	void draw_number(struct pos pos, struct vector offset, long value, struct color color) {
		char buf[12];
		FM::String::i_to_s(buf, value);
		draw_text(pos, offset, buf, color);
	}
	//-------------------------------------------------------------------------
	// ● 重绘
	//-------------------------------------------------------------------------
	void redraw() {
		fill((struct color) {0, 0, 0, 255});
		draw_cursor(Mouse::pos, Mouse::offset);
	}
}

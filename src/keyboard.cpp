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
// ■ keyboard.cpp
//-----------------------------------------------------------------------------
//   键盘驱动程序。还包含一点鼠标的处理。
//=============================================================================

namespace Keyboard {
	//-------------------------------------------------------------------------
	// ● 定义
	//-------------------------------------------------------------------------
	const unsigned int queue_size = 32;
	static uint8_t queue_data[queue_size];
	static FMQueue8 queue(queue_data, queue_size);

	//-------------------------------------------------------------------------
	// ● 等待键盘的回应
	//-------------------------------------------------------------------------
	inline void wait() {
		while (ASM::in8(0x64) & 1 << 1);
	}

	//-------------------------------------------------------------------------
	// ● 初始化键盘并启用鼠标
	//-------------------------------------------------------------------------
	void initialize() {
		wait(); ASM::out8(0x64, 0x60);
		wait(); ASM::out8(0x60, 0x47);
		wait(); ASM::out8(0x64, 0xd4);
		wait(); ASM::out8(0x60, 0xf4);
	}

	//-------------------------------------------------------------------------
	// ● 处理队列中的数据（一项）
	//-------------------------------------------------------------------------
	void process_data() {
	char buf[15];
		Graphics::fill_rect(0, 0, Graphics::width, Graphics::default_font_height, Graphics::BLACK);
		FMString::long2charbuf(buf, queue.shift());
		Graphics::draw_text((struct pos) {0, 0}, buf, Graphics::WHITE);
	}
}

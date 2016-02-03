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
// ■ mouse.cpp
//-----------------------------------------------------------------------------
//   鼠标驱动程序。参照：http://wiki.osdev.org/PS/2_Mouse
//=============================================================================

namespace Mouse {
	//-------------------------------------------------------------------------
	// ● 定义
	//-------------------------------------------------------------------------
	const unsigned int queue_size = 256;
	static uint8_t queue_data[queue_size];
	static FMQueue8 queue(queue_data, queue_size);
	struct info {
		char stage;
		uint8_t msg[3];
	} info;
	struct state {
		bool left_button, middle_button, right_button;
		struct vector motion;
		struct pos pos;
	} state;

	//-------------------------------------------------------------------------
	// ● 初始化
	//-------------------------------------------------------------------------
	void initialize() {
		info.stage = -1;
		state.left_button = state.middle_button = state.right_button = false;
		state.motion = (struct vector) {0, 0};
		state.pos.x = static_cast<int>(Graphics::width / 2);
		state.pos.y = static_cast<int>(Graphics::height / 2);
	}

	//-------------------------------------------------------------------------
	// ● 处理队列中的数据（一项）
	//-------------------------------------------------------------------------
	void process_data() {
		char buf[15];
		uint8_t msg = queue.shift();
		switch (info.stage) {
			case 0:
				// 第1个字节的第3位一定是1
				if (msg & 1 << 3){
					info.msg[0] = msg;
					info.stage = 1;
				}
				break;
			case 1:
				info.msg[1] = msg;
				info.stage = 2;
				break;
			case 2:
				// 集齐鼠标的3个字节……
				info.msg[2] = msg;
				info.stage = 0;
				// 更新三个键是否按下的状态
				state.left_button = info.msg[0] & 1 << 0;
				state.middle_button = info.msg[0] & 1 << 2;
				state.right_button = info.msg[0] & 1 << 1;
				// 计算运动向量
				state.motion.x = info.msg[1];
				state.motion.y = info.msg[2];
				if (info.msg[0] & 1 << 4) state.motion.x |= 0xffffff00;
				if (info.msg[0] & 1 << 5) state.motion.y |= 0xffffff00;
				state.motion.y *= -1;
				// 对鼠标坐标应用向量
				state.pos.x += state.motion.x;
				state.pos.y += state.motion.y;
				// 超出画面边界的处理
				if (state.pos.x < 0) state.pos.x = 0;
				if (state.pos.x >= Graphics::width) state.pos.x = Graphics::width;
				if (state.pos.y < 0) state.pos.y = 0;
				if (state.pos.y >= Graphics::height) state.pos.y = Graphics::height;
				// 绘制鼠标指针
				Graphics::set_pixel(state.pos,
					state.left_button ? Graphics::FUCHSIA : Graphics::YELLOW);
				// 绘制鼠标坐标
				Graphics::fill_rect((struct rect) {
					.x = 0,
					.y = 12,
					.width = Graphics::width,
					.height = Graphics::default_font_height,
				}, Graphics::BLACK);
				FMString::long2charbuf(buf, state.pos.x);
				Graphics::draw_text((struct pos) {0, 12}, buf, Graphics::WHITE);
				FMString::long2charbuf(buf, state.pos.y);
				Graphics::draw_text((struct pos) {100, 12}, buf, Graphics::WHITE);
				break;
			default:
				// 鼠标准备好了后会发送这个数据
				if (msg == 0xfa) info.stage = 0;
		}
	}
}

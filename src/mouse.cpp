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
	const unsigned int QUEUE_SIZE = 256;
	const uint8_t ACKNOWLEDGE = 0xfa;
	uint8_t queue_data[QUEUE_SIZE];
	FMQueue<uint8_t> queue(queue_data, QUEUE_SIZE);
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
	// ● 根据第1个字节更新按键状态
	//-------------------------------------------------------------------------
	void update_button_state(uint8_t msg0) {
		state.left_button = msg0 & 1 << 0;
		state.middle_button = msg0 & 1 << 2;
		state.right_button = msg0 & 1 << 1;
	}

	//-------------------------------------------------------------------------
	// ● 根据3个字节计算运动向量
	//-------------------------------------------------------------------------
	void update_motion(uint8_t msg0, uint8_t msg1, uint8_t msg2) {
		state.motion.x = msg1;
		state.motion.y = msg2;
		if (msg0 & 1 << 4) state.motion.x |= 0xffffff00;
		if (msg0 & 1 << 5) state.motion.y |= 0xffffff00;
		state.motion.y *= -1;
	}

	//-------------------------------------------------------------------------
	// ● 对坐标应用向量
	//-------------------------------------------------------------------------
	void apply_motion(struct vector motion) {
		state.pos.x += motion.x;
		state.pos.y += motion.y;
	}

	//-------------------------------------------------------------------------
	// ● 修理鼠标指针（超出画面边界的处理）
	//-------------------------------------------------------------------------
	void fix_pos() {
		if (state.pos.x < 0) state.pos.x = 0;
		if (state.pos.x >= Graphics::width) state.pos.x = Graphics::width - 1;
		if (state.pos.y < 0) state.pos.y = 0;
		if (state.pos.y >= Graphics::height) state.pos.y = Graphics::height - 1;
	}

	//-------------------------------------------------------------------------
	// ● 处理队列中的数据（一项）
	//-------------------------------------------------------------------------
	void process_data() {
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
				// 更新状态
				update_button_state(info.msg[0]);
				update_motion(info.msg[0], info.msg[1], info.msg[2]);
				apply_motion(state.motion);
				fix_pos();
				// 绘制
				Graphics::draw_cursor(state.pos);
				break;
			default:
				// 鼠标准备好了后会发送这个数据
				if (msg == ACKNOWLEDGE) info.stage = 0;
		}
	}

}

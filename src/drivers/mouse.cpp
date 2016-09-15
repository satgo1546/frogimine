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
// ■ drivers/mouse.cpp
//-----------------------------------------------------------------------------
//   鼠标驱动程序。参照：http://wiki.osdev.org/PS/2_Mouse
//=============================================================================

namespace PS2Mouse {
	//-------------------------------------------------------------------------
	// ● 定义
	//-------------------------------------------------------------------------
	const int QUEUE_SIZE = 256;
	const uint8_t ACKNOWLEDGE = 0xfa;
	uint8_t queue_data[QUEUE_SIZE];
	FMQueue<uint8_t> queue(queue_data, QUEUE_SIZE);
	struct info {
		char stage = -1;
		uint8_t msg[3];
	} info;
	//-------------------------------------------------------------------------
	// ● 根据第1个字节更新按键状态
	//-------------------------------------------------------------------------
	void update_button_state(uint8_t msg0) {
		Mouse::buttons.left = msg0 & 1 << 0;
		Mouse::buttons.middle = msg0 & 1 << 2;
		Mouse::buttons.right = msg0 & 1 << 1;
	}
	//-------------------------------------------------------------------------
	// ● 根据3个字节计算运动向量
	//-------------------------------------------------------------------------
	void update_motion(uint8_t msg0, uint8_t msg1, uint8_t msg2) {
		Mouse::motion.x = msg1;
		Mouse::motion.y = msg2;
		if (msg0 & 1 << 4) Mouse::motion.x |= 0xffffff00;
		if (msg0 & 1 << 5) Mouse::motion.y |= 0xffffff00;
		Mouse::motion.y *= -1;
	}
	//-------------------------------------------------------------------------
	// ● 对坐标应用向量
	//-------------------------------------------------------------------------
	void apply_motion(struct vector motion = Mouse::motion) {
		Mouse::pixel_pos.x += motion.x;
		Mouse::pixel_pos.y += motion.y;
	}
	//-------------------------------------------------------------------------
	// ● 修理鼠标指针（超出画面边界的处理）
	//-------------------------------------------------------------------------
	void fix_pos() {
		Mouse::pixel_pos.x = FMMath::clamp(
			Mouse::pixel_pos.x,
			0, Graphics::pixel_size.width - 1
		);
		Mouse::pixel_pos.y = FMMath::clamp(
			Mouse::pixel_pos.y,
			0, Graphics::pixel_size.width - 1
		);
	}
	//-------------------------------------------------------------------------
	// ● 转换坐标系
	//-------------------------------------------------------------------------
	void update_offset() {
		Mouse::pos = (struct pos) {Mouse::pixel_pos.x / 16, Mouse::pixel_pos.y / 16};
		Mouse::offset = (struct vector) {Mouse::pixel_pos.x % 16, Mouse::pixel_pos.y % 16};
	}
	//-------------------------------------------------------------------------
	// ● 处理队列中的数据（一项）
	//-------------------------------------------------------------------------
	void process_data() {
		uint8_t msg = queue.shift();
		switch (info.stage) {
			case 0:
				// 第1个字节的第3位一定是1
				if (msg & 1 << 3) {
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
				apply_motion();
				fix_pos();
				update_offset();
				break;
			default:
				// 鼠标准备好了后会发送这个数据
				if (msg == ACKNOWLEDGE) info.stage = 0;
		}
	}
	//-------------------------------------------------------------------------
	// ● 是否需要刷新状态/处理数据？
	//-------------------------------------------------------------------------
	bool needs_refresh() {
		return !queue.is_empty();
	}
	//-------------------------------------------------------------------------
	// ● 设置函数指针
	//-------------------------------------------------------------------------
	void set() {
		Mouse::needs_refresh = needs_refresh;
		Mouse::refresh = process_data;
	}
}

//-----------------------------------------------------------------------------
// ● INT 0x2c：PS/2鼠标
//-----------------------------------------------------------------------------
extern "C" void int44(uint32_t* esp) {
	ASM::out8(0xa0, 0x64);
	ASM::out8(0x20, 0x62);
	PS2Mouse::queue.push(ASM::in8(0x60));
}

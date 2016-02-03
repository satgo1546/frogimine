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

	//-------------------------------------------------------------------------
	// ● 初始化
	//-------------------------------------------------------------------------
	void initialize() {
		info.stage = -1;
	}

	//-------------------------------------------------------------------------
	// ● 处理队列中的数据（一项）
	//-------------------------------------------------------------------------
	void process_data() {
		char buf[15];
		uint8_t msg = queue.shift();
		switch (info.stage) {
			case 0:
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
				info.msg[2] = msg;
				info.stage = 0;
				Graphics::fill_rect(0, 32, Graphics::width, Graphics::default_font_height, Graphics::BLACK);
				FMString::long2charbuf(buf, info.msg[0]);
				Graphics::draw_text((struct pos) {0, 32}, buf, Graphics::WHITE);
				FMString::long2charbuf(buf, info.msg[1]);
				Graphics::draw_text((struct pos) {64, 32}, buf, Graphics::WHITE);
				FMString::long2charbuf(buf, info.msg[2]);
				Graphics::draw_text((struct pos) {128, 32}, buf, Graphics::WHITE);
				break;
			default:
				if (msg == 0xfa) info.stage = 0;
		}
	}
}

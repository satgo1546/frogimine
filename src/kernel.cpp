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
// ■ kernel.cpp
//-----------------------------------------------------------------------------
//   内核。不知道有什么用。
//=============================================================================

//-----------------------------------------------------------------------------
// ● 主循环
//-----------------------------------------------------------------------------
void kernel_loop() {
	ASM::cli();
	if (!Keyboard::queue.is_empty()) {
		Keyboard::process_data();
		Graphics::redraw();
	} else if (Mouse::needs_refresh()) {
		Mouse::refresh();
		Graphics::redraw();
	} else {
		ASM::sti_hlt();
	}
}

//-----------------------------------------------------------------------------
// ● 供外部调用的内核主程序
//   需确保此程序不返回。
//-----------------------------------------------------------------------------
extern "C" void kernel_main(intptr_t multiboot_info_address) {
	initialize(multiboot_info_address);
	for (;;) kernel_loop();
	// 万一返回了，还有一点药可救
	for (;;) ASM::hlt();
}

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
// ■ initialize.cpp
//-----------------------------------------------------------------------------
//   一开始叫我把初始化部分提取出来，我是拒绝的。
//=============================================================================

//-----------------------------------------------------------------------------
// ● 初始化
//-----------------------------------------------------------------------------
void initialize(intptr_t multiboot_info_address) {
	Memory::multiboot_info_address = multiboot_info_address;
	MultibootInfo::initialize();
	GDT::initialize();
	IDT::initialize();
	Interrupt::initialize();
	Keyboard::initialize();
	ASM::initialize_pattle();
	Graphics::draw_text((struct pos) {0, 0}, MultibootInfo::mem_lower, Graphics::WHITE);
	Graphics::draw_text((struct pos) {100, 0}, MultibootInfo::mem_upper, Graphics::WHITE);
	Graphics::draw_text((struct pos) {0, 24}, Memory::kernel_start, Graphics::WHITE);
	Graphics::draw_text((struct pos) {100, 24}, Memory::kernel_end, Graphics::WHITE);
}

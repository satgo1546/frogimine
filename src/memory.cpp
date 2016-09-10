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
// ■ memory.cpp
//-----------------------------------------------------------------------------
//   操作内存的函数。
//=============================================================================

// 这两个数据在linker.lds中定义。这个做法真是太神奇了——依旧不明白它的运作机理。
// PS1：必须放在最外面。PS2：extern后面的"C"不是必要的。
extern uint8_t kernel_start__defined_by_linker_script[];
extern uint8_t kernel_end__defined_by_linker_script[];

namespace Memory {
	//-------------------------------------------------------------------------
	// ● 定义
	//-------------------------------------------------------------------------
	auto kernel_start = (intptr_t) kernel_start__defined_by_linker_script;
	auto kernel_end = (intptr_t) kernel_end__defined_by_linker_script;

	//-------------------------------------------------------------------------
	// ● 根据地址读出内存
	//-------------------------------------------------------------------------
	inline uint8_t read8_at(intptr_t address) {
		return *((uint8_t*) address);
	}
	inline uint32_t read32_at(intptr_t address) {
		return *((uint32_t*) address);
	}

	//-------------------------------------------------------------------------
	// ● 根据地址写入内存
	//-------------------------------------------------------------------------
	inline void write8_at(intptr_t address, uint8_t value) {
		*((uint8_t*) address) = value;
	}
}

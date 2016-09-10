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
// ■ multiboot-info.cpp
//-----------------------------------------------------------------------------
//   处理与存储Multiboot启动信息结构，参照：
//   https://www.gnu.org/software/grub/manual/multiboot/multiboot.html#Boot-information-format
//=============================================================================

namespace MultibootInfo {
	uint32_t flags;
	uint32_t mem_lower, mem_upper; // 可用的连续内存地址，单位为KB
	const char* cmdline;
	const char* boot_loader_name;
	void initialize() {
		intptr_t address = Memory::multiboot_info_address;
		flags = Memory::read32_at(address);
		if (flags & 1 << 0) {
			mem_lower = Memory::read32_at(address + 4);
			mem_upper = Memory::read32_at(address + 8);
		} else {
			mem_lower = mem_upper = 0;
		}
		if (flags & 1 << 2) {
			cmdline = (const char*) Memory::read32_at(address + 16);
		} else {
			cmdline = nullptr;
		}
		if (flags & 1 << 9) {
			boot_loader_name = (const char*) Memory::read32_at(address + 64);
		} else {
			boot_loader_name = nullptr;
		}
	}
}

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

namespace Global {
	//-------------------------------------------------------------------------
	// ● 定义
	//-------------------------------------------------------------------------
	// Frogimine的启动信息
	struct bootinfo {
		uint32_t multiboot_flags = 0;
		// 可用的连续内存地址，单位为KB
		uint32_t memory_lower = 0, memory_upper = 0;
		char commandline[256] = {0};
		char bootloader[32] = {0};
	} bootinfo;
	// Multiboot信息
	// 参照：https://www.gnu.org/software/grub/
	// manual/multiboot/multiboot.html#Boot-information-format
	struct multiboot_info {
		uint32_t flags;
		uint32_t mem_lower, mem_upper;
		uint32_t boot_device;
		uint32_t cmdline;
		uint32_t mods_count;
		uint32_t mods_addr;
		union {
			struct a_out {
				uint32_t tabsize;
				uint32_t strsize;
				uint32_t addr;
				uint32_t reserved;
			};
			struct elf {
				uint32_t num;
				uint32_t size;
				uint32_t addr;
				uint32_t shndx;
			};
		} syms;
		uint32_t mmap_length;
		uint32_t mmap_addr;
		uint32_t drives_length;
		uint32_t drives_addr;
		uint32_t config_table;
		uint32_t boot_loader_name;
		uint32_t apm_table;
		uint32_t vbe_control_info;
		uint32_t vbe_mode_info;
		uint16_t vbe_mode;
		uint16_t vbe_interface_seg;
		uint16_t vbe_interface_off;
		uint16_t vbe_interface_len;
	} __attribute__((packed));
	//-------------------------------------------------------------------------
	// ● 读取Multiboot信息
	//-------------------------------------------------------------------------
	void load_multiboot() {
		auto info = (struct multiboot_info*) Memory::multiboot_info_address;
		if (info->flags & 1 << 0) {
			bootinfo.memory_lower = info->mem_lower;
			bootinfo.memory_upper = info->mem_upper;
		}
		if (info->flags & 1 << 2) {
			FM::String::strcpy(bootinfo.commandline, (const char*) info->cmdline);
		}
		if (info->flags & 1 << 9) {
			FM::String::strcpy(bootinfo.bootloader, (const char*) info->boot_loader_name);
		}
	}
	//-------------------------------------------------------------------------
	// ● 初始化
	//-------------------------------------------------------------------------
	void initialize(intptr_t multiboot_info_address) {
		Memory::multiboot_info_address = multiboot_info_address;
		load_multiboot();
		GDT::initialize();
		IDT::initialize();
		Interrupt::initialize();
		Keyboard::initialize();
		ASM::initialize_pattle();
		VGA::Text::set();
		PS2Mouse::set();
		Graphics::draw_text((struct pos) {0, 0}, vector0, "Greetings from 8025.", (struct color) {255, 255, 255, 255});
		/*
		Graphics::draw_text((struct pos) {0, 0}, bootinfo.memory_lower, Graphics::WHITE);
		Graphics::draw_text((struct pos) {100, 0}, bootinfo.memory_upper, Graphics::WHITE);
		Graphics::draw_text((struct pos) {0, 24}, Memory::kernel_start, Graphics::WHITE);
		Graphics::draw_text((struct pos) {100, 24}, Memory::kernel_end, Graphics::WHITE);
		*/
	}
}

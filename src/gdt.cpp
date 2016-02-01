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
// ■ gdt.cpp
//-----------------------------------------------------------------------------
//   与GDT有关的设定。
//   参照：《Intel® 64 and IA-32 Architectures Software Developer’s Manual,
//   Volume 3A: System Programming Guide, Part 1》
//=============================================================================

namespace GDT {
	//-------------------------------------------------------------------------
	// ● 定义
	//   参照：3.4.5 Segment Descriptors
	// ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
	// ┃                         Segment Descriptor                         ┃
	// ┃                                                                    ┃
	// ┃ 31            242322212019    161514131211     8 7             0   ┃
	// ┃ ┌┴─────────────┴┬┴┬┴┬┴┬┴┬┴─────┴┬┴┬┴─┴┬┴┬┴─────┴┬┴─────────────┴┐  ┃
	// ┃ │  Base  31:24  │G│D│L│A│SL19:16│P│DPL│S│ Type  │  Base  23:16  │4 ┃
	// ┃ └───────────────┴─┴─┴─┴─┴───────┴─┴───┴─┴───────┴───────────────┘  ┃
	// ┃ 31                            1615                             0   ┃
	// ┃ ┌┴─────────────────────────────┴┬┴─────────────────────────────┴┐  ┃
	// ┃ │      Base Address  15:00      │      Segment Limit 15:00      │0 ┃
	// ┃ └───────────────────────────────┴───────────────────────────────┘  ┃
	// ┃ L     — 64-bit code segment (IA-32e mode only)                     ┃
	// ┃ A     — Available for use by system software                       ┃
	// ┃ BASE  — Segment base address                                       ┃
	// ┃ D     — Default operation size                                     ┃
	// ┃         (0 = 16-bit segment; 1 = 32-bit segment)                   ┃
	// ┃ DPL   — Descriptor privilege level                                 ┃
	// ┃ G     — Granularity                                                ┃
	// ┃ LIMIT — Segment Limit                                              ┃
	// ┃ P     — Segment present                                            ┃
	// ┃ S     — Descriptor type (0 = system; 1 = code or data)             ┃
	// ┃ Type  — Segment type                                               ┃
	// ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
	//-------------------------------------------------------------------------
	struct segment_descriptor {
		uint16_t limit1;
		uint16_t base1;
		uint8_t base2;
		uint8_t a;
		uint8_t b;
		uint8_t base3;
	};

	//-------------------------------------------------------------------------
	// ● 设定段描述符
	//-------------------------------------------------------------------------
	void set(struct segment_descriptor* s, type_address base, uint32_t limit, uint16_t a) {
		if (limit > 0xfffff) {
			a |= 1 << 15;
			limit >>= 12;
		}
		s -> limit1 = limit & 0xffff;
		s -> b = (limit >> 16) & 0xf;
		s -> base1 = base & 0xffff;
		s -> base2 = (base & 0xff0000) / 0x10000;
		s -> base3 = (base & 0xff000000) / 0x1000000;
		s -> b |= (a >> 8) & 0xf0;
		s -> a = a & 0xff;
	}

	//-------------------------------------------------------------------------
	// ● 初始化
	//-------------------------------------------------------------------------
	void initialize() {
		// 随便找了个内存地址
		// 参照：http://wiki.osdev.org/Memory_Map_%28x86%29
		const type_address address = 0x310000;
		auto gdt = (struct segment_descriptor*) address;
		int i;
		for (i = 3; i < 8192; i++) {
			set(gdt + i, 0, 0, 0);
		}
		set(gdt, 0, 0, 0);
		set(gdt + 1, 0, 0xffffffff, 0x4092);
		ASM::set_gdtr(0xffff, address);
	}
}

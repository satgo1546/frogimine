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
	// ┃ BASE  — Segment base address                                       ┃
	// ┃ SL    — Segment Limit                                              ┃
	// ┃ G     — Granularity                                                ┃
	// ┃ D     — Default operation size                                     ┃
	// ┃         (0 = 16-bit segment; 1 = 32-bit segment)                   ┃
	// ┃ L     — 64-bit code segment (IA-32e mode only)                     ┃
	// ┃ A     — Available for use by system software                       ┃
	// ┃ P     — Segment present                                            ┃
	// ┃ DPL   — Descriptor privilege level                                 ┃
	// ┃ S     — Descriptor type (0 = system; 1 = code or data)             ┃
	// ┃ Type  — Segment type                                               ┃
	// ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
	//-------------------------------------------------------------------------
	struct segment_descriptor {
		uint16_t limit1;
		uint16_t base1;
		uint8_t base2;
		uint8_t a; // G << 7 | D << 6 | L << 5 | A << 4 | SL
		uint8_t b; // P << 7 | DPL << 5 | S << 4 | Type
		uint8_t base3;
	} __attribute__((packed));
	const int gdt_count = 8192;
	struct segment_descriptor gdt[gdt_count];

	//-------------------------------------------------------------------------
	// ● 设定段描述符
	//   a : 12位的段属性中的低8位。高4位固定为×100，G位（×）由本函数自行处理。
	//-------------------------------------------------------------------------
	void set(int index, type_address base, type_size limit, uint8_t a) {
		uint8_t b = 1 << 6;
		if (limit > 0xfffff) {
			b |= 1 << 7;
			limit >>= 12;
		}
		gdt[index].limit1 = limit & 0xffff;
		gdt[index].b = (limit >> 16) & 0xf;
		gdt[index].base1 = base & 0xffff;
		gdt[index].base2 = (base & 0xff0000) / 0x10000;
		gdt[index].base3 = (base & 0xff000000) / 0x1000000;
		gdt[index].a = a;
		gdt[index].b |= b;
	}

	//-------------------------------------------------------------------------
	// ● 初始化
	//-------------------------------------------------------------------------
	void initialize() {
		int i;
		for (i = 3; i < gdt_count; i++) {
			set(i, 0, 0, 0);
		}
		set(0, 0, 0, 0);
		set(1, 0, 0xffffffff, 0b10010010);
		set(2, 0, 0xffffffff, 0b10011010);
		ASM::set_gdtr(0xffff, (type_address) &gdt);
	}
}

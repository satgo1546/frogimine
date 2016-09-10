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
// ■ idt.cpp
//-----------------------------------------------------------------------------
//   与IDT有关的设定。
//   参照：《Intel® 64 and IA-32 Architectures Software Developer’s Manual,
//   Volume 3A: System Programming Guide, Part 1》
//=============================================================================

namespace IDT {
	//-------------------------------------------------------------------------
	// ● 定义
	//   参照：6.11 IDT DESCRIPTORS
	// ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
	// ┃                           Interrupt Gate                           ┃
	// ┃                                                                    ┃
	// ┃ 31                            1615141312       8 7   5 4       0   ┃
	// ┃ ┌┴─────────────────────────────┴┬┴┬┴─┴┬┴───────┴┬┴───┴┬┴───────┴┐  ┃
	// ┃ │         Offset 31..16         │P│DPL│0 D 1 1 0│0 0 0│         │4 ┃
	// ┃ └───────────────────────────────┴─┴───┴─────────┴─────┴─────────┘  ┃
	// ┃ 31                            1615                             0   ┃
	// ┃ ┌┴─────────────────────────────┴┬┴─────────────────────────────┴┐  ┃
	// ┃ │       Segment  Selector       │         Offset  15..0         │0 ┃
	// ┃ └───────────────────────────────┴───────────────────────────────┘  ┃
	// ┃ DPL        Descriptor Privilege Level                              ┃
	// ┃ Offset     Offset to procedure entry point                         ┃
	// ┃ P          Segment Present flag                                    ┃
	// ┃ Selector   Segment Selector for destination code segment           ┃
	// ┃ D          Size of gate: 1 = 32 bits; 0 = 16 bits                  ┃
	// ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
	//-------------------------------------------------------------------------
	struct idt_descriptor {
		uint16_t offset1;
		uint16_t segment_selector;
		uint8_t a; // 0
		uint8_t b; // P << 7 | DPL << 5 | D << 3 | 0b110
		uint16_t offset2;
	} __attribute__((packed));
	const int IDT_COUNT = 256;
	struct idt_descriptor idt[IDT_COUNT];

	//-------------------------------------------------------------------------
	// ● 设定中断描述符
	//-------------------------------------------------------------------------
	void set(int index, intptr_t offset, uint32_t selector, uint8_t b) {
		idt[index].offset1 = offset & 0xffff;
		idt[index].offset2 = (offset & 0xffff0000) / 0x10000;
		idt[index].segment_selector = selector;
		idt[index].a = 0;
		idt[index].b = b;
	}

	//-------------------------------------------------------------------------
	// ● 初始化
	//-------------------------------------------------------------------------
	void initialize() {
		for (int i = 0; i < IDT_COUNT; i++) set(i, 0, 0, 0);
		ASM::set_idtr(0x7ff, (intptr_t) idt);
	}
}

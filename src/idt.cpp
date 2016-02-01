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
		uint8_t a;
		uint8_t b;
		uint16_t offset2;
	};

	//-------------------------------------------------------------------------
	// ● 设定中断描述符
	//-------------------------------------------------------------------------
	void set(struct idt_descriptor* i, uint32_t offset, uint32_t selector,
	uint32_t a) {
		i -> offset1 = offset & 0xffff;
		i -> offset2 = (offset & 0xffff0000) / 0x10000;
		i -> segment_selector = selector;
		i -> a = (a & 0xff00) / 0x100;
		i -> b = a & 0xff;
	}

	//-------------------------------------------------------------------------
	// ● 初始化
	//-------------------------------------------------------------------------
	void initialize() {
		const type_address address = 0x301000;
		auto idt = (struct idt_descriptor*) address;
		int i;
		for (i = 0; i < 256; i++) {
			set(idt + i, 0, 0, 0);
		}
		ASM::set_idtr(0x7ff, address);
		set(idt + 0x21, (uint32_t) ASM::asm_int33, 1 << 1, 0x8e);
	}
}

//=============================================================================
// ■ gdt-idt.cpp
//-----------------------------------------------------------------------------
//   与GDT和IDT有关的设定。
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
	// ● 包装后的中断函数们
	//-------------------------------------------------------------------------
	extern "C" void asm_int33();

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
		set(idt + 0x21, (uint32_t) asm_int33, 0 << 1, 0x8e);
	}
}

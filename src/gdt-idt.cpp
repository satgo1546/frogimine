//=============================================================================
// ■ gdt-idt.cpp
//-----------------------------------------------------------------------------
//   与GDT和IDT有关的设定。
//   参照：《Intel® 64 and IA-32 Architectures Software Developer’s Manual,
//   Volume 3A: System Programming Guide, Part 1》
//=============================================================================

namespace GDT {
	// 参照：3.4.5 Segment Descriptors
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
	struct segment_descriptor {
		uint16_t limit1;
		uint16_t base1;
		uint8_t base2;
		uint8_t a;
		uint8_t b;
		uint8_t base3;
	}
}

namespace IDT {
	// 参照：6.11 IDT DESCRIPTORS
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
	struct idt_descriptor {
		uint16_t offset1;
		uint16_t segment_selector;
		uint8_t a;
		uint8_t b;
		uint16_t offset2;
	}
}

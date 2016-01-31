//=============================================================================
// ■ interrupt.cpp
//-----------------------------------------------------------------------------
//   处理中断信号用。
//=============================================================================

namespace Interrupt {
	//-------------------------------------------------------------------------
	// ● 初始化
	//-------------------------------------------------------------------------
	void initialize() {
		//  PIC0&1↘       ✗✗✗✗✗✗✗✗
		ASM::out8(0x21, 0b11111111);
		ASM::out8(0xa1, 0b11111111);
		// 边沿触发模式
		ASM::out8(0x20, 0x11);
		// IRQ 0~7 → INT 0x20~0x27
		ASM::out8(0x21, 0x20);
		// PIC1 -- IRQ2
		ASM::out8(0x21, 1 << 2);
		// 无缓冲区模式
		ASM::out8(0x21, 0x01);
		// 边沿触发模式
		ASM::out8(0xa0, 0x11);
		// IRQ 8~15 → INT 0x28~0x2f
		ASM::out8(0xa1, 0x28);
		// PIC1 -- IRQ2
		ASM::out8(0xa1, 0x02);
		// 无缓冲区模式
		ASM::out8(0xa1, 0x01);
		//    PIC0↘  #2 PIC1 ✓ ↴
		ASM::out8(0x21, 0b11111011);
		//    PIC1↘       ✗✗✗✗✗✗✗✗
		ASM::out8(0xa1, 0b11111111);
	}

	//-------------------------------------------------------------------------
	// ● INT 0x21：PS/2键盘
	//-------------------------------------------------------------------------
	void int33(uint32_t* esp) {
		Graphics::draw_text((struct pos) {32, 128}, "INT 0x21", Graphics::WHITE);
	}
}

extern "C" void int33(uint32_t* esp) { Interrupt::int33(esp); }

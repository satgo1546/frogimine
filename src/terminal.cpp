//=============================================================================
// ■ terminal.cpp
//-----------------------------------------------------------------------------
//   字符模式显卡驱动。
//=============================================================================

namespace Terminal {
	//---------------------------------------------------------------------------
	// ● 定义类型
	//---------------------------------------------------------------------------
	enum color {
		BLACK = 0,
		NAVY = 1,
		GREEN = 2,
		TEAL = 3,
		MAROON = 4,
		PURPLE = 5,
		OLIVE = 6,
		SILVER = 7,
		GRAY = 8,
		BLUE = 9,
		LIME = 10,
		AQUA = 11,
		RED = 12,
		FUCHSIA = 13,
		YELLOW = 14,
		WHITE = 15,
	};
	struct char_color {
		enum color bg, fg;
	};

	//---------------------------------------------------------------------------
	// ● 定义变量
	//---------------------------------------------------------------------------
	unsigned int width;
	unsigned int height;
	static int cursor_x;
	static int cursor_y;

	//---------------------------------------------------------------------------
	// ● 计算显示位置的内存地址
	//---------------------------------------------------------------------------
	inline type_address memory_address(struct pos pos) {
		return 0xb8000 + (pos.x + pos.y * width) * 2;
	}

	//---------------------------------------------------------------------------
	// ● 移动光标
	//---------------------------------------------------------------------------
	void set_pos(struct pos pos) {
		cursor_x = pos.x;
		cursor_y = pos.y;
		uint8_t pos_info = pos.x + pos.y * width;
		asm_out8(0x03d4, 14);
		asm_out8(0x03d5, pos_info >> 8);
		asm_out8(0x03d4, 15);
		asm_out8(0x03d5, pos_info & 0xff);
	}

	//---------------------------------------------------------------------------
	// ● 写出一个字符
	//   pos : 目标字符的位置
	//   c : 字符
	//   color : 字符的颜色
	//---------------------------------------------------------------------------
	void write_char(struct pos pos, char c, struct char_color color) {
		type_address address = memory_address(pos);
		write_memory(address, c);
		unsigned char attribute = 1 << 7 | color.bg << 4 | color.fg;
		write_memory(address + 1, attribute);
	}
}

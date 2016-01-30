//=============================================================================
// ■ asm.cpp
//-----------------------------------------------------------------------------
//   不得不用汇编编写的函数。一部分函数在外部（asm.asm）定义，另一部分使用内联
//   汇编。因为GAS的语法很诡异，所以大多数情况下不建议直接在这里写。
//=============================================================================

namespace ASM {
	//-------------------------------------------------------------------------
	// ● NOP
	//-------------------------------------------------------------------------
	extern "C" void asm_nop();
	inline void nop() {
		asm_nop();
	}

	//-------------------------------------------------------------------------
	// ● CPU挂起
	//-------------------------------------------------------------------------
	inline void hlt() {
		asm("hlt");
	}

	//-------------------------------------------------------------------------
	// ● 端口写入
	//-------------------------------------------------------------------------
	inline void out8(type_port port, uint8_t value) {
		asm volatile("outb %1, %0" : : "dN" (port), "a" (value));
	}

	//-------------------------------------------------------------------------
	// ● 端口读出
	//-------------------------------------------------------------------------
	inline uint8_t in8(type_port port) {
		uint8_t r;
		asm volatile("inb %1, %0" : "=a" (r) : "dN" (port));
		return r;
	}
	inline uint16_t in16(type_port port) {
		uint16_t r;
		asm volatile("inw %1, %0" : "=a" (r) : "dN" (port));
		return r;
	}

	//-------------------------------------------------------------------------
	// ● 设置IDTR寄存器
	//-------------------------------------------------------------------------
	extern "C" void set_idtr(int limit, type_address address);
}

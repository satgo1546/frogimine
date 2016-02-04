//=============================================================================
// ■ memory.cpp
//-----------------------------------------------------------------------------
//   操作内存的函数。
//=============================================================================

// 这两个数据在linker.lds中定义。这个做法真是太神奇了——依旧不明白它的运作机理。
// PS1：必须放在最外面。PS2：extern后面的"C"不是必要的。
extern uint8_t kernel_start__defined_by_linker_script[];
extern uint8_t kernel_end__defined_by_linker_script[];

namespace Memory {
	//-------------------------------------------------------------------------
	// ● 定义
	//-------------------------------------------------------------------------
	auto kernel_start = (type_address) kernel_start__defined_by_linker_script;
	auto kernel_end = (type_address) kernel_end__defined_by_linker_script;

	//-------------------------------------------------------------------------
	// ● 根据地址读出内存
	//-------------------------------------------------------------------------
	inline uint8_t read8_at(type_address address) {
		return *((uint8_t*) address);
	}
	inline uint32_t read32_at(type_address address) {
		return *((uint32_t*) address);
	}

	//-------------------------------------------------------------------------
	// ● 根据地址写入内存
	//-------------------------------------------------------------------------
	inline void write8_at(type_address address, uint8_t value) {
		*((uint8_t*) address) = value;
	}
}

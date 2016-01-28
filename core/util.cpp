//=============================================================================
// ■ util.cpp
//-----------------------------------------------------------------------------
//   实用的过程和函数集合。
//=============================================================================

#include "../global.h"
#ifndef INCLUDE_UTIL_CPP
#define INCLUDE_UTIL_CPP

//---------------------------------------------------------------------------
// ● CPU挂起
//---------------------------------------------------------------------------
inline void asm_hlt() {
	__asm__ ("hlt");
}

//---------------------------------------------------------------------------
// ● 根据地址读出内存
//---------------------------------------------------------------------------
inline uint8_t read_memory8(type_address address) {
	return *((uint8_t*) address);
}
inline uint32_t read_memory32(type_address address) {
	return *((uint32_t*) address);
}

//---------------------------------------------------------------------------
// ● 根据地址写入内存
//---------------------------------------------------------------------------
inline void write_memory(type_address address, uint8_t value) {
	*((uint8_t*) address) = value;
}

//---------------------------------------------------------------------------
// ● 端口写入（1字节）
//---------------------------------------------------------------------------
inline void asm_out8(type_port port, uint8_t value) {
	asm volatile("outb %1, %0" : : "dN" (port), "a" (value));
}

//---------------------------------------------------------------------------
// ● 端口读出（1字节）
//---------------------------------------------------------------------------
inline uint8_t asm_in8(type_port port) {
	uint8_t r;
	asm volatile("inb %1, %0" : "=a" (r) : "dN" (port));
	return r;
}

//---------------------------------------------------------------------------
// ● 端口读出（2字节）
//---------------------------------------------------------------------------
inline uint16_t asm_in16(type_port port) {
	uint16_t r;
	asm volatile("inw %1, %0" : "=a" (r) : "dN" (port));
	return r;
}

#endif

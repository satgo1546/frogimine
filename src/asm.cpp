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
	// ● 挂起
	//-------------------------------------------------------------------------
	inline void hlt() {
		asm("hlt");
	}

	//-------------------------------------------------------------------------
	// ● 设置中断标记
	//-------------------------------------------------------------------------
	inline void sti() {
		asm("sti");
	}

	//-------------------------------------------------------------------------
	// ● 清除中断标记
	//-------------------------------------------------------------------------
	inline void cli() {
		asm("cli");
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
	// ● 设置GDTR/IDTR寄存器
	//-------------------------------------------------------------------------
	extern "C" void set_gdtr(int limit, type_address address);
	extern "C" void set_idtr(int limit, type_address address);

	//-------------------------------------------------------------------------
	// ● 包装后的中断函数们
	//-------------------------------------------------------------------------
	extern "C" void asm_int33();
}

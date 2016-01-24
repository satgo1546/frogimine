// Copyright 2016 Iceberg OS
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
// ■ idt.h
//-----------------------------------------------------------------------------
//   i686基础驱动：IDT。
//=============================================================================

#ifndef INCLUDE_IDT_H
#define INCLUDE_IDT_H

#include "Basic/types.h"
#include "Basic/io.h"

class IDT {
	private:
	//---------------------------------------------------------------------------
	// ● IDT项
	//---------------------------------------------------------------------------
	struct IDTDescr{
		uint16_t offset_1; // offset bits 0..15
		uint16_t selector; // a code segment selector in GDT or LDT
		uint8_t zero;      // unused, set to 0
		uint8_t type_attr; // type and attributes, see below
		uint16_t offset_2; // offset bits 16..31
	};
	public:
	//---------------------------------------------------------------------------
	// ● IDT初始化
	//---------------------------------------------------------------------------
	IDT();
};

#endif

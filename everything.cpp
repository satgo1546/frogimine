//=============================================================================
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
// ■ everything.cpp
//-----------------------------------------------------------------------------
//   正常的C++项目中都不会有的、只用来包含其它文件的文件。
//=============================================================================

// 全局（系统无关）
#include "src/global.cpp"
#include "src/fm.cpp"
#include "src/fmstring.cpp"
#include "src/fmqueue.cpp"

// 低级函数库
#include "src/asm.cpp"
#include "src/memory.cpp"

// 基础设施和驱动
#include "src/gdt.cpp"
#include "src/idt.cpp"
#include "src/interrupt.cpp"
#include "src/drivers/vga_text.cpp"
//#include "src/drivers/vga_graphics.cpp"

// 硬件抽象层
#include "src/screen.cpp"
#include "src/keyboard.cpp"
#include "src/mouse.cpp"
#include "src/graphics.cpp"

// 主程序
#include "src/initialize.cpp"
#include "src/kernel.cpp"

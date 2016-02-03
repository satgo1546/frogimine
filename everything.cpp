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
//   正常的项目中都会有的、只用来包含其它文件的文件。
//   只是这个项目中的这个文件有点不正常……
//=============================================================================

#include "src/global.cpp"
#include "src/fmstring.cpp"
#include "src/fmqueue.cpp"
#include "src/asm.cpp"
#include "src/memory.cpp"
#include "src/multiboot-info.cpp"
#include "src/terminal.cpp"
#include "src/graphics.cpp"
#include "src/gdt.cpp"
#include "src/idt.cpp"
#include "src/interrupt.cpp"
#include "src/kernel.cpp"

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
// ■ vga_text.cpp
//-----------------------------------------------------------------------------
//   字符模式VGA显卡驱动。
//=============================================================================

namespace VGA { namespace Text {
	// ↑ 你问我为什么不能一步到位？C++1z是什么，好吃吗？
	//-------------------------------------------------------------------------
	// ● 定义
	//-------------------------------------------------------------------------
	const intptr_t vram_base = 0xb8000;
}}

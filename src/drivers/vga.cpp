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
// ■ vga.cpp
//-----------------------------------------------------------------------------
//   VGA驱动中字符和图形模式共用部分。
//=============================================================================

namespace VGA {
	//-------------------------------------------------------------------------
	// ● 定义
	//-------------------------------------------------------------------------
	#include "default_font.cpp"
	enum indexed_color {
		#include "generated/colors_cpp.txt"
	};
	enum indexed_color cursor_color = GRAY_DDD;
	//-------------------------------------------------------------------------
	// ● RGB → CGA 16色
	//   16色有很多种，当初就被微软坑了一次。
	//   关于Windows是如何坑人的，请访问：
	//   Wikipedia: List of software palettes
	//   #Microsoft Windows default 16-color palette
	//   “..., but with colors arranged in a different order.”
	//-------------------------------------------------------------------------
	enum indexed_color rgb_to_cga16(struct color color) {
		short r = 0;
		if (color.r & 0xf0) r |= 4;
		if (color.g & 0xf0) r |= 2;
		if (color.b & 0xf0) r |= 1;
		if ((color.r + color.g + color.b) / 3 >= 128) r |= 8;
		return (enum indexed_color) r;
	}
}

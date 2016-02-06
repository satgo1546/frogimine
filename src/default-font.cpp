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
// ■ default-font.cpp
//-----------------------------------------------------------------------------
//   绘制文本时使用的默认字体数据，仅覆盖ASCII编码中32（空格）~126（~）。
//   字体来源于Linux终端自带的lat9u-12.psfu字体。
//=============================================================================

// 我们默认这个字体要是8像素宽的，所以可以用一个字节存储一行。
const int default_font_width = 8;
const int default_font_height = 12;
const uint8_t default_font[][default_font_height] = {
	#include "generated/default-font-data.txt"
};

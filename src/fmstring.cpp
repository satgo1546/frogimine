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
// ■ fmstring.cpp
//-----------------------------------------------------------------------------
//   为了偷懒而制作的处理字符串及其相关操作的函数库。
//=============================================================================

namespace FMString {
	//-------------------------------------------------------------------------
	// ● 无符号数字 → 字符串（内部使用）
	//-------------------------------------------------------------------------
	void u_to_s(char* buf, unsigned long a, short base = 10) {
		if (a == 0) {
			*buf = 0;
			return;
		}
		*buf++ = a % base;
		u_to_s(buf + 1, a / base, base);
	}
	//-------------------------------------------------------------------------
	// ● 数字 → 字符串
	//-------------------------------------------------------------------------
	void i_to_s(char* buf, long a, short base = 10) {
		// 处理a为零的简单情况
		if (a == 0) {
			buf[0] = ' ';
			buf[1] = '0';
			buf[2] = 0;
			return;
		};
		// 确定符号位
		if (a > 0) {
			buf[0] = '+';
		} else {
			buf[0] = '-';
			a = -a;
		}
		if (a < 0) a = -a;
		// 填入数字
		u_to_s(buf + 1, a, base);
	}
}

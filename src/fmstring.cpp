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
	// ● 把数字转换成字符串
	//-------------------------------------------------------------------------
	void long2charbuf(char* buf, long a) {
		// 处理a为零的简单情况
		if (a == 0) {
			buf[0] = '0';
			buf[1] = '\0';
		};
		// 确定符号位
		buf[0] = (a > 0 ? '+' : '-');
		if (a < 0) a = -a;
		// 确定结果的长度
		// long类型可以达到10位十进制数值
		char len = 1;
		if (a >= 10) len = 2;
		if (a >= 100) len = 3;
		if (a >= 1000) len = 4;
		if (a >= 10000) len = 5;
		if (a >= 100000) len = 6;
		if (a >= 1000000) len = 7;
		if (a >= 10000000) len = 8;
		if (a >= 100000000) len = 9;
		if (a >= 1000000000) len = 10;
		// 执行转换
		int i = len;
		buf[len + 1] = '\0';
		do {
			buf[i] = '0' + a % 10;
			a /= 10;
			i--;
		} while (i >= 1);
	}
}

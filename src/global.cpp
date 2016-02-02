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
// ■ global.cpp
//-----------------------------------------------------------------------------
//   全局包含脖子文件。系统已经去掉了头，可以安全食用了。
//=============================================================================

namespace Global {
	//-------------------------------------------------------------------------
	// ● 定义
	//-------------------------------------------------------------------------
	// 因为没有头，所以只能这样定义uint*_t了。
	typedef __UINT8_TYPE__ uint8_t;
	typedef __UINT16_TYPE__ uint16_t;
	typedef __UINT32_TYPE__ uint32_t;
	typedef __UINT64_TYPE__ uint64_t;

	// 看上去是另一种类型，但其实就是无符号的整数
	typedef uint32_t type_address;
	typedef uint32_t type_size;
	typedef uint16_t type_port;

	// 通用的数据类型
	struct pos {
		int x;
		int y;
	};
	struct rect {
		int x;
		int y;
		unsigned int width;
		unsigned int height;
	};
}

using namespace Global;

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
// ■ global.cpp
//-----------------------------------------------------------------------------
//   全局包含脖子文件。系统已经去掉了头，可以安全食用了。
//=============================================================================

// namespace Global在各处都可以被当作全局命名空间使用。
namespace Global {
	//-------------------------------------------------------------------------
	// ● 宏魔法
	//-------------------------------------------------------------------------
	#define UNUSED __attribute__((unused))
	#define ARRAY_SIZE (sizeof(arr) / sizeof(*(arr)))
	#define EXPLOSION (asm("ud2"))
	//-------------------------------------------------------------------------
	// ● 定义
	//-------------------------------------------------------------------------
	// 因为没有头，所以只能这样定义uint*_t了。
	typedef __UINT8_TYPE__ uint8_t;
	typedef __UINT16_TYPE__ uint16_t;
	typedef __UINT32_TYPE__ uint32_t;
	typedef __UINT64_TYPE__ uint64_t;
	// int*_t也是如此。
	typedef __INT8_TYPE__ int8_t;
	typedef __INT16_TYPE__ int16_t;
	typedef __INT32_TYPE__ int32_t;
	typedef __INT64_TYPE__ int64_t;
	// 看上去是另一种类型，但其实就是无符号的整数。
	typedef int32_t intptr_t;
	typedef uint32_t size_t;
	typedef uint16_t type_port;

	// 图形学的数据类型
	struct pos {
		int x;
		int y;
	};
	struct vector {
		int x;
		int y;
	};
	struct size {
		int width;
		int height;
	};
	struct rect {
		int x;
		int y;
		int width;
		int height;
	};
}

using namespace Global;

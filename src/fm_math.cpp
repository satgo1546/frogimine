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
// ■ fm_math.cpp
//-----------------------------------------------------------------------------
//   不懂三角函数的数学库。
//=============================================================================

namespace FMMath {
	//-------------------------------------------------------------------------
	// ● 绝对值
	//-------------------------------------------------------------------------
	template <class T> T abs(T x) {
		if (x < 0) return -x;
		return x;
	}
	//-------------------------------------------------------------------------
	// ● 最小值和最大值
	//-------------------------------------------------------------------------
	template <class T> T min(T a, T b) {
		if (a < b) return a;
		return b;
	}
	template <class T> T max(T a, T b) {
		if (a > b) return a;
		return b;
	}
	//-------------------------------------------------------------------------
	// ● 裁切值到指定范围
	//-------------------------------------------------------------------------
	template <class T> T clamp(T x, T min, T max) {
		if (x < min) return min;
		if (x > max) return max;
		return x;
	}
}

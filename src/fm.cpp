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
// ■ fm.cpp
//-----------------------------------------------------------------------------
//   终极偷懒函数库，连类也不分了。
//=============================================================================

namespace FM {
	//-------------------------------------------------------------------------
	// ● 定义
	//-------------------------------------------------------------------------
	// 下一次迭代采用的随机数种子（内部使用）
	uint64_t rand_seed;
	//-------------------------------------------------------------------------
	// ● srand
	//-------------------------------------------------------------------------
	void srand(unsigned seed) {
		rand_seed = seed;
	}
	//-------------------------------------------------------------------------
	// ● rand
	//   参照：https://en.wikipedia.org/wiki/Linear_congruential_generator
	//   抄写时采用的是Newlib和Musl的数值。
	//-------------------------------------------------------------------------
	int rand() {
		rand_seed *= 6364136223846793005;
		rand_seed += 1;
		return rand_seed >> 32;
	}
}

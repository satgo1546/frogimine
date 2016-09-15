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
// ■ mouse.cpp
//-----------------------------------------------------------------------------
//   鼠标。
//=============================================================================

namespace Mouse {
	//-------------------------------------------------------------------------
	// ● 定义
	//-------------------------------------------------------------------------
	struct buttons {
		bool left = false;
		bool middle = false;
		bool right = false;
	} buttons;
	struct vector motion = {0, 0};
	struct pos pixel_pos = {0, 0};
	struct pos pos;
	struct vector offset;
	bool (*needs_refresh)();
	void (*refresh)();
}

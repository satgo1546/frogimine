/* Copyright 2016 Iceberg OS

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/

//=============================================================================
// ■ std.cpp
//-----------------------------------------------------------------------------
//   Driver > Basic > StdC++ > std
//=============================================================================

#include "std.h"

//---------------------------------------------------------------------------
// ● 标准C函数：内存复制
//---------------------------------------------------------------------------
void* memcpy(void *desc, const void * src, size_t size) {
	if((desc == NULL) && (src == NULL)) {	// 在Paging那里用了些技巧捕捉漏了的空指针
		return NULL;
	}
	uint8_t *desc1 = (uint8_t*)desc;
	uint8_t *src1 = (uint8_t*)src;
	while(size-- >0) {
		*desc1 = *src1;
		desc1++;
		src1++;
	}
	return desc;
}

//=============================================================================
// ■ debug.h
//-----------------------------------------------------------------------------
//   Driver > Basic > i686 > debug
//=============================================================================

#ifndef INCLUDE_DEBUG_H_
#define INCLUDE_DEBUG_H_

#include "io.h"

#define X86DEBUG

#ifdef X86DEBUG
void x86debugputchar(char c) {	// 调试用，等IO OBJ完成支持驱动之后就扔了
	write_memory(0xb8000,c);
}
#endif

#endif

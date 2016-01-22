//=============================================================================
// ■ kernel.c
//-----------------------------------------------------------------------------
//   这个文件是干什么的？
//=============================================================================

#include "config.h"

#include "Drivers/Basic/i686/types.h"
#include "Drivers/Basic/i686/io.h"
#include "Drivers/Basic/i686/memory.h"

#include "arch_init.h"

/*	debug	*/ 	
#include "Drivers/Basic/i686/debug.h"

extern "C"

//---------------------------------------------------------------------------
// ● 主程序
//---------------------------------------------------------------------------
void kernel_main() {
	
	arch_init ();
	
#ifdef X86DEBUG
	x86debugputchar('K'); // 进了kernel且完成paging了
#endif
	
	for (;;) {
		cpu_hlt ();	// 挂起
	}
}

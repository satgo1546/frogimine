//=============================================================================
// ■ io.c
//-----------------------------------------------------------------------------
//   Driver > Basic > i686 > io
//=============================================================================

#include "io.h"

//---------------------------------------------------------------------------
// ● CPU 挂起
//---------------------------------------------------------------------------
void IO::cpu_hlt () {
	__asm__ ("hlt");
}


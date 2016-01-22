//=============================================================================
// ■ memory.h
//-----------------------------------------------------------------------------
//   Driver > Basic > i686 > memory
//=============================================================================

#include "Drivers/Basic/i686/types.h"

#ifndef INCLUDE_MEMORY_H_
#define INCLUDE_MEMORY_H_

void map_pages_to_dir(int page_id, uint32_t* page_tab, uint8_t flag);
void map_physical_to_page_tab(uint32_t* page_tab, uint8_t flag, uint32_t f, uint32_t t);
void memory_init();

#endif

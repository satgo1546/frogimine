//=============================================================================
// ■ memory.c
//-----------------------------------------------------------------------------
//   Driver > Basic > i686 > memory
//=============================================================================

#include "memory.h"

uint32_t volatile page_directory[1024] __attribute__((aligned(4096)));
uint32_t volatile first_page_table[1024] __attribute__((aligned(4096)));

void memory_init () {
	
	// Init paging ===================================================
	//set each entry to not present
	int j;
	for(j = 0; j < 1024; j++)
	{
		// This sets the following flags to the pages:
		//   Supervisor: Only kernel-mode can access them
		//   Write Enabled: It can be both read from and written to
		//   Not Present: The page table is not present
		page_directory[j] = 0x00000002;
	}
	
	// holds the physical address where we want to start mapping these pages to.
	// in this case, we want to map these pages to the very beginning of memory.
	// we will fill 512 entries in the table, mapping 2 megabytes
	for(unsigned int i = 0; i < 1024; i++)
	{
		// As the address is page aligned, it will always leave 12 bits zeroed.
		// Those bits are used by the attributes ;)
		first_page_table[i] = (i * 0x1000) | 3; 
			// attributes: supervisor level, read/write, present.
	}
	
	// Put the Page Table in the Page Directory
	page_directory[0] = ((unsigned int)first_page_table) | 3;
	
	// enable it
	asm volatile ("movl %%eax, %%cr3" :: "a" (&page_directory)); // load PDPT into CR3
	asm volatile ("movl %cr0, %eax; orl $0x80000000, %eax; movl %eax, %cr0;");
	
	return;
		// Use this return to return back to the kernel
}

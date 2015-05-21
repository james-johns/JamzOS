/**
 * \file
 * \author James Johns
 */

#include <config.h>
#include <memory.h>
#include <malloc.h>
#include <printh.h>
#include <pageTable.h>

#define NULL ((void *)0)
// 512 entries of 8 bytes each; 4k table size

// page tables have LPAE_ENTRIES number of entries, therefore 
struct pageTable_s *hypPageTable;

/**
 * \fn memcpy(void *source, void *dest, unsigned int size)
 *
 * Copy size bytes of memory from source to dest.
 */
void memcpy(void *source, void *dest, unsigned int size)
{
	unsigned int i;
	for (i = 0; i < size; i++) {
		((unsigned char *)dest)[i] = ((unsigned char *)source)[i];
	}
}

void memset(void *dest, unsigned char value, unsigned int size)
{
	unsigned int i;
	for (i = 0; i < size; i++) {
		((unsigned char *)dest)[i] = value;
	}
}

/**
 * \fn init_mmu
 *
 * Initialise MMU, create page tables and load them into TTBR
 */
void init_mmu()
{
	hypPageTable = createPageTable();

	/* devices */
	mapVirtToPhys(hypPageTable, 0x0, 0x0, 0x40000000, 0x39C);
	/* RAM */ 
	mapVirtToPhys(hypPageTable, 0x40000000, 0x40000000, 
		0x10010000, 0x3DF);
	mapVirtToPhys(hypPageTable, 0x50010000, 0x50010000, 
		0x6FFF0000, 0x3DF);
	/* System memory */
	mapVirtToPhys(hypPageTable, 0xC0000000, 0xC0000000, 
		0x40000000, 0x3DF);
	
	unsigned int TTBR_hi, TTBR_lo;
	TTBR_hi = 0;
	TTBR_lo = (unsigned int) hypPageTable->entry;
	setTTBR(TTBR_lo, TTBR_hi);
	setMAIR0VAL(0xEEAA4400);
	setMAIR1VAL(0xFF000004);
	enableMMU();
}

/** 
 * \file 
 * \author James Johns
 *
 */
#include <config.h>
#include <tests.h>
#include <printh.h>
#include <gic.h>
#include <memory.h>
#include <schedule.h>
#include <malloc.h>

void init_irqs();
void init_timer();
void init_pio();

/**
 * \fn _kmain
 *
 * Initialises platform via generic calls which must be implemented
 * by target platform. Includes; irqs, mmu, timer and scheduler
 */
void _kmain()
{
	_end = (unsigned int) &_end;
	malloc(0x10);
	printh("Starting hyp main\r\n");

	init_irqs();
	init_scheduler();
	init_timer();
	init_pio();

	init_mmu();

	enableIRQS();


	printh("\r\nHalting!");
	while (1) {
		//    asm volatile("wfe"::);
	}
}

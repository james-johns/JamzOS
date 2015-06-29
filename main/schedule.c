/**
 * \file
 * \author James Johns
 */

#include <types.h>
#include <cpu.h>
#include <schedule.h>
#include <memory.h>
#include <printk.h>

void print_regs(struct cpuRegs_s *regs);

/**
 * \fn schedule(struct cpuRegs_s *regs)
 *
 * Save and switch the current executing process
 */
void schedule(struct cpuRegs_s *regs)
{
//	printk("Scheduling\r\n");
  regs->r0 = regs->r0;
}

/**
 * \fn init_scheduler
 *
 * Initialise scheduler subsystem
 */
void init_scheduler()
{
}

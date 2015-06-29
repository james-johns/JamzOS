/**
 * \file
 * \author James Johns
 */

#include <config.h>
#include <printk.h>
#include <gic.h>
#include <vgic.h>
#include <vtimer.h>
#include <cpu.h>
#include <memory.h>
#include <irq.h>

void timer_interrupt();
extern void install_svc_vectors();

/**
 * \fn init_irqs
 *
 * Initialise IRQs
 */
void init_irqs()
{
  disableIRQS();
        printk("Installing...");
        install_svc_vectors();
	printk("Installed SVC Vectors");
	init_gic();
}

/**
 * \fn print_regs
 *
 * Print CPU registers for debugging
 */
void print_regs(struct cpuRegs_s *regs)
{
	print_str("\r\nR0 : ");
	print_hex(regs->r0);
	print_str("\r\nR1 : ");
	print_hex(regs->r1);
	print_str("\r\nR2 : ");
	print_hex(regs->r2);
	print_str("\r\nR3 : ");
	print_hex(regs->r3);
	print_str("\r\nR4 : ");
	print_hex(regs->r4);
	print_str("\r\nR5 : ");
	print_hex(regs->r5);
	print_str("\r\nR6 : ");
	print_hex(regs->r6);
	print_str("\r\nR7 : ");
	print_hex(regs->r7);
	print_str("\r\nR8 : ");
	print_hex(regs->r8);
	print_str("\r\nR9 : ");
	print_hex(regs->r9);
	print_str("\r\nR10: ");
	print_hex(regs->r10);
	print_str("\r\nR11: ");
	print_hex(regs->r11);
	print_str("\r\nR12: ");
	print_hex(regs->r12);
	print_str("\r\nPC : ");
	print_hex(regs->pc);
	print_str("\r\nPSR: ");
	print_hex(regs->cpsr);
	print_str("\r\nSPSR_svc: ");
	print_hex(regs->SPSR_svc);
	print_str("\r\nlr: ");
	print_hex(regs->lr);
	print_str("\r\nSP_usr: ");
	print_hex(regs->SP_usr);
	print_str("\r\nSP_svc: ");
	print_hex(regs->SP_svc);
	print_str("\r\nlr_svc: ");
	print_hex(regs->lr_svc);
	print_str("\r\n\r\n");
}

/**
 * \fn handle_trap_undefined_instruction(struct cpuRegs_s *regs)
 *
 * Handle undefined instruction trap
 */
void handle_trap_undefined_instruction(struct cpuRegs_s *regs)
{
	printk("\r\nUndefine Instruction Trap");
	print_regs(regs);
	while(1);
}

/**
 * \fn handle_trap_supervisor_call(struct cpuRegs_s *regs)
 *
 * Handle supervisor call trap
 */
void handle_trap_supervisor_call(struct cpuRegs_s *regs)
{
	printk("\r\nSupervisor Call Trap");
	print_regs(regs);
	while(1);
}

/**
 * \fn handle_trap_prefetch_abort(struct cpuRegs_s *regs)
 *
 * Handle prefetch abort trap
 */
void handle_trap_prefetch_abort(struct cpuRegs_s *regs)
{
	printk("\r\nPrefetch Abort Trap");
	print_regs(regs);
	while(1);
}

/**
 * \fn handle_trap_data_abort(struct cpuRegs_s *regs)
 *
 * Handle data abort trap
 */
void handle_trap_data_abort(struct cpuRegs_s *regs)
{
	printk("\r\nData Abort Trap");
	print_regs(regs);
	while(1);
}

/**
 * \fn handle_trap_irq(struct cpuRegs_s *regs)
 *
 * Handle IRQ trap
 */
void handle_trap_irq(struct cpuRegs_s *regs)
{
	unsigned int interrupt = GICC[GICC_IAR];

	callIRQHandler(interrupt, regs);

	GICC[GICC_DIR] = interrupt;	// deactivate interrupt to reset priority
	GICC[GICC_EOIR] = interrupt;	// end of interrupt
}

/**
 * \fn handle_trap_fiq(struct cpuRegs_s *regs)
 *
 * Handle fast IRQ trap
 */
void handle_trap_fiq(struct cpuRegs_s *regs)
{
	printk("\r\nFIQ Trap");
	print_regs(regs);
	while(1);
}

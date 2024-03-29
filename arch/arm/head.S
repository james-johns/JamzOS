
.arm
#include <asm/assembler.h>
#include <printk.h>

.extern _kmain
.extern init_platform
	
/* easy use print macro. requires usable stack,
	clobers r0 */
#ifndef PRINT
#define PRINT(_s) \
	ldr r0, =100f; \
	bl print_str; \
	b 101f; \
100:	.asciz _s; \
	.align 2; \
101:	
#endif

GLOBAL(_start)
_start:
	cpsid aif
	ldr sp, =boot_stack
	bl init_platform
	mov r0, #'A'
	bl putc
	mov r0, #'\r'
	bl putc
	mov r0, #'\n'
	bl putc
check_mode:
	mrs r0, cpsr
	and r0, r0, #0x1F
	cmp r0, #0x13
	bne non_svc
	PRINT("SVC mode active\r\n")

	b _start_kmain
non_svc:
	PRINT("SVC mode not active. ~~~ Halting! ~~~\r\n")
	b halt

_start_kmain:
	mrs r0, cpsr
	bl print_hex
	bl _kmain

halt:
	wfe
	b halt

GLOBAL(enableIRQS)
enableIRQS:
	cpsie aif
	mov pc, lr
GLOBAL(disableIRQS)
disableIRQS:
	cpsid aif
	mov pc, lr
	
GLOBAL(install_svc_vectors)
install_svc_vectors:
	ldr r0, =svc_vectors
	mcr p15, 0, r0, c12, c0, 0 /* set VBAR */
	bx lr

.align 5
svc_vectors:
	.word 0
	b trap_undefined_instruction
	b trap_supervisor_call
	b trap_prefetch_abort
	b trap_data_abort
	.word 0
	b trap_irq
	b trap_fiq

.extern handle_trap_undefined_instruction
trap_undefined_instruction:
	SAVE_REGS
	mov r0, sp
	bl handle_trap_undefined_instruction
	RESTORE_REGS
	eret
trap_supervisor_call:
	SAVE_REGS
	mov r0, sp
	bl handle_trap_supervisor_call
	RESTORE_REGS
	eret
trap_prefetch_abort:
	SAVE_REGS
	mov r0, sp
	bl handle_trap_prefetch_abort
	RESTORE_REGS
	eret
trap_data_abort:
	SAVE_REGS
	mov r0, sp
	bl handle_trap_data_abort
	RESTORE_REGS
	eret
trap_irq:
	SAVE_REGS
	mov r0, sp
	bl handle_trap_irq
	RESTORE_REGS
	eret
trap_fiq:
	SAVE_REGS
	mov r0, sp
	bl handle_trap_fiq
	RESTORE_REGS
	eret

GLOBAL(setTTBR0)
setTTBR0:
	dsb
	mcrr p15, 0, r0, r1, c2
	isb
	mov pc, lr
GLOBAL(setTTBR1)
setTTBR1:
	dsb
	mcrr p15, 1, r0, r1, c2
	isb
	mov pc, lr
GLOBAL(setVTCR)
setVTCR:
	mcr p15, 0, r0, c2, c1, 2
	mov pc, lr
GLOBAL(getVTCR)
getVTCR:
	mrc p15, 0, r0, c2, c1, 2
	mov pc, lr
	
GLOBAL(setMAIR0VAL)
setMAIR0VAL:
	mcr p15, 0, r0, c10, c2, 0
/*	mcr p15, 4, r0, c10, c2, 0*/
	mov pc, lr
GLOBAL(setMAIR1VAL)
setMAIR1VAL:
	mcr p15, 0, r0, c10, c2, 1
/*	mcr p15, 4, r0, c10, c2, 1*/
	mov pc, lr
GLOBAL(enableMMU)
enableMMU:
	mov r0, #0 /* T0SZ, T1SZ = 0, so only TTBR0 is used */
	orr r0, r0, #0x80000000 /* EAE */
	orr r0, r0, #0x3000 /* SH0 */
	orr r0, r0, #0xC00 /* ORGN0, IRGN0 */
	mcr p15, 0, r0, c2, c0, 2 /* TTBCR */
	mrc p15, 0, r0, c1, c0, 0
	orr r0, r0, #0x03 /* MMU and D-Cache enable */
	dsb
	mcr p15, 0, r0, c1, c0, 0
	isb
	mov pc, lr
GLOBAL(disableMMU)
disableMMU:
	push {r0-r1}
	mov r1, #3
	mvn r1, r1
	mrc p15, 0, r0, c1, c0, 0
	and r0, r0, r1 /* MMU and D-Cache enable */
	dsb
	mcr p15, 0, r0, c1, c0, 0
	isb
	pop {r0-r1}
	mov pc, lr
	
/* init_uart
 * IN:
 * OUT:
 * SMASHED: r0, r1, r2
 *
 * Initialise UART0 to 8n1 with interrupts and fifos disabled
 *
init_uart:
	ldr r0, =UART_BASE
	mov r1, #0x03
	mov r2, #0x00
	strb r1, [r0, #UART_LCR]
	strb r2, [r0, #UART_IER]
	strb r2, [r0, #UART_FCR]
	strb r1, [r0, #UART_MCR]
	mov pc, lr
*/	
/* putc
 * IN: r0 - character to print
 * OUT:
 * SMASHED: r1
 *
putc:
	ldr r1, =UART_BASE
	strb r0, [r1, #UART_TX]
	mov pc, lr
*/
.align 4
.comm boot_stack, 0x2000


	

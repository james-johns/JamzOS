

#ifndef PRINTH_H
#define PRINTH_H


/*#define UART_BASE 	0x01c28000*/
#define UART_BASE 	0x1c090000
#define UART_TX		0x00
#define	UART_IER	0x04
#define UART_FCR	0x08
#define UART_LCR	0x0C
#define UART_MCR	0x10
#define UART_LINE_STATUS 0x14

#define STATUS_Tx_EMPTY (1 << 5)



#ifdef __ASSEMBLY__
.extern print_str
.extern print_hex
.extern printh
#else

#include <cpu.h>

void printh(const char *fmt, ...);
void print_str(const char *str);
void print_hex(unsigned int val);
void putc(char c);
void print_regs(struct cpuRegs_s *regs);
#endif

#endif

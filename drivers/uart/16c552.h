
#ifndef _UART_16c552_H_
#define _UART_16c552_H_

/*#define UART_BASE 	0x01c28000*/
#define UART_16c552_BASE 	0x1c090000
#define UART_16c552 ((unsigned char *) UART_16c552_BASE)
#define UART_16c552_TX		0x00
#define	UART_16c552_IER	0x04
#define UART_16c552_FCR	0x08
#define UART_16c552_LCR	0x0C
#define UART_16c552_MCR	0x10
#define UART_16c552_LINE_STATUS 0x14

#define UART_16c552_STATUS_Tx_EMPTY (1 << 5)
#define UART_16c552_STATUS_Rx_READY (1 << 0)

struct uart_s uart_16c552;

#endif


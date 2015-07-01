

#include <uart.h>
#include <uart/16c552.h>

void init_16c552()
{
	UART_16c552[UART_16c552_LCR] = 0x03;
	UART_16c552[UART_16c552_IER] = 0x00;
	UART_16c552[UART_16c552_FCR] = 0x00;
	UART_16c552[UART_16c552_MCR] = 0x03;
}

void write_16c552(char c)
{
	// wait for Tx to empty before outputting next character
	while ((UART_16c552[UART_16c552_LINE_STATUS] & UART_16c552_STATUS_Tx_EMPTY) != 0x00);
	UART_16c552[UART_16c552_TX] = c;
}

char read_16c552()
{
	while ((UART_16c552[UART_16c552_LINE_STATUS] & UART_16c552_STATUS_Rx_READY) != 0x00);
	return UART_16c552[UART_16c552_TX];
}

struct uart_s uart_16c552 = { .read = read_16c552, .write = write_16c552 };

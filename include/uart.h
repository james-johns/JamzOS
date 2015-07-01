

#ifndef _UART_H_
#define _UART_H_

struct uart_s {
	void (*write)(char);
	char (*read)(void);
};

struct uart_s defaultUART;

#endif

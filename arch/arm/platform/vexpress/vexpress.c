
#include <platform.h>

#include <uart.h>
#include <printk.h>

#include <uart/16c552.h>

void init_platform()
{
	defaultUART = uart_16c552;
}



#include <config.h>
#include <va_arg.h>
#include <malloc.h>
#include <printk.h>

#ifdef TESTING
void test_hypervisor()
{
	printk("\r\n\r\nAuto-testing hypervisor\r\n"); 
	test_va_arg();
	test_malloc();
}
#else
void test_hypervisor() { }
#endif

#include "peripheral/uart.h"
#include "sysreg.h"

void exc_hdlr()
{
    unsigned long ret = sysreg_read(elr_el1);
    uart0_printlx(ret);
    uart0_putc('\n');
}
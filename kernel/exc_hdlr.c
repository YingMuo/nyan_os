#include "string.h"
#include <stdint.h>

uint32_t ctcnt = 0;

void core_timer_hdlr()
{
    ctcnt++;
    prints("core timer jeffies: ");
    printu(ctcnt);
    putc('\n');
}
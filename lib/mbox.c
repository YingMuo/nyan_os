#include "peripheral/reg.h"
#include <stdint.h>

#define MBOX_EMPTY      0x40000000
#define MBOX_FULL       0x80000000
#define MBOX_RESPONSE   0x80000000

volatile uint32_t  __attribute__((aligned(16))) mbox[36];

int mbox_call(char c)
{
    uint32_t r = (uint32_t)(((uint64_t)&mbox & ~0xf) | (c & 0xf));
    while (*MBOX_STATUS & MBOX_FULL);
    *MBOX_WRITE = r;
    for (;;)
    {
        while (*MBOX_STATUS & MBOX_EMPTY);
        if (r == *MBOX_READ)
            return mbox[1] == MBOX_RESPONSE;
    }
    return 0;
}
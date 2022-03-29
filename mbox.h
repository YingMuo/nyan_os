#ifndef _MBOX_H
#define _MBOX_H

#include <stdint.h>

extern volatile uint32_t mbox[36];

#define MBOX_REQUEST    0

/* channels */
#define MBOX_CH_POWER   0
#define MBOX_CH_FB      1
#define MBOX_CH_VUART   2
#define MBOX_CH_VCHIQ   3
#define MBOX_CH_LEDS    4
#define MBOX_CH_BTNS    5
#define MBOX_CH_TOUCH   6
#define MBOX_CH_COUNT   7
#define MBOX_CH_PROP    8

#define MBOX_TAG_GETSERIAL  0x10004
#define MBOX_TAG_SETCLKRATE  0x10004
#define MBOX_TAG_LAST       0

int mbox_call(char c);

#endif /* _MBOX_H */
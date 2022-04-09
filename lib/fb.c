#include "peripheral/mbox.h"
#include "peripheral/uart.h"
#include "peripheral/fb.h"

struct fb_struct fb;

void fb_init()
{
    mbox[0] = 35 * 4;
    mbox[1] = MBOX_REQUEST;

    mbox[2] = 0x48003; //set phy w/h
    mbox[3] = 8;
    mbox[4] = 8;
    mbox[5] = 640; // width
    mbox[6] = 480; // height

    mbox[7] = 0x48004; //set virt w/h
    mbox[8] = 8;
    mbox[9] = 8;
    mbox[10] = 640; // virtual_width
    mbox[11] = 480 * 2; // virtual_height

    mbox[12] = 0x48009; //set virt offset
    mbox[13] = 8;
    mbox[14] = 8;
    mbox[15] = 0; // x
    mbox[16] = 0; // y

    mbox[17] = 0x48005; //set depth
    mbox[18] = 4;
    mbox[19] = 4;
    mbox[20] = 32; // depth

    mbox[21] = 0x48006; //set pixel order
    mbox[22] = 4;
    mbox[23] = 4;
    mbox[24] = 1; // RGB

    mbox[25] = 0x40001; // allocate buffer
    mbox[26] = 8;
    mbox[27] = 8;
    mbox[28] = 4096; // base address
    mbox[29] = 0; // size

    mbox[30] = 0x40008; //get pitch
    mbox[31] = 4;
    mbox[32] = 4;
    mbox[33] = 0; // pitch

    mbox[34] = MBOX_TAG_LAST;

    if (mbox_call(MBOX_CH_PROP) && mbox[20] == 32)
    {
        mbox[28] &= 0x3FFFFFFF; //convert GPU address to ARM address
        fb.width = mbox[5]; //get actual physical width
        fb.height = mbox[6]; //get actual physical height
        fb.pitch = mbox[33]; //get number of bytes per line
        fb.isrgb = mbox[24]; //get the actual channel order
        fb.next = 1;
        fb.ptr[0] = (void *)((uint64_t)mbox[28]);
        fb.ptr[1] = (void *)((uint64_t)mbox[28] + fb.height * fb.pitch);
        fb.size = mbox[29];

        uart0_prints("fb width: ");
        uart0_printu(fb.width);
        uart0_putc('\n');

        uart0_prints("fb height: ");
        uart0_printu(fb.height);
        uart0_putc('\n');

        uart0_prints("fb pitch: ");
        uart0_printu(fb.pitch);
        uart0_putc('\n');

        uart0_prints("fb isrgb: ");
        uart0_printu(fb.isrgb);
        uart0_putc('\n');

        uart0_prints("fb ptr[0]: ");
        uart0_printlx((uint64_t)fb.ptr[0]);
        uart0_putc('\n');

        uart0_prints("fb ptr[1]: ");
        uart0_printlx((uint64_t)fb.ptr[1]);
        uart0_putc('\n');

        uart0_prints("fb size: ");
        uart0_printx(fb.size);
        uart0_putc('\n');
    }
    else
    {
        uart0_puts("Unable to set screen resolution to 1024x768x32\n");
    }
}

void fb_flip()
{
    if (fb.next == 1)
    {
        mbox[0] = 8 * 4;
        mbox[1] = MBOX_REQUEST;

        mbox[2] = 0x48009; //set virt offset
        mbox[3] = 8;
        mbox[4] = 8;
        mbox[5] = 0; // x
        mbox[6] = fb.height; // y

        mbox[7] = MBOX_TAG_LAST;

        fb.next = 0;
    }
    else
    {
        mbox[0] = 8 * 4;
        mbox[1] = MBOX_REQUEST;

        mbox[2] = 0x48009; //set virt offset
        mbox[3] = 8;
        mbox[4] = 8;
        mbox[5] = 0; // x
        mbox[6] = 0; // y

        mbox[7] = MBOX_TAG_LAST;

        fb.next = 1;
    }
}

void fb_clear()
{
    for (int i = 0; i < fb.height * fb.pitch; ++i)
        fb.ptr[fb.next][i] = 0;
}

void fb_draw_pixel(uint32_t x, uint32_t y, char r, char g, char b)
{
    if (x >= fb.width || y >= fb.height)
        return;
    uint32_t off = y * fb.pitch + x * 4;
    uint32_t rgb = (uint32_t)r << 16 | (uint32_t)g << 8 | (uint32_t)b;
    *(uint32_t *)(fb.ptr[fb.next] + off) = rgb;
}
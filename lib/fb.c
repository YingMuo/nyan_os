#include "mbox.h"
#include "string.h"

uint32_t width, height, pitch, isrgb;
char *fb;

void fb_init()
{
    mbox[0] = 35 * 4;
    mbox[1] = MBOX_REQUEST;

    mbox[2] = 0x48003; //set phy w/h
    mbox[3] = 8;
    mbox[4] = 8;
    mbox[5] = 1024; // width
    mbox[6] = 768; // height

    mbox[7] = 0x48004; //set virt w/h
    mbox[8] = 8;
    mbox[9] = 8;
    mbox[10] = 1024; // virtual_width
    mbox[11] = 768; // virtual_height

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
        width = mbox[5]; //get actual physical width
        height = mbox[6]; //get actual physical height
        pitch = mbox[33]; //get number of bytes per line
        isrgb = mbox[24]; //get the actual channel order
        fb = (void *)((uint64_t)mbox[28]);
    }
    else
    {
        puts("Unable to set screen resolution to 1024x768x32\n");
    }
}

void fb_draw_pixel(uint32_t x, uint32_t y, char r, char g, char b)
{
    uint32_t off = y * pitch + x * 4;
    uint32_t rgb = (uint32_t)r << 16 | (uint32_t)g << 8 | (uint32_t)b;
    *(uint32_t *)(fb + off) = rgb;
}

void fb_show()
{
    for (uint32_t x = 0; x < width; ++x)
    {
        for (uint32_t y = 0; y < height; ++y)
        {
            if ((x + y) / 16 % 2)
                fb_draw_pixel(x, y, 0xff, 0xff, 0xff);
            else
                fb_draw_pixel(x, y, 0x00, 0x00, 0x00);
        }
    }
}
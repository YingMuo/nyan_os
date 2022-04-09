#ifndef _FB_H
#define _FB_H

#include "stdint.h"

extern const uint32_t width, height;

struct fb_struct
{
    uint32_t width;
    uint32_t height;
    uint32_t pitch;
    uint32_t isrgb;
    char *ptr[2];
    uint32_t size;
    uint8_t next;
};

void fb_init();
void fb_flip();
void fb_clear();
void fb_draw_pixel(uint32_t x, uint32_t y, char r, char g, char b);

#endif /* _FB_H */
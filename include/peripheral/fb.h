#ifndef _FB_H
#define _FB_H

#include "types.h"

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

void fb_init(uint64_t width, uint64_t height, uint32_t depth);
void fb_flip();
void fb_clear();
void fb_draw_pixel_rgb_24(uint32_t x, uint32_t y, uint8_t r, uint8_t g, uint8_t b);
void fb_draw_pixel_rgb_16(uint32_t x, uint32_t y, uint8_t r, uint8_t g, uint8_t b);
void fb_draw_pixel_rgb_8(uint32_t x, uint32_t y, uint8_t r, uint8_t g, uint8_t b);
void fb_draw_pixel_16(uint32_t x, uint32_t y, uint16_t rgb);

#endif /* _FB_H */
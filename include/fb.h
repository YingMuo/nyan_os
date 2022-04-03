#ifndef _FB_H
#define _FB_H

void fb_init();
void fb_show();
void fb_draw_pixel(uint32_t x, uint32_t y, char r, char g, char b);

#endif /* _FB_H */
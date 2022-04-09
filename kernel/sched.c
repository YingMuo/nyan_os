#include "timer.h"
#include "peripheral/fb.h"

void draw(uint64_t jeffies)
{
    for (int y = 0; y < 480; ++y)
    {
        for (int x = 0; x < 640; ++x)
        {
            if ((x + y + jeffies * 4) / 16 % 2)
                fb_draw_pixel(x, y, 0xff, 0xff, 0xff);
            else
                fb_draw_pixel(x, y, 0x00, 0x00, 0x00);
        }
    }
}

void sched()
{
    uint64_t jeffies = get_jeffies();
    if (jeffies % 3 == 0)
    {
        fb_flip();
        draw(jeffies);
    }
}
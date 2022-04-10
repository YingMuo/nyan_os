#include "timer.h"
#include "peripheral/fb.h"
#include "animation.h"

void draw(uint64_t jeffies)
{
    for (int y = 0; y < 512; ++y)
    {
        for (int x = 0; x < 512; ++x)
        {
            fb_draw_pixel_16(x, y, frames_16[frame_ctr][y / 8][x / 8]);
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
        ++frame_ctr;
        frame_ctr %= 12;
    }
}
/*
 * Pop Tart Cat animation frames
 */
#ifndef ANIMATION_H
#define ANIMATION_H

#include "types.h"

#define FRAME_WIDTH  64
#define FRAME_HEIGHT 64
#define FRAME_SIZE 12

void animation_init_16();
extern uint16_t frames_16[12][64][64];
extern uint8_t frame_ctr;

#endif
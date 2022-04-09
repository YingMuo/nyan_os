#ifndef _TIMER_H
#define _TIMER_H

#include "types.h"

#define TIMER_HZ 1000LL

uint64_t get_jeffies();
void inc_jeffies();
void core_timer_enable();

#endif /* _TIMER_H */
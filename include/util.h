#ifndef _UTIL_H
#define _UTIL_H

#include <stdint.h>
uint64_t get_tc();
uint32_t get_tf();
void svc1();
void brk1();
void core_timer_enable();

#endif /* _UTIL_H */
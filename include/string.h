#ifndef _STRING_H
#define _STRING_H

#include <stdint.h>

void putc(char c);
int puts(const char *s);
int prints(const char *s);
int printu(uint32_t u);
int printlu(uint64_t lu);
int printx(uint32_t x);
int printlx(uint64_t lx);
int gets(char *s);
int strcmp(const char *s1, const char *s2);

#endif /* _STRING_H */
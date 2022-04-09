#ifndef _SYSREG_H
#define _SYSREG_H

#define sysreg_read(reg) ({\
    unsigned long __val;\
    asm volatile ("mrs %0, " #reg : "=r" (__val));\
    __val;\
})

#define sysreg_write(reg, __val) ({\
    asm volatile ("msr " #reg ", %0"  :: "r" (__val));\
})

#endif /* _SYSREG_H */
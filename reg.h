#ifndef	__REG_H
#define	__REG_H

#include <stdint.h>
#define __REG_TYPE volatile uint32_t
#define __REG __REG_TYPE *

#define MM 0x3f000000

#define GPIO        (MM + 0x200000)
#define GPFSEL1     ((__REG)(GPIO + 0x04))
#define GPSET1      ((__REG)(GPIO + 0x1c))
#define GPCLR1      ((__REG)(GPIO + 0x28))
#define GPPUD       ((__REG)(GPIO + 0x94))
#define GPPUDCLK0   ((__REG)(GPIO + 0x98))

#define AUX             (MM + 0x215000)
#define AUX_IRQ         ((__REG)(AUX + 0x00))
#define AUX_ENABLES     ((__REG)(AUX + 0x04))
#define AUX_MU_IO_REG   ((__REG)(AUX + 0x40))
#define AUX_MU_IER_REG  ((__REG)(AUX + 0x44))
#define AUX_MU_IIR_REG  ((__REG)(AUX + 0x48))
#define AUX_MU_LCR_REG  ((__REG)(AUX + 0x4C))
#define AUX_MU_MCR_REG  ((__REG)(AUX + 0x50))
#define AUX_MU_LSR_REG  ((__REG)(AUX + 0x54))
#define AUX_MU_MSR_REG  ((__REG)(AUX + 0x58))
#define AUX_MU_SCRATCH  ((__REG)(AUX + 0x5C))
#define AUX_MU_CNTL_REG ((__REG)(AUX + 0x60))
#define AUX_MU_STAT_REG ((__REG)(AUX + 0x64))
#define AUX_MU_BAUD_REG ((__REG)(AUX + 0x68))

#endif /* __REG_H */
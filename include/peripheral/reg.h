#ifndef	__REG_H
#define	__REG_H

#include "types.h"
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

#define MBOX        (MM + 0xb880)
#define MBOX_READ   ((__REG)(MBOX + 0x00))
#define MBOX_POLL   ((__REG)(MBOX + 0x10))
#define MBOX_SENDER ((__REG)(MBOX + 0x14))
#define MBOX_STATUS ((__REG)(MBOX + 0x18))
#define MBOX_CONFIG ((__REG)(MBOX + 0x1c))
#define MBOX_WRITE  ((__REG)(MBOX + 0x20))

#define UART0        (MM + 0x201000)
#define UART0_DR     ((__REG)(UART0 + 0x00))
#define UART0_RSRECR ((__REG)(UART0 + 0x04))
#define UART0_FR     ((__REG)(UART0 + 0x18))
#define UART0_ILPR   ((__REG)(UART0 + 0x20))
#define UART0_IBRD   ((__REG)(UART0 + 0x24))
#define UART0_FBRD   ((__REG)(UART0 + 0x28))
#define UART0_LCRH   ((__REG)(UART0 + 0x2c))
#define UART0_CR     ((__REG)(UART0 + 0x30))
#define UART0_IFLS   ((__REG)(UART0 + 0x34))
#define UART0_IMSC   ((__REG)(UART0 + 0x38))
#define UART0_RIS    ((__REG)(UART0 + 0x3c))
#define UART0_MIS    ((__REG)(UART0 + 0x40))
#define UART0_ICR    ((__REG)(UART0 + 0x44))
#define UART0_DMACR  ((__REG)(UART0 + 0x48))
#define UART0_ITCR   ((__REG)(UART0 + 0x80))
#define UART0_ITIP   ((__REG)(UART0 + 0x84))
#define UART0_ITOP   ((__REG)(UART0 + 0x88))
#define UART0_TDR    ((__REG)(UART0 + 0x8c))

#define CORE0_TIMER_IRQ_CTRL ((__REG)0x40000040)

#endif /* __REG_H */
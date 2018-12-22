#include <stdint.h>

#define TIMER_BASE        0x01C20C00
#define WDOG0_MODE_REG    *(volatile uint32_t *)(TIMER_BASE + 0x94)
void udelay(uint32_t d);
void reboot(uint32_t seconds);
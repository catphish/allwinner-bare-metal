#include <stdint.h>

#define TIMER_BASE        0x01C20C00
#define WDOG0_MODE    *(volatile uint32_t *)(TIMER_BASE + 0xB8)
void udelay(uint32_t d);
void reboot(uint32_t seconds);

void init_bss();
extern char* _bstart;
extern char* _bend;
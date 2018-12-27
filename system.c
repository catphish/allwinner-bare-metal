#include "system.h"

void udelay(uint32_t d) {
  for(int n=0;n<d*2;n++) asm("NOP");
}

void reboot(uint32_t seconds) {
  WDOG0_MODE = (seconds << 4) | 1;
}

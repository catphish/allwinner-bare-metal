#include "system.h"

void init_bss() {
  for (char* dst = _bstart; dst < _bend; dst++)
    *dst = 0;
}

void udelay(uint32_t d) {
  for(uint32_t n=0;n<d*200;n++) asm("NOP");
}

void reboot(uint32_t seconds) {
  WDOG0_MODE = (seconds << 4) | 1;
}

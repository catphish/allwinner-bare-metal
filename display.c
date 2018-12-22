#include <stdint.h>
#include "ccu.h"
#include "system.h"
#include "display.h"

void display_init() {
  PLL3_CFG_REG = (1<<31) |  (1<<15) | (1<<14) | 0x63; // 287MHz
  AHB_GATING_REG1 |= (1<<11) | (1<<10);
  HDMI_CLK_REG = (1<<31);
  HDMI1_RST_REG = (1<<1);
}

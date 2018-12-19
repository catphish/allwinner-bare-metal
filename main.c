#include <stdint.h>
#include "ports.h"
#include "uart.h"
#include "ccu.h"

#define DRAM_BASE         0x40000000
#define DRAM_ZERO         *(volatile uint32_t *)(DRAM_BASE + 0x4)

#define DRAMC_BASE        0x01c01000
#define DRAMC_CCR         *(volatile uint32_t *)(DRAMC_BASE + 0x0)

void udelay(uint32_t d) {
  for(int n=0;n<d*2;n++) asm("NOP");
}

void main() {
  PG_CFG0 |= (1<<8);   // PORT G2 output
  PG_DATA |= (1<<2);   // PORT G2 high
  udelay(1000000);
  PG_DATA &= ~(1<<2);  // PORT G2 low

  uart_init();
  uart_print("Hi!\r\n");

  PLL5_CFG_REG |= (1<<31);
  udelay(100000);
  //PLL5_CFG_REG |= (1<<29);
  //udelay(100000);
  //DRAMC_CCR |= (1<<31);

  //DRAM_ZERO = 0x12345678;
  //uart_print_uint32(PLL5_CFG_REG);
  //uart_print("\r\n");
  //uart_print_uint32(DRAM_ZERO);
  //uart_print("\r\n");
  uart_print("Done!\r\n");

  // Return to FEL
  asm("ldr pc, =0xFFFF0018;");
}

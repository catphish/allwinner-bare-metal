#include "ports.h"
#include "uart.h"
#include "mmu.h"
#include "system.h"

void main() {
  // Reboot in one second using watchdog
  reboot(1);

  // Configure the UART for debugging
  uart_init();
  uart_print("Hi!\r\n");

  // Set up MMU and paging configuration
  mmu_init();

  // Flash an LED for no reason
  set_pin_mode(PORTA, 15, 1); // PORT A15 output
  set_pin_data(PORTA, 15, 1); // PORT A15 high
  udelay(100000);
  set_pin_data(PORTA, 15, 0); // PORT A15 low

  uart_print("Done!\r\n");

  // Go back to sleep
  while(1) asm("wfi");
}
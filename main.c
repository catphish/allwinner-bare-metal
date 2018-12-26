#include "ports.h"
#include "uart.h"
#include "mmu.h"
#include "system.h"
#include "display.h"

void main() {
  // Reboot in 10 seconds using watchdog
  reboot(8); // 0x8 == 10 second reset timer

  // Enble all GPIO
  gpio_init();

  // Configure the UART for debugging
  uart_init();
  uart_print("Hi!\r\n");

  // Set up MMU and paging configuration
  mmu_init();

  // Illuminate the power LED
  set_pin_mode(PORTL, 10, 1); // PORT L10 output
  set_pin_data(PORTL, 10, 1); // PORT L10 high

  // Clear display memory
  for(int n=0x40000000; n<(0x40000000+1920*1080*4); n+=4)
    *(volatile uint32_t*)(n) = 0xff000000;

  // Configure display
  uart_print("Setting up display!\r\n");
  display_init((void*)0x40000000);

  // Put some data in display DRAM, if we see colours we're good
  for(int n=0x40000000; n<(0x40000000+1920*1080*2); n+=4) {
    udelay(1); *(volatile uint32_t*)(n) = 0xff00ff00;
  }
  for(int n=0x40000000+1920*1080*2; n<(0x40000000+1920*1080*4); n+=4) {
    udelay(1); *(volatile uint32_t*)(n) = 0xffff00ff;
  }

  // Go back to sleep
  while(1) asm("wfi");
}

#include "ports.h"
#include "uart.h"
#include "mmu.h"
#include "system.h"
#include "display.h"
#include "interrupts.h"

uint32_t tick_counter;

void startup() {
  tick_counter = 0;

  // Reboot in n seconds using watchdog
  reboot(4); // 0x8 == 10 second reset timer

  // Enble all GPIO
  gpio_init();

  // Configure the UART for debugging
  uart_init();
  uart_print("Booting!\r\n");

  // Set up MMU and paging configuration
  mmu_init();

  // Illuminate the power LED
  set_pin_mode(PORTL, 10, 1); // PORT L10 output
  set_pin_data(PORTL, 10, 1); // PORT L10 high

  // Configure display
  display_init((void*)(0x60000000-0x800000));

  // Put some data in display DRAM, if we see colours we're good

  install_ivt();

  // Go back to sleep
  while(1) asm("wfi");
}

void game_tick_next() {
  tick_counter++;
  //game_tick(tick_counter);
}

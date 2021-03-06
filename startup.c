#include "ports.h"
#include "uart.h"
#include "mmu.h"
#include "system.h"
#include "display.h"
#include "interrupts.h"
#include "ccu.h"
#include "usb.h"

uint32_t tick_counter;

void game_tick(uint32_t tick_counter);
void game_start();

void startup() {
  init_bss();

  // Reboot in n seconds using watchdog
  reboot(2); // 0x8 == 10 second reset timer

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
  display_init((volatile uint32_t*)(0x60000000-VIDEO_RAM_BYTES));

  // USB
  usb_init();

  uart_print("Ready!\r\n");
  game_start();

  install_ivt();

  // Go back to sleep
  while(1) asm("wfi");
}

void game_tick_next() {
  buffer_swap();
  game_tick(tick_counter);
  tick_counter++;
}

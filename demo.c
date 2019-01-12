#include <stdint.h>
#include "spritelayers.h"
#include "display.h"
#include "demo_data.h"
#include "uart.h"

int32_t abs(int32_t i) {
  return(i < 0 ? 0 - i : i);
}

void game_start() {
  
}

void game_tick(uint32_t tick_counter) {
  for(int n=0; n<480*270; n++)
    framebuffer[n] = 0xff0000ff;

  //   DE_WB_STATUS = 0xffffffff;
  //   DE_WB_GCTRL |= 1;
    
  // uart_print_uint32(framebuffer2[1]);
  // uart_print(" ");
  // uart_print_uint32(DE_WB_STATUS);
  // uart_print(" ");
  // uart_print_uint32(DE_WB_DEBUG);
  // uart_print("\r\n");
}

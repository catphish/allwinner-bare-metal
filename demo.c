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
  //for(int test=0;test<20;test++){
    for(int n=0; n<480*270; n++) {
      uint32_t data = demo_sprite[n%256];
      if(data) active_buffer[n+tick_counter] = data;
      //active_buffer[n] = 0xff0000ff;
    }
  //}

  // uart_print_uint32(tick_counter);
  // uart_print("\r\n");
}

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
  for(int n=0; n<480*135; n++)
    framebuffer[n] = 0xffff0000;
  for(int n=480*135; n<480*270; n++)
    framebuffer[n] = 0xff00ff00;
}

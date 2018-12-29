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
  uint32_t** pattern = (uint32_t**)0x50000000;
  for(int n=0;n<1024;n++)
    pattern[n] = demo_sprite;

  for(int n=0;n<480*270;n++)
    framebuffer_back[n]=0;

  fill(0xff008080);

  struct sprite_layer background = {
    .pattern = pattern,
    .x_size = 32,
    .y_size = 6,
    .x_offset = -((tick_counter/4)%16),
    .y_offset = 0,
  };
  render_layer(&background);

  struct sprite_layer foreground = {
    .pattern = pattern,
    .x_size = 32,
    .y_size = 6,
    .x_offset = -((tick_counter/2)%16),
    .y_offset = 120,
  };
  render_layer(&foreground);

  uint32_t y = abs((tick_counter % 200) - 100);
  render_sprite(demo_sprite, 230, 100+y);

}

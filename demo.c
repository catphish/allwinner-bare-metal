#include <stdint.h>
#include "spritelayers.h"
#include "display.h"
#include "demo_data.h"
#include "uart.h"

// A quick demo of the graphics engine
uint32_t x, y;
uint32_t direction_x, direction_y;

void game_start() {
  x = 0;
  y = 0;
  direction_x = 3;
  direction_y = 2;
}

void game_tick(uint32_t tick_counter) {
  struct sprite_list demo_sprite_list = {
    .sprite_data = (uint32_t*)demo_sprite,
    .x_offset = x,
    .y_offset = y,
    .next = 0
  };
  for(int n=0;n<10000;n++)
    render_sprites(&demo_sprite_list);

  x+=direction_x; y+=direction_y;
  if(x<=0)      direction_x =  3;
  if(x>=480-16) direction_x = -3;
  if(y<=0)      direction_y =  2;
  if(y>=270-16) direction_y = -2;
}

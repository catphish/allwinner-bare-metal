#include <stdint.h>
#include "spritelayers.h"
#include "display.h"
#include "demo_data.h"
#include "uart.h"

// Define the scrolling background pattern
uint32_t* pattern[31*18];
struct sprite_layer background;

void game_start() {
  // Populate the pattern
  for(int n=0;n<31*17;n++)
    pattern[n] = demo_sprite;

  // Configure the background to use the pattern
  background.pattern = pattern;
  background.x_size = 31;
  background.y_size = 17;
  background.x_offset = 0;
  background.y_offset = 0;
}

void game_tick(uint32_t tick_counter) {
  // Scroll the background
  background.x_offset = -(tick_counter%16);
  // ...and render it
  render_layer(&background);
}

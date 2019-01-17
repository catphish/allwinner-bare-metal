#include <stdint.h>
#include "spritelayers.h"
#include "display.h"

void render_layer(struct sprite_layer* layer){
  for(uint32_t y=0;y<layer->y_size;y++) {
    for(uint32_t x=0;x<layer->x_size;x++) {
      render_sprite(layer->pattern[y*layer->x_size+x], x*16+layer->x_offset, y*16+layer->y_offset);
    }
  }
}

void render_sprite(uint32_t* pattern, int32_t x_offset, int32_t y_offset){
  // Add 16 to the offset such that 0,0 is the upper-left of the visible display
  x_offset += 16;
  y_offset += 16;
  volatile uint32_t* destination = active_buffer + y_offset*512 + x_offset;
  for(int y=0; y<16; y++) {
    for(int x=0; x<16; x++) {
      if(*pattern) {
        *destination = *pattern;
      }
      pattern++;
      destination++;
    }
    destination += 512-16;
  }
}

// TODO: An additionl function to render individual sprites with full 8-bit opacity

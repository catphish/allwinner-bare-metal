#include <stdint.h>
#include "spritelayers.h"
#include "display.h"

void fill(uint32_t color) {
  for(int n=0;n<480*270;n++)
    framebuffer[n] = color;
}

void render_layer(struct sprite_layer* layer){
  for(uint32_t y=0;y<layer->y_size;y++) {
    for(uint32_t x=0;x<layer->x_size;x++) {
      render_sprite(layer->pattern[y*layer->x_size+x], x*16+layer->x_offset, y*16+layer->y_offset);
    }
  }
}

void render_sprite(uint32_t* pattern, int32_t x_offset, int32_t y_offset){
  for(int y=0; y<16; y++) {
    for(int x=0; x<16; x++) {
      int32_t destination_x = x_offset + x;
      int32_t destination_y = y_offset + y;
      if(destination_x < 0 || destination_x > 479) continue;
      if(destination_y < 0 || destination_y > 269) continue;
      uint32_t source = pattern[y*16+x];
      if(source) {
        framebuffer[destination_y*480+destination_x] = source;
      }
    }
  }
}

// TODO: An additionl function to render individual sprites with full 8-bit opacity

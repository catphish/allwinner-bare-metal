#include <stdint.h>
#include "spritelayers.h"
#include "display.h"
#include "uart.h"

void render_sprites(struct sprite_list* list) {
  volatile uint32_t* framebuffer = active_framebuffer();
  do {
    for(int x=0;x<16;x++) {
      for(int y=0;y<16;y++) {
        // Check pixel isn't transparent
        int destination_x = x + list->x_offset;
        int destination_y = y + list->y_offset;
        if(destination_x<0 || destination_x > 479) continue;
        if(destination_y<0 || destination_y > 269) continue;

        uint32_t top_pixel = list->sprite_data[y*16+x];
        // uint32_t top_opacity = top_pixel >> 24;
        // if(!top_opacity) continue;

        // uint32_t bottom_pixel = framebuffer[destination_y*480 + destination_x];
        // uint32_t bottom_opacity = 255 - top_opacity;

        // uint32_t rb = (bottom_pixel & 0xff0000) >> 16;
        // uint32_t gb = (bottom_pixel & 0xff00)   >> 8;
        // uint32_t bb = (bottom_pixel & 0xff)     >> 0;

        // uint32_t rt = (top_pixel & 0xff0000) >> 16;
        // uint32_t gt = (top_pixel & 0xff00)   >> 8;
        // uint32_t bt = (top_pixel & 0xff)     >> 0;

        // uint32_t r = (rb * bottom_opacity + rt * top_opacity) >> 8;
        // uint32_t b = (bb * bottom_opacity + bt * top_opacity) >> 8;
        // uint32_t g = (gb * bottom_opacity + gt * top_opacity) >> 8;

        framebuffer[destination_y*480 + destination_x] = top_pixel; //0xff000000 | (r<<16) | (g<<8) | b;
      }
    }
    list = list->next;
  } while(list);
}

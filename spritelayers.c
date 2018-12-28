#include <stdint.h>
#include <arm_neon.h>
#include "spritelayers.h"
#include "display.h"
#include "uart.h"

void render_sprites(struct sprite_list* list) {
  volatile uint32_t* framebuffer = active_framebuffer();

  do {
    // int32_t start_x, end_x;
    // if(list->x_offset < 0)      start_x = 0 - list->x_offset;
    // else                        start_x = 0;
    // if(list->x_offset > 480-16) end_x = 479 - list->x_offset;
    // else                        end_x = 15;

    // int32_t start_y, end_y;
    // if(list->y_offset < 0)      start_y = 0 - list->y_offset;
    // else                        start_y = 0;
    // if(list->y_offset > 270-16) end_y = 269 - list->y_offset;
    // else                        end_y = 15;
    for(int y=0;y<16;y++) {
      int source_y = y * 16;
      int destination = (y + list->y_offset) * 480 + list->x_offset;
      // uart_print("list->sprite_data: ");
      // uart_print_uint32(list->sprite_data);
      // uart_print("\r\nframebuffer: ");
      // uart_print_uint32(framebuffer);
      // uart_print("\r\n");

      asm(
        "VLDM %[source], {s0-s15};"
        "VSTM %[destination], {s0-s15};"
        : : [source]"r"(list->sprite_data+source_y), [destination]"r"(framebuffer+destination));

    //     uint32_t top_pixel = list->sprite_data[source_y+x];
    //     // uint32_t top_opacity = top_pixel >> 24;
    //     // if(!top_opacity) continue;

    //     // uint32_t bottom_pixel = framebuffer[destination_y*480 + destination_x];
    //     // uint32_t bottom_opacity = 255 - top_opacity;

    //     // uint32_t rb = (bottom_pixel & 0xff0000) >> 16;
    //     // uint32_t gb = (bottom_pixel & 0xff00)   >> 8;
    //     // uint32_t bb = (bottom_pixel & 0xff)     >> 0;

    //     // uint32_t rt = (top_pixel & 0xff0000) >> 16;
    //     // uint32_t gt = (top_pixel & 0xff00)   >> 8;
    //     // uint32_t bt = (top_pixel & 0xff)     >> 0;

    //     // uint32_t r = (rb * bottom_opacity + rt * top_opacity) >> 8;
    //     // uint32_t b = (bb * bottom_opacity + bt * top_opacity) >> 8;
    //     // uint32_t g = (gb * bottom_opacity + gt * top_opacity) >> 8;

    //     framebuffer[destination_y + destination_x] = top_pixel; //0xff000000 | (r<<16) | (g<<8) | b;
    //   }
    }
    list = list->next;
  } while(list);
}

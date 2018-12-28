#include <stdint.h>
#include "spritelayers.h"
#include "display.h"

void render_sprites(struct sprite_list* list) {
  do {
    int32_t destination = list->y_offset * 480 + list->x_offset;
    for(int source=0; source<16*16;source++) {
      if(list->sprite_data[source] & 0xff000000) {
        framebuffer_back[destination] = list->sprite_data[source];
      }
      destination++;
      if(source % 16 == 15)destination += 480-16;
    }
    list = list->next;
  } while(list);
}

// TODO: We want 3 separate functions here:
// * A background grid (with fixed background colour)
// * A foreground grid (with transparency)
// * A list of individual sprites with transparency (render_sprites already implemented)

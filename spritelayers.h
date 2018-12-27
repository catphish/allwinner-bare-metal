#include <stdint.h>

struct sprite_list {
  uint32_t* sprite_data;
  int32_t x_offset;
  int32_t y_offset;
  struct sprite_list* next;
};

void render_sprites(struct sprite_list* list);
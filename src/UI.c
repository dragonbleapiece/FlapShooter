#include "UI.h"

void initUILevel(UI *interface, Level level) {
  Entity *item;
  interface->items = NULL;
  interface->textures = NULL;
  int i;
  Texture *t = createTextureToList(&(interface->textures), SRC_HEART, 1, 1);
  float size = 16. / UNITE;
  float margin = 0.1;
  for(i = 1; i <= level.player->maxLife; ++i) {
    item = allocEntity((margin + size) * i , margin, size, size, -1, 0., t, NULL, VOID_CODE);
    addEntityToList(&(interface->items), item);
  }
}



#ifndef UI_H
#define UI_H
#include <math.h>
#include "settings.h"
#include "entity.h"
#include "texture.h"
#include "level.h"

typedef struct ui {
  EntityList items;
  TextureList textures;
} UI;

void initUILevel(UI *interface, Level level);


#endif

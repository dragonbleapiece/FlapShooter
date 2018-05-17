/*
 * level.c
 * Déclaration de la structure et des fonctions de gestion des entités (vaiseaux, obstacles, bonus etc...)
 *
 * Auteur : Nicolas CUSUMANO & Nicolas SENECAL
 * IMAC1 - S2 - Promotion 2020
 */

#include "level.h"
#include "entity.h"
#include "ppm.h"
#include "settings.h"
#include "bounding.h"
#include "collision.h"

Level generateLevelFromFile(const char filename[]) {

  Level level;
  initialiseLevel(&level);
  PPMImage *img = generatePPMImageFromFile(filename);

  //printPPMImage(*img);

  if (!img) {
    fprintf(stderr, "Cannot start the game...\n");
    exit(1);
  }

  level.height = img->y;
  level.width = img->x;

  int i, j;

  for (i = 0; i < img->x; ++i) {
    for (j = 0; j < img->y; ++j) {
      if (!addEntityToLevel(img->data[i][j], &level, i, j)) {
        fprintf(stderr, "Unable to allocate memory\n");
        exit(1);
      }
    }
  }

  freePPMImage(img);
  loadBackgroundLevel(&level);

  return level;
}

void initialiseLevel(Level *level) {
  level->player = NULL;
  level->obstacles = NULL;
  level->ennemies = NULL;
  level->bonus = NULL;
  level->projectiles = NULL;
  level->background = NULL;
  level->textures = NULL;
}

int addEntityToLevel(EntityCode code, Level *level, float x, float y) {
  int r = 1;
  Entity *e;
  Texture *t;
  switch (code) {
    case VOID_CODE:
      break;

    case PLAYER_CODE:
      t = createTextureToList(&(level->textures), SRC_RABBIT, 1, 16);
      e = allocEntity(x * UNITE, y * UNITE, 80, 60, 1, 1, t, createAABBBoundingBox(0.94, 0.9));
      if (e != NULL) {
        e->speedX = LEVEL_SPEED;
        addEntityToList(&level->player, e);
      } else r = 0;
      break;

    case ENNEMYONE_CODE:
      e = allocEntity(x * UNITE, y * UNITE, 0.0, 0.0, 1, 1, NULL, NULL);
      if (e != NULL) addEntityToList(&level->ennemies, e);
      else r = 0;
      break;

    case ENNEMYTWO_CODE:
      e = allocEntity(x * UNITE, y * UNITE, 0.0, 0.0, 1, 1, NULL, NULL);
      if (e != NULL) addEntityToList(&level->ennemies, e);
      else r = 0;
      break;

    case OBSTACLE_CODE:
      e = allocEntity(x * UNITE, y * UNITE, UNITE, UNITE, -1, 1, NULL, createAABBBoundingBox(1., 1.));
      if (e != NULL) addEntityToList(&level->obstacles, e);
      else r = 0;
      break;

    case DESTRUCTIBLE_CODE:
      e = allocEntity(x * UNITE, y * UNITE, UNITE, UNITE, 1, 1, NULL, NULL);
      if (e != NULL) addEntityToList(&level->obstacles, e);
      else r = 0;
      break;

    case BONUS_CODE:
      e = allocEntity(x * UNITE, y * UNITE, 0.0, 0.0, 1, 1, NULL, NULL);
      if (e != NULL) addEntityToList(&level->bonus, e);
      else r = 0;
      break;

    case PROJECTILE_CODE:
      e = allocEntity(x * UNITE, y * UNITE, 0.0, 0.0, 1, 1, NULL, NULL);
      if (e != NULL) addEntityToList(&level->projectiles, e);
      else r = 0;
      break;

    default:
      r = 0;
      break;
  }

  return r;
}

void freeLevel(Level *level) {
  freeEntityList(&level->player);
  freeEntityList(&level->obstacles);
  freeEntityList(&level->ennemies);
  freeEntityList(&level->bonus);
  freeEntityList(&level->projectiles);
  freeEntityList(&level->background);
  freeTextureList(&level->textures);
}

void loadBackgroundLevel(Level *level) {
  Entity *e;
  Texture *t;

  /* SKY (x2) */
  t = createTextureToList(&(level->textures), SRC_BACKGROUND1, 1, 1);
  e = allocEntity(0, 0, WIDTH_BACKGROUND1, HEIGHT_BACKGROUND1, 0, 0, t, NULL);
  e->speedX = 0.5;
  addEntityToUnsortedList(&level->background, e);
  e = allocEntity(WIDTH_BACKGROUND1, 0, WIDTH_BACKGROUND1, HEIGHT_BACKGROUND1, 0, 0, t, NULL);
  e->speedX = 0.5;
  addEntityToUnsortedList(&level->background, e);

  /* MOUNTAINS (x2) */
  t = createTextureToList(&(level->textures), SRC_BACKGROUND2, 1, 1);
  e = allocEntity(0, WINDOW_HEIGHT - HEIGHT_BACKGROUND2, WIDTH_BACKGROUND2, HEIGHT_BACKGROUND2, 0, 0, t, NULL);
  e->speedX = 0.4;
  addEntityToUnsortedList(&level->background, e);
  e = allocEntity(WIDTH_BACKGROUND2, WINDOW_HEIGHT - HEIGHT_BACKGROUND2, WIDTH_BACKGROUND2, HEIGHT_BACKGROUND2, 0, 0, t, NULL);
  e->speedX = 0.4;
  addEntityToUnsortedList(&level->background, e);

  /* GROUND (x2) */
  t = createTextureToList(&(level->textures), SRC_BACKGROUND3, 1, 1);
  e = allocEntity(0, WINDOW_HEIGHT - HEIGHT_BACKGROUND3, WIDTH_BACKGROUND3, HEIGHT_BACKGROUND3, 1, 0, t, NULL);
  e->speedX = 0;
  addEntityToUnsortedList(&level->background, e);
  e = allocEntity(WIDTH_BACKGROUND3, WINDOW_HEIGHT - HEIGHT_BACKGROUND3, WIDTH_BACKGROUND3, HEIGHT_BACKGROUND3, 1, 0, t, NULL);
  e->speedX = 0;
  addEntityToUnsortedList(&level->background, e);


}

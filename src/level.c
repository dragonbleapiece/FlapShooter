/*
 * level.c
 * Déclaration de la structure et des fonctions de gestion des entités (vaiseaux, obstacles, bonus etc...)
 *
 * Auteur : Nicolas CUSUMANO & Nicolas SENECAL
 * IMAC1 - S2 - Promotion 2020
 */

#include "level.h"

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
  // On arrondie le vitesse pour prévenir des défauts d'affichage
  level.speedCoeff = 1.;
  level.speed = convert_speed(LEVEL_SPEED);

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
  level->currentBonus = NULL;
  level->playerStatus = 1;
}

int addEntityToLevel(EntityCode code, Level *level, float x, float y) {
  int r = 1;
  Entity *e;
  Texture *t;
  switch (code) {
    case VOID_CODE:
      break;

    case PLAYER_CODE:
      t = createTextureToList(&(level->textures), SRC_RABBIT, 3, 16);
      e = allocEntity(x, y, 1.4, 1.4 * 0.75, 10, 1, t, createAABBBoundingBox(0.925, 0.87), code);
      if (e != NULL) {
        e->speedX = LEVEL_SPEED * level->speedCoeff;
        e->shotX = 76. / 80.;
        e->shotY = 8. / 60.;
        e->shotFrequency = PLAYER_SHOT_FREQUENCY;
        e->life = 5;
        addEntityToList(&level->player, e);
      } else r = 0;
      break;

    case ENNEMYONE_CODE:
      t = createTextureToList(&(level->textures), SRC_RATON, 3, 16);
      e = allocEntity(x, y, 0.6, 1.2, 1, 1, t, createAABBBoundingBox(1., 1.), code);
      if (e != NULL) {
        initRouteListForEnnemyOne(e);
        e->shotFrequency = ENNEMY_SHOT_FREQUENCY;
        e->shotX = -16. / 32.;
        e->shotY = 10. / 64.;
        addEntityToList(&level->ennemies, e);
      } else r = 0;
      break;

    case ENNEMYTWO_CODE:
      e = allocEntity(x, y, 1, 1, 1, 1, NULL, NULL, code);
      if (e != NULL) addEntityToList(&level->ennemies, e);
      else r = 0;
      break;

    case OBSTACLE_CODE:
      t = createTextureToList(&(level->textures), SRC_OBSTACLE, 1, 1);
      e = allocEntity(x, y, 1, 1, -1, 1, t, createAABBBoundingBox(1., 1.), code);
      if (e != NULL) addEntityToList(&level->obstacles, e);
      else r = 0;
      break;

    case DESTRUCTIBLE_CODE:
      t = createTextureToList(&(level->textures), SRC_DESTRUCTIBLE_OBSTACLE, 1, 1);
      e = allocEntity(x, y, 1, 1, 1, 1, t, createAABBBoundingBox(1., 1.), code);
      if (e != NULL) {
        addEntityToList(&level->obstacles, e);
        // On ajoute un bonus aléatoire en dessous (1 chance sur 3)
        if (rand_a_b(1, 4) == 2)
          addEntityToLevel((EntityCode) rand_a_b(SPEED_BONUS, LIFE_BONUS + 1), level, x, y);
      } else {
        r = 0;
      }
      break;

    case PROJECTILE_CODE:
      e = allocEntity(x, y, 0.0, 0.0, 1, 1, NULL, NULL, code);
      if (e != NULL) addEntityToList(&level->projectiles, e);
      else r = 0;
      break;

    case SPEED_BONUS:
      t = createTextureToList(&(level->textures), SRC_SPEED_BONUS, 2, 10);
      e = allocEntity(x + 0.25, y + 0.25, 0.5, 0.5, 1, 0, t, createCircleBoundingBox(0.5), code);
      if (e != NULL) addEntityToList(&level->bonus, e);
      else r = 0;
      break;

    case SHOT_BONUS:
      t = createTextureToList(&(level->textures), SRC_SHOT_BONUS, 2, 10);
      e = allocEntity(x + 0.25, y + 0.25, 0.5, 0.5, 1, 0, t, createCircleBoundingBox(0.5), code);
      if (e != NULL) addEntityToList(&level->bonus, e);
      else r = 0;
      break;

    case LIFE_BONUS:
      t = createTextureToList(&(level->textures), SRC_HEART, 1, 1);
      e = allocEntity(x + 0.25, y + 0.25, 0.5, 0.5, 1, 0, t, createCircleBoundingBox(0.5), code);
      if (e != NULL) addEntityToList(&level->bonus, e);
      else r = 0;
      break;

    default:
      r = 0;
      break;
  }

  return r;
}

void removeLevelBehind(Level *level, float xMax) {
  removeEntityBehind(&level->player, xMax);
  removeEntityBehind(&level->obstacles, xMax);
  removeEntityBehind(&level->ennemies, xMax);
  removeEntityBehind(&level->bonus, xMax);
  removeEntityBehind(&level->projectiles, xMax);
}

void freeLevel(Level *level) {
  freeEntityList(&level->player);
  freeEntityList(&level->obstacles);
  freeEntityList(&level->ennemies);
  freeEntityList(&level->bonus);
  freeEntityList(&level->projectiles);
  freeEntityList(&level->background);
  freeTextureList(&level->textures);
  freeBonusList(&level->currentBonus);
}

void loadBackgroundLevel(Level *level) {
  Entity *e;
  Texture *t;
  float sizeX, sizeY;

  /* SKY */
  t = createTextureToList(&(level->textures), SRC_BACKGROUND0, 1, 1);
  sizeY = ((float) HEIGHT_BACKGROUND0 / MAX_HEIGHT_BACKGROUND) * level->height;
  sizeX = ((float) WIDTH_BACKGROUND0 / HEIGHT_BACKGROUND1) * sizeY;
  e = allocEntity(-1, 0, sizeX, sizeY, -1, 0, t, NULL, VOID_CODE);
  e->speedX = 1;
  addEntityToUnsortedList(&level->background, e);

  /* CLOUD (x2) */
  t = createTextureToList(&(level->textures), SRC_BACKGROUND1, 1, 1);
  sizeY = ((float) HEIGHT_BACKGROUND1 / MAX_HEIGHT_BACKGROUND) * level->height;
  sizeX = ((float) WIDTH_BACKGROUND1 / HEIGHT_BACKGROUND1) * sizeY;
  e = allocEntity(0, 0, sizeX, sizeY, -1, 0, t, NULL, VOID_CODE);
  e->speedX = 0.6;
  addEntityToUnsortedList(&level->background, e);
  e = allocEntity(sizeX, 0, sizeX, sizeY, -1, 0, t, NULL, VOID_CODE);
  e->speedX = 0.6;
  addEntityToUnsortedList(&level->background, e);

  /* MOUNTAINS (x2) */
  t = createTextureToList(&(level->textures), SRC_BACKGROUND2, 1, 1);
  sizeY = ((float) HEIGHT_BACKGROUND2 / MAX_HEIGHT_BACKGROUND) * level->height;
  sizeX = ((float) WIDTH_BACKGROUND2 / HEIGHT_BACKGROUND2) * sizeY;
  e = allocEntity(0, level->height - sizeY, sizeX, sizeY, -1, 0, t, NULL, VOID_CODE);
  e->speedX = 0.4;
  addEntityToUnsortedList(&level->background, e);
  e = allocEntity(sizeX, level->height - sizeY, sizeX, sizeY, -1, 0, t, NULL, VOID_CODE);
  e->speedX = 0.4;
  addEntityToUnsortedList(&level->background, e);

  /* GROUND (x2) */
  t = createTextureToList(&(level->textures), SRC_BACKGROUND3, 1, 1);
  sizeY = ((float) HEIGHT_BACKGROUND3 / MAX_HEIGHT_BACKGROUND) * level->height;
  sizeX = ((float) WIDTH_BACKGROUND3 / HEIGHT_BACKGROUND3) * sizeY;
  e = allocEntity(0, level->height - sizeY, sizeX, sizeY, -1, 0, t, NULL, VOID_CODE);
  e->speedX = 0;
  addEntityToUnsortedList(&level->background, e);
  e = allocEntity(sizeX, level->height - sizeY, sizeX, sizeY, -1, 0, t, NULL, VOID_CODE);
  e->speedX = 0;
  addEntityToUnsortedList(&level->background, e);

}
